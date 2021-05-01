#include <string>
#include <vector>
#include <mbed.h>
// #include "ADXL345_I2C.h"
#include "MPU6050.h"
#include "base_util.h"
#include "canlink_util.h"
#include "pwm_motor.h"

BaseUtil base_util;

MPU6050 imu(PC_9, PA_8);
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
  else if(command.size() == 3 && command[1]=="pwm"){
    int va = atoi(command[2].c_str());
    float pwm = (float)va / 100;
    mot0.setPwmTarget(pwm);
    mot1.setPwmTarget(pwm);
    mot2.setPwmTarget(pwm);
    result += "set pwm " + std::to_string(pwm);
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

  float palse_per_roll = 1600;
  float wheel_radius = 0.019;
  float wheel_base = 0.097;
  float linear_scale = palse_per_roll / (wheel_radius * 2 * M_PI);
  float angular_scale = palse_per_roll * wheel_base / (wheel_radius * 2 * M_PI);

  // linear
  float sp0 = linear_scale * (move_target.vx * cos(M_PI*5/6) + move_target.vy * sin(M_PI*5/6)) + angular_scale * move_target.rate;
  float sp1 = linear_scale * (move_target.vx * cos(M_PI*3/2) + move_target.vy * sin(M_PI*3/2)) + angular_scale * move_target.rate;
  float sp2 = linear_scale * (move_target.vx * cos(M_PI/6) + move_target.vy * sin(M_PI/6)) + angular_scale * move_target.rate;
  printf("%f %f %f\n", sp0, sp1, sp2);
  mot0.setSpeedTarget(-sp0);
  mot1.setSpeedTarget(-sp1);
  mot2.setSpeedTarget(-sp2);
}

void propoStatusCallback(CanlinkMsg canlink_msg){
  std::vector<unsigned char> data;
  for(int i=0;i<canlink_msg.len;i++)data.push_back(canlink_msg.data[i]);
  canlink_util::PropoStatus propo_status;
  propo_status.decode(data, canlink_msg.ext_data);
  // printf("%s\n", propo_status.getStr().c_str());

  float sp0 = propo_status.x * cos(M_PI*5/6) + propo_status.y * sin(M_PI*5/6);
  float sp1 = propo_status.x * cos(M_PI*3/2) + propo_status.y * sin(M_PI*3/2);
  float sp2 = propo_status.x * cos(M_PI/6) + propo_status.y * sin(M_PI/6);
  printf("%f %f %f\n", sp0, sp1, sp2);
  mot0.setSpeedTarget(-sp0*1600);
  mot1.setSpeedTarget(-sp1*1600);
  mot2.setSpeedTarget(-sp2*1600);
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

  float x = 0.0f;
  float y = 0.0f;
  float th = 0.0f;
  thread_sleep_for(100);

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

      // heart_beat
      canlink_util::HeartBeat heart_beat;
      heart_beat.mode = canlink_util::HeartBeat::MODE_ACTIVE;
      base_util.sendCanlink(CANLINK_NODE_SH, heart_beat.getID(), heart_beat.getData());

      // board_info
      canlink_util::BoardInfo board_info;
      unsigned long *uid = (unsigned long *)UID_BASE; 
      strncpy((char *)board_info.name, "WL", 2);
      board_info.id = uid[0];
      board_info.revision = 0;
      base_util.sendCanlink(CANLINK_NODE_SH, board_info.getID(), board_info.getData());
    }
    if(flag_50hz->check()){
      int diff0 = -mot0.control(0.02);
      int diff1 = -mot1.control(0.02);
      int diff2 = -mot2.control(0.02);

      float palse_per_roll = 1600;
      float wheel_radius = 0.019;
      float wheel_base = 0.097;
      float linear_scale = palse_per_roll / (wheel_radius * 2 * M_PI);
      float angular_scale = palse_per_roll * wheel_base / (wheel_radius * 2 * M_PI);
      float dx_r = 1/(3*linear_scale)*(diff0*2*cos(M_PI*5/6) + diff1*2*cos(M_PI*3/2) + diff2*2*cos(M_PI*1/6));
      float dy_r = 1/(3*linear_scale)*(diff0*2*sin(M_PI*5/6) + diff1*2*sin(M_PI*3/2) + diff2*2*sin(M_PI*1/6));
      float dt_r = 1/(3*angular_scale)*(diff0 + diff1 + diff2);
      // printf("diff %+6.3f %+6.3f %+6.3f\n", dx_r/0.02, dy_r/0.02, dt_r/0.02);

      //update
      float local_dx = dx_r * cos(th + dt_r/2) - dy_r * sin(th + dt_r/2);
      float local_dy = dx_r * sin(th + dt_r/2) + dy_r * cos(th + dt_r/2);
      // printf("diff %+7.3f %+7.3f %+7.3f\n", local_dx*50, local_dy*50, dt_r*50);
      
      x += local_dx;
      y += local_dy;
      th += dt_r;
      // printf("diff %+7.3f %+7.3f %+7.3f\n", x, y, th);

      canlink_util::LocalVelocity local_velocity;
      local_velocity.x = local_dx * 50.0;
      local_velocity.y = local_dy * 50.0;
      local_velocity.theta = dt_r * 50.0;
      base_util.sendCanlink(CANLINK_NODE_SH, local_velocity.getID(), local_velocity.getData());

      canlink_util::LocalPosition local_position;
      local_position.x = x;
      local_position.y = y;
      local_position.theta = th;
      base_util.sendCanlink(CANLINK_NODE_SH, local_position.getID(), local_position.getData());
    }
    base_util.process();
    thread_sleep_for(1);
  }
}
