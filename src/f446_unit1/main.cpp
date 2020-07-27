#include <string>
#include <vector>
// #include "ADXL345_I2C.h"
// #include "MPU6050.h"
#include "mbed.h"
#include "base_util.h"

DigitalOut myled(PC_13);
CAN can1(PA_11, PA_12);

BaseUtil base_util;

std::string monitorCanCallback(std::vector<std::string> command)
{
  std::string result = "";
  if (command[1] == "tx")
  {
    if(command.size() < 3){
      result += "too few args";
      return result;
    }

    CANMessage msg;
    msg.id = atoi(command[2].c_str());
    for(int i = 3; i < command.size(); i++){
      msg.data[i - 3] = atoi(command[i].c_str());
    }
    msg.len = command.size() - 3;

    if(can1.write(msg)){
      printf("success %u\n", msg.data[0]);
    }
    else{
      printf("fail %u\n", msg.data[0]);
    }
  }
  return result;
}

int main()
{
  base_util.registerParam("PID_P", 0);
  base_util.registerParam("PID_I", 0);
  base_util.registerParam("PID_D", 0);
  base_util.loadParam();

  base_util.monitor_.register_func("can", monitorCanCallback);

  can1.frequency(1000000);
  int handle = can1.filter(0, 0x3F0, CANStandard);
  printf("filter: %u\n", handle);

  thread_sleep_for(1500);
  char data[8]={1,2,3,4,5,6,7,8};
  CANMessage can_data(10, data, 8);
  while (1)
  {
    base_util.process();
    can_data.id = 0x01;
    can1.write(can_data);
    can_data.id = 0x11;
    can1.write(can_data);
    // if(can1.write(can_data)){
    //   printf("success %u\n", can_data.data[0]);
    //   base_util.led2_ = !base_util.led2_;
    // }
    // else{
    //   printf("fail %u\n", can_data.data[0]);
    // }
    // unsigned int re = can1.rderror();
    // unsigned int te = can1.tderror();
    // printf("error tx:%u rx:%u\n", te, re);

    can_data.data[0]++;
    thread_sleep_for(500);

    while(can1.read(can_data)) {
      printf("Message received: %d ", can_data.id);
      for(int i =0;i<can_data.len;i++){
        printf("%u ", can_data.data[i]);
      }
      printf("\n");
      base_util.led2_ = !base_util.led2_;
    } 

    thread_sleep_for(100);
  }
}
