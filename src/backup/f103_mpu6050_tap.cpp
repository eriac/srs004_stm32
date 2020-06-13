#include <string>
#include <vector>
#include "ADXL345_I2C.h"
#include "MPU6050.h"
#include "mbed.h"
#include "mon.h"
#include "param.h"

DigitalOut myled(PB_3);
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

ADXL345_I2C accelerometer(PB_9, PB_8);
// ADD_ALT(SDO) of ADXL345 must be High

int main()
{
  mon.register_func("led", callback(ledCommand));
  mon.register_func("param", callback(&param, &Param::monCallback));

  param.register_int("PID_P", 10);
  param.register_int("PID_I", 20);

  thread_sleep_for(500);
  accelerometer.setPowerControl(0x00);
  accelerometer.setDataFormatControl(0x03);
  accelerometer.setDataRate(ADXL345_3200HZ);

  // TAP
  accelerometer.setTapThreshold(0x40);
  accelerometer.setTapDuration(16 * 625);
  accelerometer.setTapAxisControl(0x07);
  accelerometer.setInterruptEnableControl(0x40);

  accelerometer.setPowerControl(0x08);
  thread_sleep_for(500);

  int ret = accelerometer.getDevId();
  mon.serial_.printf("id: %i\n", ret);

  while (1)
  {
    int readings[3] = { 0, 0, 0 };
    accelerometer.getOutput(readings);
    int source = accelerometer.getInterruptSource();
    // mon.serial_.printf("%+04i, %+04i, %+04i %i\n", (int16_t)readings[0], (int16_t)readings[1], (int16_t)readings[2],
    //                    source & 1 << 6);

    if (source & 1 << 6)
    {
      myled = 0;
    }
    else
    {
      myled = 1;
    }
    mon.process();
    thread_sleep_for(100);
  }
}
