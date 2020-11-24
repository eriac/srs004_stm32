#include <mbed.h>

# define SBUS2_BYTE_SIZE 24
# define SBUS2_CH_SIZE 16

class Sbus2Receiver{
public:
  Sbus2Receiver(PinName tx_pin, PinName rx_pin) : serial_(tx_pin, rx_pin, 100000){
    serial_.attach(this, &Sbus2Receiver::rxCallback);
  }
  void rxCallback(void){
    char recv = serial_.getc();
    if(index_ == -1){
      if(recv==0x0f){
        index_ = 0;
      }
    }
    else{
      buffer_[index_] = recv;
      index_++;
    }

    if(index_==24){
      index_=-1;
      bool valid = !(buffer_[22] & 0x04);
      if(valid){
        for(int i=0;i<SBUS2_CH_SIZE;i++){
          int offset_byte = (i*11)/8;
          int offset_bit = (i*11)%8;
          output_[i] =decodeCh(offset_byte, offset_bit);
        }

      }
      valid_ = valid;
    }

  }
  int decodeCh(int offset_byte, int offset_bit){
		if(offset_bit < 5){
      unsigned int l_byte = buffer_[offset_byte] >> offset_bit;
      unsigned int h_byte = buffer_[offset_byte+1] << (8 - offset_bit);
      return  (h_byte|l_byte) & 0x7ff;
    }
		else{
      unsigned int l_byte = buffer_[offset_byte] >> offset_bit;
      unsigned int m_byte = buffer_[offset_byte+1] << (8 - offset_bit);
      unsigned int h_byte = buffer_[offset_byte+2] << (16 - offset_bit);
      return  (h_byte|m_byte|l_byte) & 0x7ff;
    }
  }
  bool checkUpdate(){
    bool output = valid_;
    valid_ = false;
    return output;
  }
  int getCh(int channel){
    return output_[channel];
  }

  unsigned char buffer_[SBUS2_BYTE_SIZE];
  int output_[SBUS2_CH_SIZE];
  int flag_ = 0;
  int last_ = 0;
  int index_ = -1;
  bool valid_ = false;
  RawSerial serial_;
};
