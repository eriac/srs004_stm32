#include <string>
#include <vector>
#include "mbed.h"
#include "base_util.h"
#include "sbus2.h"
#include "canlink_util.h"
#include <ros.h>
#include <std_msgs/String.h>

BaseUtil base_util;

// Create the ROS node handle
class mySTM32 : public MbedHardware
{
public:
  mySTM32(): MbedHardware(PA_0, PA_1, 1000000) {}; 
};
ros::NodeHandle_<mySTM32> nh;

std_msgs::String str_msg;
ros::Publisher chatter("chatter", &str_msg);

char hello[13] = "hello world!";

int main() {
		nh.initNode();
    nh.advertise(chatter);
    
    while (1) {
        // led = !led;
        base_util.toggleLed(1);

        str_msg.data = hello;
        chatter.publish( &str_msg );
        nh.spinOnce();
        thread_sleep_for(1000);
    }
}


// int main()
// {
//   base_util.registerParam("GAIN_F", 0.00015f);
//   base_util.registerParam("GAIN_P", 0.0002f);
//   base_util.registerParam("GAIN_I", 0.0010f);
//   base_util.loadParam();

//   base_util.setCanlinkID(1);
//   // base_util.registerMonitor("can", monitorCanCallback);
//   // base_util.registerMonitor("mot", motorCallback);
//   // base_util.registerMonitor("imu", callback(imuCommand));

//   // base_util.registerCanlink(2, canlinkCommand);
//   // base_util.registerCanlink(20, canlinkCommand);

//   auto flag_2hz = base_util.registerTimer(2.0);
//   auto flag_50hz = base_util.registerTimer(50.0);
//   while (1)
//   {
//     if(flag_2hz->check()){
//       // printf("2hz\n");

//       // canlink_util::LedColor led_color;
//       // led_color.set_mode = canlink_util::LedColor::SET_BASE_COLOR;
//       // led_color.red = 10;
//       // led_color.green = 10;
//       // led_color.blue = 0;
//       // base_util.sendCanlink(2, led_color.getID(), led_color.getData());
//       base_util.toggleLed(1);
//     }
//     if(flag_50hz->check()){
//       if(sbus2.checkUpdate()){
//         // printf("sbus2\n");
//         // printf(" 0ch: %04u,  1ch: %04u,  2ch: %04u,  3ch: %04u\n", sbus2.getCh(0), sbus2.getCh(1), sbus2.getCh(2), sbus2.getCh(3));
//         // printf(" 4ch: %04u,  5ch: %04u,  6ch: %04u,  7ch: %04u\n", sbus2.getCh(4), sbus2.getCh(5), sbus2.getCh(6), sbus2.getCh(7));

//         unsigned int sw_d = sbus2.getCh(7);
//         if(sw_d < 1024){
//           base_util.turnOnLed(2);
//         }
//         else{
//           base_util.turnOffLed(2);
//         }
//       }
//       if(sbus2.checkLost()){
//         printf("sbus2 lost\n");
//       }
//     }
//     base_util.process();
//     thread_sleep_for(10);
//   }
// }
