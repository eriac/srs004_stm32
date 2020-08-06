#include <string>
#include <vector>
// #include "ADXL345_I2C.h"
// #include "MPU6050.h"
#include "mbed.h"
#include "base_util.h"

DigitalOut myled(PC_13);
CAN can1(PA_11, PA_12);

BaseUtil base_util;

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

  base_util.setCanlinkID(2);
  base_util.canlink_.register_func(10, canlinkCommand);

  can1.frequency(1000000);

  char data[8]={1,2,3,4,5,6,7};
  CANMessage can_data(10, data, 8);
  while (1)
  {
    base_util.process();
    thread_sleep_for(100);
  }
}
