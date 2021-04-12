#include <string>
#include <vector>
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
// ADXL345_I2C accelerometer(PB_11, PB_10);
// IcLed3 ic_led3(PA_7, PA_6, PA_5);

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
    // ic_led3.setBase(led_color.red, led_color.green, led_color.blue);
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
  base_util.setCanlinkID(10);
  base_util.registerCanlink(10, canlinkCommand);

  auto flag_2hz = base_util.registerTimer(2.0);
  auto flag_10hz = base_util.registerTimer(10.0);

  in_wall_v.mode(PullNone);
  in_bat1_v.mode(PullNone);
  in_bat2_v.mode(PullNone);
  in_bat1_fault.mode(PullUp);
  in_bat1_status.mode(PullUp);

  thread_sleep_for(200);

  while (true)
  {
    if(flag_2hz->check()){
      base_util.toggleLed(1);

      canlink_util::LedColor led_color;
      led_color.set_mode = canlink_util::LedColor::SET_BASE_COLOR;
      led_color.red = 0;
      led_color.green = 10;
      led_color.blue = 0;

      static int counter = 0;
      counter++;
      if(counter % 4 == 0){
        led_color.red = 0;
        led_color.green = 0;
        led_color.blue = 10;
      }
      else if(counter % 4 == 2){
        led_color.red = 0;
        led_color.green = 10;
        led_color.blue = 10;
      }
      base_util.sendCanlink(2, led_color.getID(), led_color.getData());
    }
    if(flag_10hz->check()){
      float adc0 = adc_wall * 3.3 * 110 / 5.1; 
      float adc1 = adc_bat1 * 3.3 * 110 / 5.1; 
      float adc2 = adc_bat2 * 3.3 * 110 / 5.1; 
      unsigned int bat1_f = in_bat1_fault;
      unsigned int bat1_s = in_bat1_status;

      static float adc1_avr = 0.0;
      float rate = 0.1;
      if(1.0 < fabs(adc1_avr - adc1))rate = 0.7;
      adc1_avr = (1 - rate) * adc1_avr + rate * adc1;

      // printf("adc %f %f %f %u %u\n", adc0, adc1, adc2, bat1_f, bat1_s);

      // printf("adc %05x %05x %05x\n", adc_wall.read_u16(), adc_bat1.read_u16(), adc_bat2.read_u16());
    }
    base_util.process();
    thread_sleep_for(10);
  }
}
