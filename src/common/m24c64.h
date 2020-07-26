#include "mbed.h"

union param_value {
  struct int_value_t
  {
    int data;
    unsigned char rest[4];
  } int_value;
  struct float_value_t
  {
    float data;
    unsigned char rest[4];
  } float_value;
  unsigned char char_value[8];
};

enum class param_type : unsigned char
{
  TYPE_NONE,
  TYPE_INT,
  TYPE_FLOAT,
  TYPE_STRING
};

struct param_item
{
  param_item(){
    type = param_type::TYPE_NONE;
    strncpy(name, "", 7);
  }
  param_type type;
  char name[7];
  union param_value value;
};

union param_union {
  param_union(){}
  param_item param[2];
  unsigned char byte[32];
};

class I2CEEprom
{
private:
  unsigned char addr;

public:
  I2CEEprom(I2C& i2c);
  void write_page(unsigned int page, param_union pdata);
  param_union read_page(unsigned int page);
  void clear_page(unsigned int page);
  I2C& mi2c;
};

I2CEEprom::I2CEEprom(I2C& i2c) : mi2c(i2c)
{
  addr = 0xA0;
}

void I2CEEprom::clear_page(unsigned int page){
  mi2c.start();
  unsigned char addr_h = ((page * 32) >> 8) & 0xff;
  unsigned char addr_l = (page * 32) & 0xff;
  mi2c.write(addr);
  mi2c.write(addr_h);
  mi2c.write(addr_l);
  for (int i = 0; i <32; i++)
  {
    mi2c.write(0xff);
  }
  mi2c.stop();  
}

void I2CEEprom::write_page(unsigned int page, param_union pdata)
{
  mi2c.start();
  unsigned char addr_h = ((page * 32) >> 8) & 0xff;
  unsigned char addr_l = (page * 32) & 0xff;
  mi2c.write(addr);
  mi2c.write(addr_h);
  mi2c.write(addr_l);
  for (int i = 0; i <32; i++)
  {
    mi2c.write(pdata.byte[i]);
  }
  mi2c.stop();
}

param_union I2CEEprom::read_page(unsigned int page){
  mi2c.start();
  unsigned char addr_h = ((page * 32) >> 8) & 0xff;
  unsigned char addr_l = (page * 32) & 0xff;
  mi2c.write(addr);
  mi2c.write(addr_h);
  mi2c.write(addr_l);
  mi2c.start();
  mi2c.write(addr + 1);

  param_union pdata;
  for (int i = 0; i < 32; i++)
  {
    if(i!=31)pdata.byte[i] = mi2c.read(1);
    else pdata.byte[i] = mi2c.read(0);
  }
  mi2c.stop();
  return pdata;
}