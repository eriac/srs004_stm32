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

union param_value {
  struct int_value_t
  {
    int data;
    unsigned char rest[4];
  } int_value;
  struct float_value_t
  {
    float data;
    unsigned char rest[4];
  } float_value;
  unsigned char char_value[8];
};

enum class param_type : unsigned char
{
  TYPE_NONE,
  TYPE_INT,
  TYPE_FLOAT,
  TYPE_STRING
};

struct param_item
{
  param_type type;
  char name[7];
  union param_value value;
};

union param_union {
  param_item param[2];
  unsigned char byte[32];
};

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
    int page = -1;
    page = std::atoi(command[2].c_str());
    if (0 <= page && page < 256)
    {
      std::vector<unsigned char> data;
      for (int i = 0; i < 32; i++)
        data.push_back(0xff);
      eeprom.write_page(page, data);
      thread_sleep_for(20);
      result = "clear page: " + std::to_string(page);
    }
  }
  else if (command[1] == "set")
  {
    int page = -1;
    page = std::atoi(command[2].c_str());
    if (0 <= page && page < 256)
    {
      std::vector<unsigned char> data;
      for (int i = 0; i < 32; i++)
        data.push_back(100 + i);
      eeprom.write_page(page, data);
      thread_sleep_for(20);
      result = "set page: " + std::to_string(page);
    }
  }
  else if (command[1] == "read")
  {
    int page = -1;
    page = std::atoi(command[2].c_str());
    if (0 <= page && page < 256)
    {
      result = "read page[" + std::to_string(page) + "] ";
      std::vector<unsigned char> ret = eeprom.read_page(page, 32);
      for (auto item : ret)
        result += std::to_string(item) + " ";
    }
  }
  else if (command[1] == "store")
  {
    param_union page0;
    strncpy(page0.param[0].name, "abcd", 8);
    page0.param[0].type = param_type::TYPE_INT;
    page0.param[0].value.int_value.data = 30;
    strncpy(page0.param[1].name, "xyz", 8);
    page0.param[1].type = param_type::TYPE_FLOAT;
    page0.param[1].value.float_value.data = 12.345;
    result = "store: ";
    std::vector<unsigned char> data;
    for (int i = 0; i < 32; i++)
    {
      data.push_back(page0.byte[i]);
      result += std::to_string(page0.byte[i]) + ", ";
    }
    eeprom.write_page(0, data);
    thread_sleep_for(20);
  }
  else if (command[1] == "load")
  {
    int page = -1;
    std::vector<unsigned char> data = eeprom.read_page(0, 32);
    param_union page0;
    result = "load: ";
    for (int i = 0; i < 32; i++)
    {
      page0.byte[i] = data[i];
      result += std::to_string(data[i]) + ", ";
    }

    for (int i = 0; i < 2; i++)
    {
      if (page0.param[i].type == param_type::TYPE_INT)
        result += std::string(page0.param[i].name) + " INT: " + std::to_string(page0.param[i].value.int_value.data);
      else if (page0.param[i].type == param_type::TYPE_FLOAT)
        result += std::string(page0.param[i].name) + " FLOAT: " + std::to_string(page0.param[i].value.float_value.data);
      else
        result += "OTHER:" + std::to_string((int)(page0.param[i].type));
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

  param.register_int("PID_P", 10);
  param.register_int("PID_I", 20);
  param.register_int("PID_D", 1);

  fled.format(8, 3);
  fled.frequency(8000000);

  while (1)
  {
    mon.process();
    led1 = !led1;
    thread_sleep_for(100);
  }
}
