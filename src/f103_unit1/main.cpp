#include <string>
#include <vector>
// #include "ADXL345_I2C.h"
// #include "MPU6050.h"
#include "mbed.h"
#include "base_util.h"

DigitalOut myled(PC_13);

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
  base_util.registerCanlink(10, canlinkCommand);

  auto flag = base_util.hz_timer_.registerTimer(1.0);
  while (1)
  {
    if(flag->check()){
      printf("flag: true\n");
    }
    base_util.process();
    thread_sleep_for(100);
  }
}
