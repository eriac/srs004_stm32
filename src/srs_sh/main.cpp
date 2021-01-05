#include <string>
#include <vector>
#include "mbed.h"
#include "base_util.h"
#include "sbus2.h"
#include "canlink_util.h"
#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Int32.h>
#include <std_msgs/ColorRGBA.h>
#include <geometry_msgs/TwistStamped.h>
#include <s4_msgs/JoyPropo.h>
#include <s4_msgs/OdometryLite2D.h>

BaseUtil base_util;

class SerialAdapter{
public:
  SerialAdapter(PinName td, PinName rd): serial_(td, rd, 1000000){
    serial_.attach(callback(this, &SerialAdapter::rxCallback));
    frame_valid_ = false;
  }
  void output(std::string code){
    event_callback_t callback;
    // std::string serial_code = code+"\n";
    // serial_.write((uint8_t *)serial_code.c_str(), serial_code.size(), callback); 
    serial_.printf("%s\n", code.c_str());
  }
  void registerCallback(Callback<void(std::string)> func){
    callback_ = func;
  }
  void rxCallback(void){
    char recv = serial_.getc();
    if(!frame_valid_){
      if(recv=='$'){
        frame_valid_=true;
      }
    }
    else{
      if(recv=='\n'){
        //ok
      }
      else if(true){
        //add
      } 
    }

    // serial_.putc(recv);
    // if(recv=='a'){
    //   base_util.toggleLed(2);
    // }
    // printf("recv: %c\n", recv);
  }

  RawSerial serial_;
  Callback<void(std::string)> callback_;
  bool frame_valid_;
  unsigned char buffer[64];
  int size_;
  int max_size_{64};
};

class mySTM32 : public MbedHardware
{
public:
  mySTM32(): MbedHardware(PA_0, PA_1, 57600) {}; 
};
ros::NodeHandle_<mySTM32> nh;

std_msgs::String str_msg;
ros::Publisher chatter("chatter", &str_msg);

std_msgs::Int32 int_msg;
ros::Publisher target_pub("target_status", &int_msg);

s4_msgs::JoyPropo joy_propo_msg;
ros::Publisher joy_propo_pub("joy_propo", &joy_propo_msg);

s4_msgs::OdometryLite2D odom_2d_msg;
ros::Publisher odom_2d_pub("omni_cart/odom2d", &odom_2d_msg);

void setLedCb(const std_msgs::ColorRGBA& color_msg){
  canlink_util::LedColor led_color;
  led_color.set_mode = canlink_util::LedColor::SET_BASE_COLOR;
  led_color.red = color_msg.r*255;
  led_color.green = color_msg.g*255;
  led_color.blue = color_msg.b*255;
  base_util.sendCanlink(CANLINK_NODE_TR1, led_color.getID(), led_color.getData());
}
ros::Subscriber<std_msgs::ColorRGBA> set_led_sub("set_led", &setLedCb);

void cmdVelCb(const geometry_msgs::TwistStamped& twist_msg){
  canlink_util::MoveTarget move_target;
  move_target.vx = twist_msg.twist.linear.x;
  move_target.vy = twist_msg.twist.linear.y;
  move_target.rate = twist_msg.twist.angular.z;
  base_util.sendCanlink(CANLINK_NODE_WL, move_target.getID(), move_target.getData());
}
ros::Subscriber<geometry_msgs::TwistStamped> cmd_vel_sub("omni_cart/cmd_vel", &cmdVelCb);

void targetStatusCommand(CanlinkMsg canlink_msg){
  std::vector<unsigned char> data;
  for(int i=0;i<canlink_msg.len;i++)data.push_back(canlink_msg.data[i]);
  canlink_util::TargetStatus target_status;
  target_status.decode(data, canlink_msg.ext_data);
  int_msg.data = target_status.hit_count;
  target_pub.publish(&int_msg);
}

void localPositionCommand(CanlinkMsg canlink_msg){
  std::vector<unsigned char> data;
  for(int i=0;i<canlink_msg.len;i++)data.push_back(canlink_msg.data[i]);
  canlink_util::LocalPosition local_position;
  local_position.decode(data, canlink_msg.ext_data);
  // int_msg.data = target_status.hit_count;
  // target_pub.publish(&int_msg);
  odom_2d_msg.pose.x = local_position.x;
  odom_2d_msg.pose.y = local_position.y;
  odom_2d_msg.pose.theta = local_position.theta;
  odom_2d_pub.publish(&odom_2d_msg);
}

Sbus2Receiver sbus2(PC_10, PC_11);

int main()
{
  base_util.registerParam("GAIN_F", 0.00015f);
  base_util.registerParam("GAIN_P", 0.0002f);
  base_util.registerParam("GAIN_I", 0.0010f);
  base_util.loadParam();

  base_util.setCanlinkID(1);
  // base_util.registerMonitor("can", monitorCanCallback);
  // base_util.registerMonitor("mot", motorCallback);
  // base_util.registerMonitor("imu", callback(imuCommand));

  base_util.registerCanlink(CANLINK_CMD_TARGET_STATUS, targetStatusCommand);
  base_util.registerCanlink(CANLINK_CMD_LOCAL_POSITION, localPositionCommand);

  // rosserial
	nh.initNode();
  nh.advertise(chatter);
  nh.advertise(target_pub);
  nh.advertise(joy_propo_pub);
  nh.advertise(odom_2d_pub);
  nh.subscribe(set_led_sub);
  nh.subscribe(cmd_vel_sub);

  auto flag_2hz = base_util.registerTimer(2.0);
  auto flag_50hz = base_util.registerTimer(50.0);
  while (1)
  {
    if(flag_2hz->check()){
      // printf("2hz\n");
      base_util.toggleLed(1);
      str_msg.data = "hello rosserial";
      chatter.publish( &str_msg );
    }
    if(flag_50hz->check()){
      if(sbus2.checkUpdate()){
        // printf("sbus2\n");
        // printf(" 0ch: %04u,  1ch: %04u,  2ch: %04u,  3ch: %04u\n", sbus2.getCh(0), sbus2.getCh(1), sbus2.getCh(2), sbus2.getCh(3));
        // printf(" 4ch: %04u,  5ch: %04u,  6ch: %04u,  7ch: %04u\n", sbus2.getCh(4), sbus2.getCh(5), sbus2.getCh(6), sbus2.getCh(7));

        joy_propo_msg.x = -(float)((int)sbus2.getCh(1)-1024)/656.0;
        joy_propo_msg.y = -(float)((int)sbus2.getCh(3)-1024)/656.0;
        joy_propo_msg.z = -(float)((int)sbus2.getCh(2)-1024)/656.0;
        joy_propo_msg.r = -(float)((int)sbus2.getCh(0)-1024)/656.0;
        auto getPosition=[&](float value)->int{
          int output = 0;
          if(value<584){
            output = s4_msgs::JoyPropo::SW_OFF;
          }
          else if(value<1464){
            output = s4_msgs::JoyPropo::SW_MID;
          }
          else{
            output = s4_msgs::JoyPropo::SW_ON;
          }
          return output;
        };
        joy_propo_msg.sw_a = getPosition(sbus2.getCh(4));
        joy_propo_msg.sw_b = getPosition(sbus2.getCh(5));
        joy_propo_msg.sw_c = getPosition(sbus2.getCh(6));
        joy_propo_msg.sw_d = getPosition(sbus2.getCh(7));
        joy_propo_pub.publish(&joy_propo_msg);

        if(joy_propo_msg.sw_d == s4_msgs::JoyPropo::SW_ON){
          // canlink_util::PropoStatus propo_status;
          // propo_status.x = joy_propo_msg.x;
          // propo_status.y = joy_propo_msg.y;
          // propo_status.z = joy_propo_msg.z;
          // propo_status.r = joy_propo_msg.r;
          // propo_status.sw_a = joy_propo_msg.sw_a;
          // propo_status.sw_b = joy_propo_msg.sw_b;
          // propo_status.sw_c = joy_propo_msg.sw_c;
          // propo_status.sw_d = joy_propo_msg.sw_d;
          // base_util.sendCanlink(CANLINK_NODE_WL, propo_status.getID(), propo_status.getData());
          canlink_util::MoveTarget move_target;
          move_target.vx = 0.2 * joy_propo_msg.x;
          move_target.vy = 0.2 * joy_propo_msg.y;
          move_target.rate = 1.0 * joy_propo_msg.r;
          base_util.sendCanlink(CANLINK_NODE_WL, move_target.getID(), move_target.getData());

          base_util.turnOnLed(2);
        }
        else{
          base_util.turnOffLed(2);
        }
      }
      if(sbus2.checkLost()){
        printf("sbus2 lost\n");
      }
    }
    nh.spinOnce();
    base_util.process();
    thread_sleep_for(1);
  }
}
