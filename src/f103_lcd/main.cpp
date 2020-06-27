#include <string>
#include <vector>
// #include "ADXL345_I2C.h"
// #include "MPU6050.h"
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

#include "Adafruit_SSD1306.h"

I2C i2c(PB_9, PB_8);

uint8_t i2cAddress = SSD_I2C_ADDRESS;
uint8_t rawHeight = 64;
uint8_t rawWidth = 128;
Adafruit_SSD1306_I2c oled(i2c, D10, i2cAddress, rawHeight, rawWidth);

void print(std::string str)
{
  for (size_t i = 0; i < str.size(); i++)
  {
    oled._putc(str[i]);
  }
  oled.display();
}

int main()
{
  thread_sleep_for(100);

  mon.register_func("led", callback(ledCommand));
  // mon.register_func("param", callback(&param, &Param::monCallback));

  param.register_int("PID_P", 10);
  param.register_int("PID_I", 20);
  param.register_int("PID_D", 1);

  oled.setTextCursor(20,40);
  print("hello");

  while (1)
  {
    mon.process();
    thread_sleep_for(100);
  }
}
