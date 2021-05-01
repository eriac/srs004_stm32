#include <string>
#include <vector>
#include "ADXL345_I2C.h"
// #include "MPU6050.h"
#include "mbed.h"
#include "base_util.h"
#include "canlink_util.h"
#include "ic_led3.h"


BaseUtil base_util;
ADXL345_I2C accelerometer(PB_11, PB_10);
IcLed3 ic_led3(PA_7, PA_6, PA_5);

void canlinkCommand(CanlinkMsg canlink_msg){
  printf("can rt s:%d t:%u c:%u ", canlink_msg.source_id, canlink_msg.target_id, canlink_msg.command_id);
  for(int i =0;i<canlink_msg.len;i++){
    printf("%u ", canlink_msg.data[i]);
  }
  printf("\n");

  if(canlink_msg.command_id == CANLINK_CMD_LED_COLOR){
    std::vector<unsigned char> data;
    for(int i=0;i<canlink_msg.len;i++)data.push_back(canlink_msg.data[i]);
    
    canlink_util::LedColor led_color;
    led_color.decode(data, canlink_msg.ext_data);
    ic_led3.setBase(led_color.red, led_color.green, led_color.blue);
    printf("ledcolor %u %u %u\n", led_color.red, led_color.green, led_color.blue);
  }
  base_util.toggleLed(2);
}

std::string ledCommand(std::vector<std::string> command)
{
  printf("size: %u\n", command.size());
  std::string result;
  if (command[1] == "color")
  {
    if (command.size() == 5)
    {
      // unsigned char r = std::atoi(command[2].c_str());
      // unsigned char g = std::atoi(command[3].c_str());
      // unsigned char b = std::atoi(command[4].c_str());
      // set_led(r, g, b);
      // result = "color: " + std::to_string(r) + ", " + std::to_string(g) + ", " + std::to_string(b);
      // result = "***";
    }
    else
    {
      result = "command.size must be 5";
    }
  }
  return result;
}

int hit_count = 0;
std::string hitCommand(std::vector<std::string> command)
{
  std::string result = "";
  result += "hit count: " + std::to_string(hit_count) + "\n";
  return result;
}


int main()
{
  base_util.registerMonitor("led", ledCommand);
  base_util.setCanlinkID(CANLINK_NODE_TR1);
  base_util.registerCanlink(CANLINK_CMD_LED_COLOR, canlinkCommand);

  // TAP
  accelerometer.setPowerControl(0x00);
  accelerometer.setDataFormatControl(0x03);
  accelerometer.setDataRate(ADXL345_3200HZ);
  accelerometer.setTapThreshold(0x40);
  accelerometer.setTapDuration(16 * 625);
  accelerometer.setTapAxisControl(0x07);
  accelerometer.setInterruptEnableControl(0x40);
  accelerometer.setPowerControl(0x08);
  thread_sleep_for(10);

  int ret = accelerometer.getDevId();
  printf("id: %i\n", ret);

  auto flag_2hz = base_util.registerTimer(2.0);
  auto flag_5hz = base_util.registerTimer(5.0);
  auto flag_10hz = base_util.registerTimer(10.0);

  ic_led3.setBase(0, 0, 10);

  unsigned long *uid = (unsigned long *)UID_BASE; 
  printf("\r\nUnique ID: %08X %08X %08X %08X\r\n", uid[0], uid[1], uid[2], uid[3]);
  printf("%s %s\n", __DATE__, __TIME__);

  while (true)
  {
    if(flag_2hz->check()){
      base_util.toggleLed(1);

      // heart_beat
      canlink_util::HeartBeat heart_beat;
      heart_beat.mode = canlink_util::HeartBeat::MODE_ACTIVE;
      base_util.sendCanlink(CANLINK_NODE_SH, heart_beat.getID(), heart_beat.getData());

      // board_info
      canlink_util::BoardInfo board_info;
      unsigned long *uid = (unsigned long *)UID_BASE; 
      strncpy((char *)board_info.name, "TR", 2);
      board_info.id = uid[0];
      board_info.revision = 0;
      base_util.sendCanlink(CANLINK_NODE_SH, board_info.getID(), board_info.getData());

    }
    if(flag_5hz->check()){
        canlink_util::TargetStatus target_status;
        target_status.hit_count = hit_count;
        base_util.sendCanlink(CANLINK_NODE_SH, target_status.getID(), target_status.getData());
    }
    if(flag_10hz->check()){
      int readings[3] = { 0, 0, 0 };
      accelerometer.getOutput(readings);
      int source = accelerometer.getInterruptSource();
      if(source & 0x40){
        printf("hit\n");
        ic_led3.setPalse(10, 0, 0);
        hit_count++;
      }
    }
    base_util.process();
    ic_led3.process();
    thread_sleep_for(10);
  }
}
