#include "mbed.h"

class I2CEEprom
{
private:
  unsigned char addr;

public:
  I2CEEprom(I2C& i2c);
  void write_page(unsigned int page, std::vector<unsigned char> data);
  std::vector<unsigned char> read_page(unsigned int page, int size);
  I2C& mi2c;
};

I2CEEprom::I2CEEprom(I2C& i2c) : mi2c(i2c)
{
  addr = 0xA0;
}

void I2CEEprom::write_page(unsigned int page, std::vector<unsigned char> data)
{
  mi2c.start();
  unsigned char addr_l = (page * 32) & 0xff;
  unsigned char addr_h = ((page * 32) >> 8) & 0xff;
  mi2c.write(addr);
  mi2c.write(addr_l);
  mi2c.write(addr_h);
  for (auto item : data)
  {
    mi2c.write(item);
  }
  mi2c.stop();
}

std::vector<unsigned char> I2CEEprom::read_page(unsigned int page, int size)
{
  mi2c.start();
  unsigned char addr_l = (page * 32) & 0xff;
  unsigned char addr_h = ((page * 32) >> 8) & 0xff;
  mi2c.write(addr);
  mi2c.write(addr_l);
  mi2c.write(addr_h);
  mi2c.start();
  mi2c.write(addr + 1);

  std::vector<unsigned char> result;
  for (int i = 0; i < size; i++)
  {
    result.push_back(mi2c.read(1));
  }
  mi2c.stop();
  return result;
}
