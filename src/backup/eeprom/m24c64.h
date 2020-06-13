#include "mbed.h"
// http://robot.tamagawa.ac.jp:8080/cyber/mbed/i2c_memory.html

class I2CEEprom : public I2C
{
private:
  unsigned char addr;

public:
  I2CEEprom();
  I2CEEprom(PinName data, PinName clock, int address);
  void write(unsigned int address, unsigned char data);
  unsigned char read(unsigned int address);
};

I2CEEprom::I2CEEprom() : I2C(PB_7, PB_6)
{
  addr = 0xA0;
}
I2CEEprom::I2CEEprom(PinName data, PinName clock, int address) : I2C(data, clock)
{
  addr = address;
}

void I2CEEprom::write(unsigned int address, unsigned char data)
{
  start();
  ((I2C*)this)->write(addr);
  ((I2C*)this)->write((address >> 8) & 0xff);
  ((I2C*)this)->write(address & 0xff);
  ((I2C*)this)->write(data);
  stop();
}

unsigned char I2CEEprom::read(unsigned int address)
{
  unsigned char x;
  start();
  ((I2C*)this)->write(addr);
  ((I2C*)this)->write((address >> 8) & 0xff);
  ((I2C*)this)->write(address & 0xff);
  start();
  ((I2C*)this)->write(addr + 1);
  x = ((I2C*)this)->read(0);
  stop();
  return x;
}