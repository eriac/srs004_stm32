#include <string>
#include <vector>
#include "ADXL345_I2C.h"
#include "MPU6050.h"
#include "mbed.h"
#include "mon.h"
#include "param.h"


DigitalOut myled(PC_13);
Param param;

Mon mon(USBTX, USBRX);
// RawSerial serial(USBTX, USBRX, 115200);
SPI cled(PB_5, PB_4, PB_3);

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

int main()
{
  mon.register_func("led", callback(ledCommand));
  mon.register_func("param", callback(&param, &Param::monCallback));

  param.register_int("PID_P", 10);
  param.register_int("PID_I", 20);

  cled.frequency(4000000);
  while (1)
  {
    mon.process();
    myled = !myled;
    thread_sleep_for(500);
    cled.write(0x90);
    cled.write(0x90);
    cled.write(0x90);
  }
}