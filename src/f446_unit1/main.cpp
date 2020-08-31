#include <string>
#include <vector>
// #include "ADXL345_I2C.h"
#include "MPU6050.h"
#include "mbed.h"
#include "base_util.h"

MPU6050 imu(PC_9, PA_8);

BaseUtil base_util;

struct ControlStatus{
  float target_speed;
  float current_speed;
  float iterm;
  float output;
  void print(){
    printf("o: %+5.3f, t: %+7.1f, c: %+7.1f i: %7.1f\n", output, target_speed, current_speed, iterm);
  }
};

struct ControlParameter{
  float f;
  float p;
  float i;
};

class PwmMotor{
public:
  PwmMotor(PinName p_mot_a, PinName p_mot_b, PinName p_enc_a, PinName p_enc_b): mot_a_(p_mot_a), mot_b_(p_mot_b), enc_a_(p_enc_a), enc_b_(p_enc_b){
    counter_ = 0;
    last_counter_ = 0;
    notify_ = false;

    enc_a_.mode(PullUp);
    enc_b_.mode(PullUp);

    enc_a_.rise([this](){
      if(this->enc_b_.read())this->counter_++;
      else this->counter_--;
    });
    // enc_a_.rise([&](){
    //   if(enc_b_.read())counter_++;
    //   else counter_--;
    // });
    // enc_a_.fall([&](){
    //   if(enc_b_.read())counter_--;
    //   else counter_++;
    // });
    // enc_b_.rise([&](){
    //   if(enc_a_.read())counter_--;
    //   else counter_++;
    // });
    // enc_b_.fall([&](){
    //   if(enc_a_.read())counter_++;
    //   else counter_--;
    // });
  }
  void setPwm(float ach, float bch){
    mot_a_ = ach;
    mot_b_ = bch;
  }
  void setTarget(float target){
    target_ = target;
  }
  void control(float dt){
    float diff = (counter_ - last_counter_) / dt - target_;
    result_.iterm = result_.iterm + diff * dt;
    float output_raw = param_.f * target_ - param_.p * diff - param_.i * result_.iterm;
    float output = std::min(std::max(output_raw, -1.0f), 1.0f);
    if(output>0)setPwm(output, 0);
    else setPwm(0, -output);

    result_.target_speed = target_;
    result_.current_speed = (counter_ - last_counter_)  / dt;
    result_.output = output;

    if(result_.target_speed == 0 && result_.current_speed == 0){
      result_.iterm /= 2.0;
    }

    last_counter_ = counter_;
  }
  void print(){
    if(notify_)result_.print();
  }
  void setParam(float f, float p, float i){
    param_.f = f;
    param_.p = p;
    param_.i = i;
  }

  ControlStatus result_;
  ControlParameter param_;
  PwmOut mot_a_;
  PwmOut mot_b_;
  InterruptIn enc_a_;
  InterruptIn enc_b_;
  float target_;
  int counter_;
  int last_counter_;
  bool notify_;
};

PwmMotor mot0(PA_6, PA_7, PA_4, PA_5);
// PwmMotor mot1(PB_0, PB_1, PC_4, PC_5);
// PwmMotor mot2(PB_8, PB_9, PB_4, PB_5);

InterruptIn test_a(PC_3);
// InterruptIn test_b(PC_5);

std::string imuCommand(std::vector<std::string> command)
{
  std::string result;
  if (command[1] == "acc")
  {
    int acc[3];
    Timer imu_timer;
    imu_timer.start();
    imu.readAccelData(acc);
    imu_timer.stop();
    uint64_t time = imu_timer.read_us();
    float res =imu.getAres();
    result = "acc: " + std::to_string(res * acc[0]) + ", " + std::to_string(res * acc[1]) + ", " + std::to_string(res * acc[2]) + ", " + std::to_string(time);
  }
  else if (command[1] == "gyro")
  {
    int acc[3];
    Timer imu_timer;
    imu_timer.start();
    imu.readGyroData(acc);
    imu_timer.stop();
    uint64_t time = imu_timer.read_us();
    float res =imu.getGres();
    result = "acc: " + std::to_string(res * acc[0]) + ", " + std::to_string(res * acc[1]) + ", " + std::to_string(res * acc[2]) + ", " + std::to_string(time);
  }
  return result;
}

std::string monitorCanCallback(std::vector<std::string> command)
{
  std::string result = "";
  if (command[1] == "tx")
  {
    if(command.size() < 4){
      result += "too few args";
      return result;
    }

    CANMessage can_msg;
    can_msg.format = CANExtended;
    unsigned char target_id = atoi(command[2].c_str()) & 0x7f;
    unsigned char command_id = atoi(command[3].c_str()) & 0x7f;

    base_util.sendCanlink(target_id, command_id, std::vector<unsigned char>{10, 20, 30, 40});
  }
  return result;
}

std::string motorCallback(std::vector<std::string> command)
{
  std::string result = "";
  if (command[1] == "notify")
  {
    if(command.size() == 3){
      printf("notify\n");
      int target = atoi(command[2].c_str());
      if(target == 0) mot0.notify_ = true;
      // else if(target == 1) mot1.notify_ = true;
      // else if(target == 2) mot2.notify_ = true;
      else return result;
      result += "target" + std::to_string(target);
    }
  }
  else if (command[1] == "escape")
  {
    mot0.notify_ = false;
    // mot1.notify_ = false;
    // mot2.notify_ = false;
  }
  else if(command.size() == 3){
    unsigned char va = atoi(command[1].c_str()) & 0x7f;
    unsigned char vb = atoi(command[2].c_str()) & 0x7f;
    // mot1.setPwm((float)va / 256, (float)vb / 256);

    result += "a: " + std::to_string((float)va / 256) + ", ";
    result += "b: " + std::to_string((float)vb / 256);
  }
  else if(command.size() == 2){
    int va = atoi(command[1].c_str());
    mot0.setTarget(va);
    // mot1.setTarget(va);
    // mot2.setTarget(va);
  }
  else{
    result += "too few args";
  }
  return result;
}

void canlinkCommand(CanlinkMsg canlink_msg){
  printf("Message received: s:%d t:%u, c:%u ", canlink_msg.source_id, canlink_msg.target_id, canlink_msg.command_id);
  for(int i =0;i<canlink_msg.len;i++){
    printf("%u ", canlink_msg.data[i]);
  }
  printf("\n");
}

int main()
{
  base_util.registerParam("GAIN_F", 0.00015f);
  base_util.registerParam("GAIN_P", 0.0002f);
  base_util.registerParam("GAIN_I", 0.0005f);
  base_util.loadParam();

  base_util.setCanlinkID(1);
  base_util.registerMonitor("can", monitorCanCallback);
  base_util.registerMonitor("mot", motorCallback);
  base_util.registerMonitor("imu", callback(imuCommand));

  base_util.registerCanlink(2, canlinkCommand);

  auto flag_2hz = base_util.registerTimer(2.0);
  auto flag_50hz = base_util.registerTimer(50.0);
  while (1)
  {
    if(flag_2hz->check()){
      base_util.sendCanlink(2, 10, std::vector<unsigned char>{10, 20, 30, 40});
      base_util.toggleLed(1);

      mot0.print();
      // mot1.print();
      // mot2.print();
      float gain_f = 0;
      base_util.getParam("GAIN_F", gain_f);
      float gain_p = 0;
      base_util.getParam("GAIN_P", gain_p);
      float gain_i = 0;
      base_util.getParam("GAIN_I", gain_i);

      mot0.setParam(gain_f, gain_p, gain_i);
      // mot1.setParam(gain_f, gain_p, gain_i);
      // mot2.setParam(gain_f, gain_p, gain_i);

    }
    if(flag_50hz->check()){
      mot0.control(0.02);
      // mot1.control(0.02);
      // mot2.control(0.02);
    }
    base_util.process();
    thread_sleep_for(10);
  }
}
