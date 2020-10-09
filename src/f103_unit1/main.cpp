#include <string>
#include <vector>
#include "ADXL345_I2C.h"
// #include "MPU6050.h"
#include "mbed.h"
#include "base_util.h"

DigitalOut myled(PC_13);
ADXL345_I2C accelerometer(PB_11, PB_10);

BaseUtil base_util;

void canlinkCommand(CanlinkMsg canlink_msg){
  printf("Message received: s:%d t:%u, c:%u ", canlink_msg.source_id, canlink_msg.target_id, canlink_msg.command_id);
  for(int i =0;i<canlink_msg.len;i++){
    printf("%u ", canlink_msg.data[i]);
  }
  printf("\n");
  base_util.toggleLed(2);
}

SPI fled(PA_7, PA_6, PA_5);

void idoring_led(){
  char tx_data[4] = { 0x3f, 0x3f, 0x3f, 0x3f };
  char rx_data[4];
  fled.write(tx_data, 4, rx_data, 4);
}

void set_led(unsigned char red, unsigned char green, unsigned char blue)
{
  char tx_data[72];
  char rx_data[72];
  for (int i = 0; i < 72; i++) tx_data[i] = 0x3f;

  for (int i = 0; i < 8; i++)
    if (green & 1 << (7 - i))
      tx_data[i] = 0x03;
  for (int i = 0; i < 8; i++)
    if (red & 1 << (7 - i))
      tx_data[i + 8] = 0x03;
  for (int i = 0; i < 8; i++)
    if (blue & 1 << (7 - i))
      tx_data[i + 16] = 0x03;

  for (int i = 0; i < 8; i++)
    if (green & 1 << (7 - i))
      tx_data[i+24] = 0x03;
  for (int i = 0; i < 8; i++)
    if (red & 1 << (7 - i))
      tx_data[i + 8 +24] = 0x03;
  for (int i = 0; i < 8; i++)
    if (blue & 1 << (7 - i))
      tx_data[i + 16 +24] = 0x03;

  for (int i = 0; i < 8; i++)
    if (green & 1 << (7 - i))
      tx_data[i+48] = 0x03;
  for (int i = 0; i < 8; i++)
    if (red & 1 << (7 - i))
      tx_data[i + 8 +48] = 0x03;
  for (int i = 0; i < 8; i++)
    if (blue & 1 << (7 - i))
      tx_data[i + 16 +48] = 0x03;

  fled.write(tx_data, 72, rx_data, 72);
}

std::string ledCommand(std::vector<std::string> command)
{
  printf("size: %u\n", command.size());
  std::string result;
  if (command[1] == "color")
  {
    if (command.size() == 5)
    {
      // unsigned char r = std::atoi(command[2].c_str());
      // unsigned char g = std::atoi(command[3].c_str());
      // unsigned char b = std::atoi(command[4].c_str());
      // set_led(r, g, b);
      // result = "color: " + std::to_string(r) + ", " + std::to_string(g) + ", " + std::to_string(b);
      // result = "***";
    }
    else
    {
      result = "command.size must be 5";
    }
  }
  return result;
}


int main()
{
  // base_util.registerParam("PID_P", 0);
  // base_util.registerParam("PID_I", 0);
  // base_util.registerParam("PID_D", 0);
  // base_util.loadParam();
  base_util.registerMonitor("led", ledCommand);

  // base_util.setCanlinkID(2);
  // base_util.registerCanlink(10, canlinkCommand);

  fled.format(8, 3);
  fled.frequency(8000000);

  // TAP
  accelerometer.setPowerControl(0x00);
  accelerometer.setDataFormatControl(0x03);
  accelerometer.setDataRate(ADXL345_3200HZ);
  accelerometer.setTapThreshold(0x40);
  accelerometer.setTapDuration(16 * 625);
  accelerometer.setTapAxisControl(0x07);
  accelerometer.setInterruptEnableControl(0x40);
  accelerometer.setPowerControl(0x08);
  thread_sleep_for(500);

  int ret = accelerometer.getDevId();
  printf("id: %i\n", ret);

  idoring_led();
  thread_sleep_for(500);
  set_led(10, 0, 0);
  thread_sleep_for(500);
  set_led(00, 10, 0);
  thread_sleep_for(500);
  set_led(00, 0, 10);
  thread_sleep_for(500);
  set_led(00, 0, 0);

  auto flag_2hz = base_util.registerTimer(2.0);
  auto flag_10hz = base_util.registerTimer(10.0);
  while (1)
  {
    if(flag_2hz->check()){
      // printf("flag 2hz\n");
      base_util.toggleLed(1);

      int readings[3] = { 0, 0, 0 };
      accelerometer.getOutput(readings);
      int source = accelerometer.getInterruptSource();
      // printf("%+04i, %+04i, %+04i %i\n", (int16_t)readings[0], (int16_t)readings[1], (int16_t)readings[2],
      //                    source & 1 << 6);

    }
    if(flag_10hz->check()){
      int readings[3] = { 0, 0, 0 };
      accelerometer.getOutput(readings);
      int source = accelerometer.getInterruptSource();
      if(source & 0x40){
        printf("hit\n");
        set_led(10, 0, 0);
      }
      else{
        set_led(0, 0, 10);
      }
      // printf("%+04i, %+04i, %+04i %i\n", (int16_t)readings[0], (int16_t)readings[1], (int16_t)readings[2],
      //                    source & 1 << 6);

    }
    base_util.process();
    thread_sleep_for(10);
  }
}
