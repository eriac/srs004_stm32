#include "mbed.h"

DigitalOut myled(PC_13);
// DigitalIn mybutton(USER_BUTTON);

Thread thread;

void led_thread()
{
  while (true)
  {
    // Signal flags that are reported as event are automatically cleared.
    Thread::signal_wait(0x1);
    myled = !myled;
  }
}

int main()
{
  thread.start(callback(led_thread));
  while (1)
  {
    thread.signal_set(0x1);
    // if(mybutton)thread.signal_set(0x1);
    thread_sleep_for(500);
  }
}
