#include <ros.h>
#include <std_msgs/Empty.h>
#include <std_msgs/Bool.h>
#include "mbed.h"

class mySTM32 : public MbedHardware
{
public:
  mySTM32() : MbedHardware(USBTX, USBRX, 57600){};
};
ros::NodeHandle_<mySTM32> nh;

DigitalOut myled(LED1);
DigitalIn mybutton(USER_BUTTON);

void messageCb(const std_msgs::Empty& toggle_msg)
{
  myled = !myled;  // blink the led
}
ros::Subscriber<std_msgs::Empty> sub("toggle_led", &messageCb);

std_msgs::Bool pushed_msg;
ros::Publisher pub_button("pushed", &pushed_msg);

int main()
{
  nh.initNode();
  nh.subscribe(sub);
  nh.advertise(pub_button);

  while (1)
  {
    pushed_msg.data = mybutton;
    pub_button.publish(&pushed_msg);

    nh.spinOnce();
    thread_sleep_for(500);
  }
}
