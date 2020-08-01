#include <string>
#include <vector>
// #include "ADXL345_I2C.h"
// #include "MPU6050.h"
#include "mbed.h"
#include "base_util.h"

DigitalOut myled(PC_13);
// CAN can1(PA_11, PA_12);

BaseUtil base_util;

std::string monitorCanCallback(std::vector<std::string> command)
{
  std::string result = "";
  if (command[1] == "tx")
  {
    if(command.size() < 4){
      result += "too few args";
      return result;
    }

    CANMessage can_msg;
    can_msg.format = CANExtended;
    unsigned char target_id = atoi(command[2].c_str()) & 0x7f;
    unsigned char command_id = atoi(command[3].c_str()) & 0x7f;

    base_util.canlink_.send(target_id, command_id, std::vector<unsigned char>{10, 20, 30, 40});

  }
  return result;
}

void canlinkCommand(CanlinkMsg canlink_msg){
  printf("Message received: s:%d t:%u, c:%u ", canlink_msg.source_id, canlink_msg.target_id, canlink_msg.command_id);
  for(int i =0;i<canlink_msg.len;i++){
    printf("%u ", canlink_msg.data[i]);
  }
  printf("\n");
}

int main()
{
  base_util.registerParam("PID_P", 0);
  base_util.registerParam("PID_I", 0);
  base_util.registerParam("PID_D", 0);
  base_util.loadParam();

  base_util.canlink_.setID(1);
  base_util.monitor_.register_func("can", monitorCanCallback);
  base_util.canlink_.register_func(2, canlinkCommand);

  thread_sleep_for(1500);
  char data[8]={1,2,3,4,5,6,7,8};
  CANMessage can_data(10, data, 8, CANData, CANExtended);
  while (1)
  {
    base_util.process();
    base_util.canlink_.send(2, 10, std::vector<unsigned char>{10, 20, 30, 40});
    base_util.led1_ != base_util.led1_;
    thread_sleep_for(500);
  }
}
