#include "mbed.h"
#include "mon.h"

DigitalOut led1(LED1);

Mon mon(USBTX, USBRX);
Param param0;

void led(std::vector<std::string> command)
{
    if(command[1] == "set") {
        if(command[2] == "0")led1=0;
        else led1 = 1;
    }
}

int main()
{
    mon.register_func("led", callback(led));
    mon.register_func("param", callback(&param0, &Param::monCallback));

    param0.register_int("PID_P", 10);
    param0.register_int("PID_I", 20);

    while(1) {
        thread_sleep_for(100);
        mon.process();
    }
}
