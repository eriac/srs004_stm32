#include <string>
#include <vector>
// #include "ADXL345_I2C.h"
// #include "MPU6050.h"
#include "m24c64.h"
#include "mbed.h"
#include "mon.h"
#include "param.h"

DigitalOut myled(PC_13);
DigitalOut led1(PB_12);
DigitalOut led2(PB_13);
Param param;

#define EEPROM_MAX_PAGE 4

SPI fled(PA_7, PA_6, PA_5);

void set_led(unsigned char red, unsigned char green, unsigned char blue)
{
  char tx_data[24] = { 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f,
                       0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f };
  char rx_data[24];

  for (int i = 0; i < 8; i++)
    if (green & 1 << (7 - i))
      tx_data[i] = 0x03;
  for (int i = 0; i < 8; i++)
    if (red & 1 << (7 - i))
      tx_data[i + 8] = 0x03;
  for (int i = 0; i < 8; i++)
    if (blue & 1 << (7 - i))
      tx_data[i + 16] = 0x03;

  fled.write(tx_data, 24, rx_data, 24);
}

Mon mon(USBTX, USBRX);
// RawSerial serial(USBTX, USBRX, 115200);


std::string ledCommand(std::vector<std::string> command)
{
  std::string result;
  if (command[1] == "set")
  {
    if (command[2] == "0")
    {
      led2 = 0;
      result = "set off";
    }
    else
    {
      led2 = 1;
      result = "set on";
    }
  }

  if (command[1] == "color")
  {
    if (command.size() == 5)
    {
      unsigned char r = std::atoi(command[2].c_str());
      unsigned char g = std::atoi(command[3].c_str());
      unsigned char b = std::atoi(command[4].c_str());
      set_led(r, g, b);
      result = "color: " + std::to_string(r) + ", " + std::to_string(g) + ", " + std::to_string(b);
    }
    else
    {
      result = "command.size must be 5";
    }
  }

  return result;
}

I2C i2c0(PB_7, PB_6);
I2CEEprom eeprom(i2c0);

std::string eepromCommand(std::vector<std::string> command)
{
  std::string result;
  if (command[1] == "clear")
  {
    for(int i = 0; i < EEPROM_MAX_PAGE; i++){
      eeprom.clear_page(i);
    }
  }
  else if (command[1] == "store")
  {
    unsigned int index = 0;
    param_union pages[EEPROM_MAX_PAGE];
    for(auto item : param.int_param_){
      int page = index / 2;
      int side = index % 2;
      auto& target_side = pages[page].param[side];
      strncpy(target_side.name, item.first.c_str(), 7);
      target_side.type = param_type::TYPE_INT;
      target_side.value.int_value.data = item.second;        
      index ++;
      if(index / 2 == EEPROM_MAX_PAGE)break;
    }
    for(int i = 0; i < EEPROM_MAX_PAGE; i++){
      eeprom.write_page(i, pages[i]);
      thread_sleep_for(20);
    }
  }
  else if (command[1] == "load")
  {
    param_union pages[EEPROM_MAX_PAGE];
    for(int i = 0; i < EEPROM_MAX_PAGE; i++){
      pages[i] = eeprom.read_page(i);
    }

    for(int index = 0; index < EEPROM_MAX_PAGE * 2; index++){
      int page = index / 2;
      int side = index % 2;
      auto& target_side = pages[page].param[side];
      if (target_side.type == param_type::TYPE_INT){
        param.update_int(target_side.name, target_side.value.int_value.data);
        result += std::string(target_side.name) + " INT: " + std::to_string(target_side.value.int_value.data)+"\n";
      }
      else if (target_side.type == param_type::TYPE_FLOAT)
        result += std::string(target_side.name) + " FLOAT: " + std::to_string(target_side.value.float_value.data)+"\n";
      else
        result += "OTHER:" + std::to_string((int)(target_side.type))+"\n";
    }
  }
  return result;
}

// ADXL345_I2C accelerometer(PB_9, PB_8);
// ADD_ALT(SDO) of ADXL345 must be High

int main()
{
  thread_sleep_for(100);

  mon.register_func("led", callback(ledCommand));
  mon.register_func("param", callback(&param, &Param::monCallback));
  mon.register_func("eep", callback(eepromCommand));

  param.register_int("PID_P", 0);
  param.register_int("PID_I", 0);
  param.register_int("PID_D", 0);
  param.register_int("PID_2", 0);
  param.register_int("PID_3", 0);

  fled.format(8, 3);
  fled.frequency(8000000);

  while (1)
  {
    mon.process();
    led1 = !led1;
    thread_sleep_for(100);
  }
}
