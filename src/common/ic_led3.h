#pragma once

#include "mbed.h"

struct ColorLED{
  unsigned char red;
  unsigned char green;
  unsigned char blue;
};

enum class EffectMode{
  NONE,
  PALSE,
  kFLASH
};


class IcLed3{
public:
  IcLed3(PinName mosi, PinName miso, PinName sck): spi_(mosi, miso, sck){
    spi_.format(8, 3);
    spi_.frequency(8000000);
    thread_sleep_for(500);
    idoring_led();
  }

  void idoring_led(){
    char tx_data[4];
    for(int i=0; i<4; i++)tx_data[i]=0x3f;
    char rx_data[4];
    spi_.write(tx_data, 4, rx_data, 4);
  }

  void setColor(unsigned char red, unsigned char green, unsigned char blue)
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

    spi_.write(tx_data, 72, rx_data, 72);
  }

  SPI spi_;
  ColorLED base_color_;
  ColorLED effect_color;
  EffectMode effect_mode_;
  Timer timer_;
};
