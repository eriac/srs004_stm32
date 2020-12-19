#include <string>
#include <vector>
// #include "ADXL345_I2C.h"
#include "MPU6050.h"
#include "mbed.h"
#include "base_util.h"
#include "canlink_util.h"

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
    mode_ = Mode::FREE;

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

  void setSpeedTarget(float target){
    mode_=Mode::SPEED;
    target_speed_ = target;
  }
  void setPwmTarget(float target){
    
  }
  void setFree(){
    
  }
  void setTarget(float target){
  }

  void control(float dt){
    float diff = (counter_ - last_counter_) / dt - target_speed_;
    result_.iterm = result_.iterm + diff * dt;
    float output_raw = param_.f * target_speed_ - param_.p * diff - param_.i * result_.iterm;
    float output = std::min(std::max(output_raw, -1.0f), 1.0f);
    if(output>0){
      mot_a_ = output;
      mot_b_ = 0;
    }
    else{
      mot_a_ = 0;
      mot_b_ = -output;
    }

    result_.target_speed = target_speed_;
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
  float target_speed_;
  int counter_;
  int last_counter_;
  bool notify_;
  enum class Mode{FREE, PWM, SPEED} mode_;
};

PwmMotor mot0(PA_6, PA_7, PA_0, PA_1);
PwmMotor mot1(PB_0, PB_1, PC_4, PC_5);
PwmMotor mot2(PB_8, PB_9, PD_2, PB_3);

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
  if (command.size() == 3 && command[1] == "notify")
  {
    printf("notify\n");
    int target = atoi(command[2].c_str());
    if(target == 0) mot0.notify_ = true;
    // else if(target == 1) mot1.notify_ = true;
    // else if(target == 2) mot2.notify_ = true;
    else return result;
    result += "target" + std::to_string(target);
  }
  else if (1<=command.size() && command[1] == "escape")
  {
    mot0.notify_ = false;
    // mot1.notify_ = false;
    // mot2.notify_ = false;
  }
  else if(command.size() == 3 && command[1]=="speed"){
    int va = atoi(command[2].c_str());
    mot0.setSpeedTarget(va);
    mot1.setSpeedTarget(va);
    mot2.setSpeedTarget(va);
    result += "set speed " + std::to_string(va);
  }
  else if(command.size() == 2){
  }
  else{
    result += "too few args";
  }
  return result;
}

void moveTargetCallback(CanlinkMsg canlink_msg){
  // printf("Message received: s:%d t:%u, c:%u ", canlink_msg.source_id, canlink_msg.target_id, canlink_msg.command_id);
  // for(int i =0;i<canlink_msg.len;i++){
  //   printf("%u ", canlink_msg.data[i]);
  // }
  // base_util.toggleLed(2);
  // printf("\n");
  std::vector<unsigned char> data;
  for(int i=0;i<canlink_msg.len;i++)data.push_back(canlink_msg.data[i]);
  canlink_util::MoveTarget move_target;
  move_target.decode(data, canlink_msg.ext_data);
  printf("move_target: %f %f %f\n", move_target.vx, move_target.vy, move_target.rate);
}

void propoStatusCallback(CanlinkMsg canlink_msg){
  std::vector<unsigned char> data;
  for(int i=0;i<canlink_msg.len;i++)data.push_back(canlink_msg.data[i]);
  canlink_util::PropoStatus propo_status;
  propo_status.decode(data, canlink_msg.ext_data);
  printf("%s\n", propo_status.getStr().c_str());
}

int main()
{
  base_util.registerParam("GAIN_F", 0.00015f);
  base_util.registerParam("GAIN_P", 0.0002f);
  base_util.registerParam("GAIN_I", 0.0010f);
  base_util.loadParam();

  base_util.setCanlinkID(CANLINK_NODE_WL); // 3
  base_util.registerMonitor("can", monitorCanCallback);
  base_util.registerMonitor("mot", motorCallback);
  base_util.registerMonitor("imu", callback(imuCommand));

  base_util.registerCanlink(CANLINK_CMD_MOVE_TARGET, moveTargetCallback);
  base_util.registerCanlink(CANLINK_CMD_PROPO_STATUS, propoStatusCallback);

  auto flag_2hz = base_util.registerTimer(2.0);
  auto flag_50hz = base_util.registerTimer(50.0);
  while (1)
  {
    if(flag_2hz->check()){
      base_util.sendCanlink(2, 10, std::vector<unsigned char>{10, 20, 30, 40});
      base_util.toggleLed(1);

      mot0.print();
      mot1.print();
      mot2.print();
      float gain_f = 0;
      base_util.getParam("GAIN_F", gain_f);
      float gain_p = 0;
      base_util.getParam("GAIN_P", gain_p);
      float gain_i = 0;
      base_util.getParam("GAIN_I", gain_i);

      mot0.setParam(gain_f, gain_p, gain_i);
      mot1.setParam(gain_f, gain_p, gain_i);
      mot2.setParam(gain_f, gain_p, gain_i);

    }
    if(flag_50hz->check()){
      mot0.control(0.02);
      mot1.control(0.02);
      mot2.control(0.02);
    }
    base_util.process();
    thread_sleep_for(10);
  }
}
