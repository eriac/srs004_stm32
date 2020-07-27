#include <string>
#include <vector>
// #include "ADXL345_I2C.h"
// #include "MPU6050.h"
#include "mbed.h"
#include "base_util.h"

DigitalOut myled(PC_13);
CAN can1(PA_11, PA_12);

BaseUtil base_util;

int main()
{
  base_util.registerParam("PID_P", 0);
  base_util.registerParam("PID_I", 0);
  base_util.registerParam("PID_D", 0);
  base_util.loadParam();

  can1.frequency(1000000);

  char data[8]={1,2,3,4,5,6,7};
  CANMessage can_data(10, data, 8);
  while (1)
  {
    base_util.process();
    // if(can1.write(can_data)){
    //   printf("success %u\n", can_data.data[0]);
    //   base_util.led2_ = !base_util.led2_;
    // }
    // else{
    //   printf("fail %u\n", can_data.data[0]);
    // }
    // can_data.data[0]++;
    // thread_sleep_for(500);

    if(can1.read(can_data)) {
      printf("Message received: %d\n", can_data.data[0]);
      if(can1.write(can_data)){
        printf("replay success %u\n", can_data.data[0]);
        base_util.led2_ = !base_util.led2_;
      }
      else{
        printf("replay fail %u\n", can_data.data[0]);
      }

    } 
    thread_sleep_for(100);
  }
}
