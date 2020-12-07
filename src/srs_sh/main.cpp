#include <string>
#include <vector>
#include "mbed.h"
#include "base_util.h"
#include "sbus2.h"
#include "canlink_converter.h"
#include "canlink_serialiser.h"

BaseUtil base_util;

RawSerial serial(PA_0, PA_1, 1000000);
// serial.attach([&]{
//   char recv = serial.getc();
//   serial.putc(recv);
//   if(recv=='a'){
//     base_util.toggleLed(2);
//   }
//   // printf("recv: %c\n", recv);
// });
void nop(int value){
}

void canlinkCommand(CanlinkMsg canlink_msg){
  // printf("Message received: s:%d t:%u, c:%u ", canlink_msg.source_id, canlink_msg.target_id, canlink_msg.command_id);
  // for(int i =0;i<canlink_msg.len;i++){
  //   printf("%u ", canlink_msg.data[i]);
  // }
  // printf("\n");
  CanLinkSerialiser::CanLinkSerialiser cs;
  cs.channel = 'A';
  cs.source_id = canlink_msg.source_id;
  cs.target_id = canlink_msg.target_id;
  cs.command = canlink_msg.command_id;
  cs.size = canlink_msg.len;
  for(int i=0;i<8;i++)cs.data[i] = canlink_msg.data[i];

  event_callback_t callback;
  std::string code = cs.encode();

  std::string serial_code = code+"\n";
  serial.write((uint8_t *)serial_code.c_str(), serial_code.size(), callback); 

  printf("%s\n", code.c_str());

}

Sbus2Receiver sbus2(PC_10, PC_11);

int main()
{
  base_util.registerParam("GAIN_F", 0.00015f);
  base_util.registerParam("GAIN_P", 0.0002f);
  base_util.registerParam("GAIN_I", 0.0010f);
  base_util.loadParam();

  base_util.setCanlinkID(1);
  // base_util.registerMonitor("can", monitorCanCallback);
  // base_util.registerMonitor("mot", motorCallback);
  // base_util.registerMonitor("imu", callback(imuCommand));

  base_util.registerCanlink(2, canlinkCommand);
  base_util.registerCanlink(CANLINK_CMD_ID_TARGET_STATUS, canlinkCommand);

  auto flag_2hz = base_util.registerTimer(2.0);
  auto flag_50hz = base_util.registerTimer(50.0);
  while (1)
  {
    if(flag_2hz->check()){
      // printf("2hz\n");
      // base_util.sendCanlink(2, 10, std::vector<unsigned char>{sbus2.getCh(0)/10, sbus2.getCh(1)/10, sbus2.getCh(2)/10, sbus2.getCh(3)/10});
      // base_util.sendCanlink(2, 10, std::vector<unsigned char>{10, 20, 30, 40});

      CanlinkConvertor::LedColor led_color;
      led_color.set_mode = CanlinkConvertor::LedColor::SET_BASE_COLOR;
      led_color.red = 10;
      led_color.green = 10;
      led_color.blue = 0;
      base_util.sendCanlink(2, led_color.getID(), led_color.encode());
      base_util.toggleLed(1);
    }
    if(flag_50hz->check()){
      if(sbus2.checkUpdate()){
        // printf("sbus2\n");
        // printf(" 0ch: %04u,  1ch: %04u,  2ch: %04u,  3ch: %04u\n", sbus2.getCh(0), sbus2.getCh(1), sbus2.getCh(2), sbus2.getCh(3));
        // printf(" 4ch: %04u,  5ch: %04u,  6ch: %04u,  7ch: %04u\n", sbus2.getCh(4), sbus2.getCh(5), sbus2.getCh(6), sbus2.getCh(7));

        unsigned int sw_d = sbus2.getCh(7);
        if(sw_d < 1024){
          base_util.turnOnLed(2);
        }
        else{
          base_util.turnOffLed(2);
        }
      }
      if(sbus2.checkLost()){
        printf("sbus2 lost\n");
      }
    }
    base_util.process();
    thread_sleep_for(10);
  }
}
