#include "mbed.h"
#include "mon.h"

#include <string>
#include <vector>
#include "MPU6050.h"
#include "m24c64.h"
#include "mbed.h"
#include "param.h"

DigitalOut led0(PB_12);
DigitalOut led1(PB_13);
DigitalIn in0(PA_4);
DigitalIn in1(PA_5);
PwmOut out0(PA_6);
PwmOut out1(PA_7);

Mon mon(USBTX, USBRX);

std::string motCommand(std::vector<std::string> command)
{
  std::string result;
  if (command[1] == "set")
  {
    int speed = std::atoi(command[2].c_str());
    if (speed > 0)
    {
      out0 = 0;
      out1 = (float)speed / 256;
    }
    else
    {
      out0 = -(float)speed / 256;
      out1 = 0;
    }
  }
  return result;
}

MPU6050 imu(PC_9, PA_8);

std::string imuCommand(std::vector<std::string> command)
{
  std::string result;
  if (command[1] == "acc")
  {
    int acc[3];
    imu.readAccelData(acc);
    result = "acc: " + std::to_string(acc[0]) + ", " + std::to_string(acc[1]) + ", " + std::to_string(acc[2]);
  }
  return result;
}

int main()
{
  in0.mode(PullUp);
  in1.mode(PullUp);
  mon.register_func("mot", callback(motCommand));
  mon.register_func("imu", callback(imuCommand));
  while (1)
  {
    mon.process();
    thread_sleep_for(100);
  }
}
