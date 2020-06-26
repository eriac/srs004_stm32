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
  void write_p(unsigned int address, unsigned char* data, int size);
  void write_page(unsigned int page, std::vector<unsigned char> data);

  unsigned char read(unsigned int address);
  std::vector<unsigned char> read_page(unsigned int page);
};

I2CEEprom::I2CEEprom() : I2C(PB_9, PB_8)
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
  int ret1=((I2C*)this)->write(addr);
  int ret2=((I2C*)this)->write((address >> 8) & 0xff);
  int ret3=((I2C*)this)->write(address & 0xff);
  int ret4=((I2C*)this)->write(data);
  stop();
}

void I2CEEprom::write_p(unsigned int address, unsigned char* data, int size)
{
  start();
  ((I2C*)this)->write(addr);
  ((I2C*)this)->write((address >> 8) & 0xff);
  ((I2C*)this)->write(address & 0xff);
  for(int i =0;i<size;i++){
    ((I2C*)this)->write(data[i]);
  }
  // ((I2C*)this)->write(data,size,true);
  stop();
}

void I2CEEprom::write_page(unsigned int page, std::vector<unsigned char> data)
{
  start();
  unsigned char addr_l = (page * 32) & 0xff;
  unsigned char addr_h= ((page * 32) >> 8) & 0xff;
  ((I2C*)this)->write(addr);
  ((I2C*)this)->write(addr_l);
  ((I2C*)this)->write(addr_h);
  for(auto item: data){
    ((I2C*)this)->write(item);
  }
  stop();
}

std::vector<unsigned char> I2CEEprom::read_page(unsigned int page)
{
  start();
  unsigned char addr_l = (page * 32) & 0xff;
  unsigned char addr_h= ((page * 32) >> 8) & 0xff;
  ((I2C*)this)->write(addr);
  ((I2C*)this)->write(addr_l);
  ((I2C*)this)->write(addr_h);
  start();
  ((I2C*)this)->write(addr + 1);

  std::vector<unsigned char> result;
  for(int i=0;i<8;i++){
    result.push_back(((I2C*)this)->read(1));
  }
  stop();
  return result;
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