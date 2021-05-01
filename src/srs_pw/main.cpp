#include <string>
#include <vector>
#include <chrono>
#include <ctime>
#include "ADXL345_I2C.h"
// #include "MPU6050.h"
#include "mbed.h"
#include "base_util.h"
#include "canlink_util.h"
#include "ic_led3.h"

AnalogIn adc_wall(PA_4);
AnalogIn adc_bat1(PA_5);
AnalogIn adc_bat2(PA_6);

DigitalIn in_wall_v(PA_4);
DigitalIn in_bat1_v(PA_5);
DigitalIn in_bat2_v(PA_6);

DigitalIn in_bat1_fault(PB_0);
DigitalIn in_bat1_status(PB_1);

BaseUtil base_util;

float wall_v = 0.0;
float bat1_v = 0.0;
float bat2_v = 0.0;
bool bat1_en = false;
bool bat2_en = false;

std::string batCommand(std::vector<std::string> command)
{
  std::string result;
  result += "wall: " + std::to_string(wall_v) + " V\n";
  result += "bat1: " + std::to_string(bat1_v) + " V " + (bat1_en ? "[ON]" : "[OFF]") + "\n";
  result += "bat2: " + std::to_string(bat2_v) + " V " + (bat2_en ? "[ON]" : "[OFF]") + "\n";
  return result;
}

int main()
{
  base_util.registerMonitor("bat", batCommand);
  base_util.setCanlinkID(CANLINK_NODE_PW);

  auto flag_2hz = base_util.registerTimer(2.0);
  auto flag_10hz = base_util.registerTimer(10.0);

  in_wall_v.mode(PullNone);
  in_bat1_v.mode(PullNone);
  in_bat2_v.mode(PullNone);
  in_bat1_fault.mode(PullUp);
  in_bat1_status.mode(PullUp);

  thread_sleep_for(200);

  unsigned long *uid = (unsigned long *)UID_BASE; 
  printf("\r\nUnique ID: %08X %08X %08X %08X\r\n", uid[0], uid[1], uid[2], uid[3]);
  printf("%s %s\n", __DATE__, __TIME__);

  Timer timer0;
  timer0.start();
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
      strncpy((char *)board_info.name, "PW", 2);
      board_info.id = uid[0];
      board_info.revision = 0;
      base_util.sendCanlink(CANLINK_NODE_SH, board_info.getID(), board_info.getData());

      // power_status
      canlink_util::PowerStatus power_status;
      if(bat1_en){
        power_status.source = canlink_util::PowerStatus::SOURCE_BATTERY1;
        power_status.system_remain_percent = 50;
      }
      else if(bat2_en){
        power_status.source = canlink_util::PowerStatus::SOURCE_BATTERY2;
        power_status.system_remain_percent = 60;
      }
      else{
        power_status.source = canlink_util::PowerStatus::SOURCE_WALL;
        power_status.system_remain_percent = 70;
      }
      power_status.voltage_wall_mv = wall_v * 1000;
      power_status.voltage_bat1_mv = bat1_v * 1000;
      power_status.voltage_bat2_mv = bat2_v * 1000;
      base_util.sendCanlink(CANLINK_NODE_SH, power_status.getID(), power_status.getData());
    }
    if(flag_10hz->check()){
      float adc0 = adc_wall * 3.3 * 110 / 5.1; 
      float adc1 = adc_bat1 * 3.3 * 110 / 5.1; 
      float adc2 = adc_bat2 * 3.3 * 110 / 5.1; 
      unsigned int bat1_f = in_bat1_fault;
      unsigned int bat1_s = in_bat1_status;

      wall_v = 0.0;

      float bat1_rate = fabs(bat1_v - adc1) < 1.0 ? 0.1 : 0.7;
      bat1_v = (1 - bat1_rate) * bat1_v + bat1_rate * adc1;
      bat1_en = ! bat1_s;

      bat2_v = 0.0;
      bat2_en = false;
    }
    base_util.process();
    thread_sleep_for(10);
  }
}
