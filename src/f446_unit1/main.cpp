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
  float output;
  void print(){
    printf("o: %+5.3f, t: %+7.1f, c: %+7.1f\n", output, target_speed, current_speed);
  }

};

class PwmMotor{
public:
  PwmMotor(PinName p_mot_a, PinName p_mot_b, PinName p_enc_a, PinName p_enc_b): mot_a_(p_mot_a), mot_b_(p_mot_b), enc_a_(p_enc_a), enc_b_(p_enc_b){
    counter_ = 0;
    last_counter_ = 0;
    notify_ = false;

    enc_a_.mode(PullUp);
    enc_b_.mode(PullUp);

    enc_a_.rise([&](){
      if(enc_b_.read())counter_++;
      else counter_--;
    });
    enc_a_.fall([&](){
      if(enc_b_.read())counter_--;
      else counter_++;
    });
    enc_b_.rise([&](){
      if(enc_a_.read())counter_--;
      else counter_++;
    });
    enc_b_.fall([&](){
      if(enc_a_.read())counter_++;
      else counter_--;
    });
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
    float gain_p = 0.001;
    float output = std::min(std::max(- gain_p * diff, -1.0f), 1.0f);
    if(output>0)setPwm(output, 0);
    else setPwm(0, -output);

    result_.target_speed = target_;
    result_.current_speed = (counter_ - last_counter_)  / dt;
    result_.output = output;

    last_counter_ = counter_;
  }
  void print(){
    if(notify_)result_.print();
  }

  ControlStatus result_;
  PwmOut mot_a_;
  PwmOut mot_b_;
  InterruptIn enc_a_;
  InterruptIn enc_b_;
  float target_;
  int counter_;
  int last_counter_;
  bool notify_;
};

PwmMotor mot1(PB_0, PB_1, PC_4, PC_5);


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
    mot1.notify_ = true;
  }
  if (command[1] == "escape")
  {
    mot1.notify_ = false;
  }

  else if(command.size() == 3){
    unsigned char va = atoi(command[1].c_str()) & 0x7f;
    unsigned char vb = atoi(command[2].c_str()) & 0x7f;
    mot1.setPwm((float)va / 256, (float)vb / 256);

    result += "a: " + std::to_string((float)va / 256) + ", ";
    result += "b: " + std::to_string((float)vb / 256);
  }
  else if(command.size() == 2){
    int va = atoi(command[1].c_str());
    mot1.setTarget(va);
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
  base_util.registerParam("PID_P", 0);
  base_util.registerParam("PID_I", 0);
  base_util.registerParam("PID_D", 0);
  base_util.loadParam();

  base_util.setCanlinkID(1);
  base_util.registerMonitor("can", monitorCanCallback);
  base_util.registerMonitor("mot", motorCallback);
  base_util.registerMonitor("imu", callback(imuCommand));

  base_util.registerCanlink(2, canlinkCommand);

  auto flag_2hz = base_util.registerTimer(2.0);
  auto flag_50hz = base_util.registerTimer(50.0);
  int last_counter = 0;
  while (1)
  {
    if(flag_2hz->check()){
      base_util.sendCanlink(2, 10, std::vector<unsigned char>{10, 20, 30, 40});
      base_util.toggleLed(1);

      mot1.print();
    }
    if(flag_50hz->check()){
      mot1.control(0.02);
      last_counter = mot1.counter_;
    }
    base_util.process();
    thread_sleep_for(10);
  }
}
