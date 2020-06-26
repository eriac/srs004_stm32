#include <string>
#include <vector>
#include "ADXL345_I2C.h"
#include "MPU6050.h"
#include "m24c64.h"
#include "mbed.h"
#include "mon.h"
#include "param.h"

DigitalOut myled(PC_13);
Param param;

Mon mon(USBTX, USBRX);
// RawSerial serial(USBTX, USBRX, 115200);

std::string ledCommand(std::vector<std::string> command)
{
  std::string result;
  if (command[1] == "set")
  {
    if (command[2] == "0")
    {
      myled = 0;
      result = "set on";
    }
    else
    {
      myled = 1;
      result = "set off";
    }
  }
  return result;
}

I2CEEprom eeprom;

std::string eepromCommand(std::vector<std::string> command)
{
  std::string result;
  if (command[1] == "clear")
  {
    int page = -1;
    page = std::atoi(command[2].c_str());
    if (0 <= page && page < 256)
    {
      unsigned char data[8] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
      eeprom.write_p(page * 32, data, 8);
      thread_sleep_for(20);
      result = "clear page: " + std::to_string(page);
      ;
    }
  }
  else if (command[1] == "set")
  {
    int page = -1;
    page = std::atoi(command[2].c_str());
    if (0 <= page && page < 256)
    {
      // unsigned char data[8] = { 11, 22, 33, 44, 55, 66, 77, 88 };
      // eeprom.write_p(page * 32, data, 8);
      std::vector<unsigned char> data = { 11, 22, 33, 44, 55, 66, 77, 88 };
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
      // for (int i = 0; i < 8; i++)
      // {
      //   int ret = eeprom.read(page * 32 + i);
      //   result += std::to_string(ret) + " ";
      // }
      std::vector<unsigned char> ret = eeprom.read_page(page);
      for (auto item : ret)
        result += std::to_string(item) + " ";
    }
  }
  return result;
}

// ADXL345_I2C accelerometer(PB_9, PB_8);
// ADD_ALT(SDO) of ADXL345 must be High

int main()
{
  mon.register_func("led", callback(ledCommand));
  // mon.register_func("param", callback(&param, &Param::monCallback));
  mon.register_func("eep", callback(eepromCommand));

  param.register_int("PID_P", 10);
  param.register_int("PID_I", 20);

  thread_sleep_for(100);
  // for (int i = 0; i < 16; i++)
  // {
  //   eeprom.write(100 + i, 0xff);
  //   // thread_sleep_for(10);
  // }
  // for (int i = 0; i < 16; i++)
  // {
  //   eeprom.write(100 + i, i);
  //   // thread_sleep_for(10);
  //   wait_ms(100);
  // }
  unsigned char data[8] = { 10, 20, 30, 40, 50, 60, 70, 80 };
  eeprom.write_p(64, data, 8);
  thread_sleep_for(20);

  unsigned char data2[8] = { 11, 21, 31, 41, 51, 61, 71, 81 };
  eeprom.write_p(64 + 8, data2, 8);

  thread_sleep_for(500);
  // accelerometer.setPowerControl(0x00);
  // accelerometer.setDataFormatControl(0x03);
  // accelerometer.setDataRate(ADXL345_3200HZ);

  // TAP
  // accelerometer.setTapThreshold(0x40);
  // accelerometer.setTapDuration(16 * 625);
  // accelerometer.setTapAxisControl(0x07);
  // accelerometer.setInterruptEnableControl(0x40);

  // accelerometer.setPowerControl(0x08);
  thread_sleep_for(500);

  // int ret = accelerometer.getDevId();
  // mon.serial_.printf("id: %i\n", ret);

  while (1)
  {
    // int readings[3] = { 0, 0, 0 };
    // accelerometer.getOutput(readings);
    // int source = accelerometer.getInterruptSource();
    // mon.serial_.printf("%+04i, %+04i, %+04i %i\n", (int16_t)readings[0], (int16_t)readings[1], (int16_t)readings[2],
    //                    source & 1 << 6);
    // if (source & 1 << 6)
    // {
    //   myled = 0;
    // }
    // else
    // {
    //   myled = 1;
    // }

    unsigned char read[16];
    for (int i = 0; i < 16; i++)
    {
      read[i] = eeprom.read(64 + i);
    }

    // for (int i = 0; i < 16; i++)
    //   printf("%u ", read[i]);
    // printf("\n");

    mon.process();
    thread_sleep_for(100);
  }
}
