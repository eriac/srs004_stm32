#pragma once

#include "mbed.h"

struct ColorLED{
  unsigned char red;
  unsigned char green;
  unsigned char blue;
};

enum class LedMode{
  INIT0,
  INIT1,
  WAIT,
  BASE,
  NONE,
  PALSE_WAIT,
  PALSE_EFFECT,
};

class IcLed3{
public:
  IcLed3(PinName mosi, PinName miso, PinName sck);
  void process(void);
  void setBase(unsigned char red, unsigned char green, unsigned char blue);
  void setPalse(unsigned char red, unsigned char green, unsigned char blue);

private:
  void idoring_led();
  void setColor(unsigned char red, unsigned char green, unsigned char blue);
  SPI spi_;
  ColorLED base_color_;
  ColorLED effect_color_;
  LedMode mode_;
  Timer timer_;
  int base_time_;
};


IcLed3::IcLed3(PinName mosi, PinName miso, PinName sck): spi_(mosi, miso, sck){
  spi_.format(8, 3);
  spi_.frequency(8000000);
  thread_sleep_for(500);
  idoring_led();
  mode_ = LedMode::INIT0;
  timer_.start();
}

void IcLed3::process(void){
  int timer_ms = timer_.read_ms();
  if(mode_ == LedMode::INIT0 && 10 < timer_ms){
    mode_ = LedMode::INIT1;
    setColor(10, 10, 10);
    printf("INIT0->INIT1\n");
  }    
  else if(mode_ == LedMode::INIT1 && 300 < timer_ms){
    mode_ = LedMode::WAIT;
    setColor(base_color_.red, base_color_.green, base_color_.blue);
    printf("INIT1->WAIT\n");
  }
  else if(mode_ == LedMode::BASE){
    mode_ = LedMode::WAIT;
    setColor(base_color_.red, base_color_.green, base_color_.blue);
    printf("BASE->WAIT\n");
  }
  else if(mode_ == LedMode::PALSE_WAIT){
    mode_ = LedMode::PALSE_EFFECT;
    setColor(effect_color_.red, effect_color_.green, effect_color_.blue);
    printf("PALSE_WAIT->PALSE_EFFECT\n");
  }
  else if(mode_ == LedMode::PALSE_EFFECT && 200 < (timer_ms-base_time_)){
    mode_ = LedMode::WAIT;
    setColor(base_color_.red, base_color_.green, base_color_.blue);
    printf("PALSE_EFFECT->WAIT\n");
  }
}

void IcLed3::setBase(unsigned char red, unsigned char green, unsigned char blue){
  if(mode_ == LedMode::WAIT){
    mode_ = LedMode::BASE;
    printf("SET BASE\n");
  }
  base_color_.red = red;
  base_color_.green = green;
  base_color_.blue = blue;
}

void IcLed3::setPalse(unsigned char red, unsigned char green, unsigned char blue){
  if(mode_ == LedMode::WAIT){
    mode_ = LedMode::PALSE_WAIT;
    printf("SET PALSE_WAIT\n");
  }
  base_time_ = timer_.read_ms();
  effect_color_.red = red;
  effect_color_.green = green;
  effect_color_.blue = blue;
}

void IcLed3::idoring_led(){
  char tx_data[4];
  for(int i=0; i<4; i++)tx_data[i]=0x3f;
  char rx_data[4];
  spi_.write(tx_data, 4, rx_data, 4);
}

void IcLed3::setColor(unsigned char red, unsigned char green, unsigned char blue)
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
