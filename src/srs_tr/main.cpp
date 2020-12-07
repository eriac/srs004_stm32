#include <string>
#include <vector>
#include "ADXL345_I2C.h"
// #include "MPU6050.h"
#include "mbed.h"
#include "base_util.h"
#include "canlink_converter.h"
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

  if(canlink_msg.command_id == CANLINK_CMD_ID_LED_COLOR){
    CanlinkConvertor::LedColor led_color;
    led_color.decode(canlink_msg);
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


int main()
{
  base_util.registerMonitor("led", ledCommand);
  base_util.setCanlinkID(2);
  base_util.registerCanlink(10, canlinkCommand);

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
  auto flag_10hz = base_util.registerTimer(10.0);
  int hit_counter = 0;

  ic_led3.setBase(0, 0, 10);

  while (true)
  {
    if(flag_2hz->check()){
      base_util.toggleLed(1);
    }
    if(flag_10hz->check()){
      int readings[3] = { 0, 0, 0 };
      accelerometer.getOutput(readings);
      int source = accelerometer.getInterruptSource();
      if(source & 0x40){
        printf("hit\n");
        ic_led3.setPalse(10, 0, 0);
        
        hit_counter++;
        CanlinkConvertor::TargetStatus target_status;
        target_status.hit_count = hit_counter;
        base_util.sendCanlink(1, target_status.getID(), target_status.encode());
      }
    }
    base_util.process();
    ic_led3.process();
    thread_sleep_for(10);
  }
}
