#include "mbed.h"
#include "mon.h"

DigitalOut myled(PC_13);

// MonBase mon(USBTX, USBRX);
RawSerial serial(USBTX, USBRX, 115200);

std::string led(std::vector<std::string> command)
{
  std::string result = "not match";
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

void dummy(void)
{
  while (true)
  {
    thread_sleep_for(500);
    serial.printf("aaaa\n");
  }
}

int main()
{
  // mon.start();

  Thread thread1;
  // thread1.start(callback(&mon, &MonBase::dummy));
  thread1.start(dummy);

  // mon.register_func("led", callback(led));
  // mon.register_func("param", callback(&param0, &Param::monCallback));

  // param0.register_int("PID_P", 10);
  // param0.register_int("PID_I", 20);

  while (1)
  {
    thread_sleep_for(100);
    // mon.process();
    // myled = !myled;
  }
}
