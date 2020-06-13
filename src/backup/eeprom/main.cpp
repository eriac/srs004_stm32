#include <string>
#include <vector>
#include "ADXL345_I2C.h"
#include "MPU6050.h"
#include "mbed.h"
#include "mon.h"
#include "param.h"

#include "m24c64.h"

DigitalOut myled(PB_3);
Param param;

Mon mon(USBTX, USBRX);
// RawSerial serial(USBTX, USBRX, 115200);

I2CEEprom eeprom;

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

  eeprom.write(1, 0x11);
  eeprom.write(2, 0x22);
  eeprom.write(3, 0x33);

  while (1)
  {
    for (int i = 0; i < 4; i++)
    {
      int x = eeprom.read(i);
      printf("%04x:%02x\n", i, x);
    }
    mon.process();
    myled = !myled;
    thread_sleep_for(250);
  }
}
