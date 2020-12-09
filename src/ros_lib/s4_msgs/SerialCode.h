#ifndef _ROS_s4_msgs_SerialCode_h
#define _ROS_s4_msgs_SerialCode_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace s4_msgs
{

  class SerialCode : public ros::Msg
  {
    public:
      char* command[4];
      char* option[4];
      char* suboption[4];
      uint8_t data[20];
      typedef int8_t _datanum_type;
      _datanum_type datanum;

    SerialCode():
      command(),
      option(),
      suboption(),
      data(),
      datanum(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      for( uint32_t i = 0; i < 4; i++){
      uint32_t length_commandi = strlen(this->command[i]);
      varToArr(outbuffer + offset, length_commandi);
      offset += 4;
      memcpy(outbuffer + offset, this->command[i], length_commandi);
      offset += length_commandi;
      }
      for( uint32_t i = 0; i < 4; i++){
      uint32_t length_optioni = strlen(this->option[i]);
      varToArr(outbuffer + offset, length_optioni);
      offset += 4;
      memcpy(outbuffer + offset, this->option[i], length_optioni);
      offset += length_optioni;
      }
      for( uint32_t i = 0; i < 4; i++){
      uint32_t length_suboptioni = strlen(this->suboption[i]);
      varToArr(outbuffer + offset, length_suboptioni);
      offset += 4;
      memcpy(outbuffer + offset, this->suboption[i], length_suboptioni);
      offset += length_suboptioni;
      }
      for( uint32_t i = 0; i < 20; i++){
      *(outbuffer + offset + 0) = (this->data[i] >> (8 * 0)) & 0xFF;
      offset += sizeof(this->data[i]);
      }
      union {
        int8_t real;
        uint8_t base;
      } u_datanum;
      u_datanum.real = this->datanum;
      *(outbuffer + offset + 0) = (u_datanum.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->datanum);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      for( uint32_t i = 0; i < 4; i++){
      uint32_t length_commandi;
      arrToVar(length_commandi, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_commandi; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_commandi-1]=0;
      this->command[i] = (char *)(inbuffer + offset-1);
      offset += length_commandi;
      }
      for( uint32_t i = 0; i < 4; i++){
      uint32_t length_optioni;
      arrToVar(length_optioni, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_optioni; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_optioni-1]=0;
      this->option[i] = (char *)(inbuffer + offset-1);
      offset += length_optioni;
      }
      for( uint32_t i = 0; i < 4; i++){
      uint32_t length_suboptioni;
      arrToVar(length_suboptioni, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_suboptioni; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_suboptioni-1]=0;
      this->suboption[i] = (char *)(inbuffer + offset-1);
      offset += length_suboptioni;
      }
      for( uint32_t i = 0; i < 20; i++){
      this->data[i] =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->data[i]);
      }
      union {
        int8_t real;
        uint8_t base;
      } u_datanum;
      u_datanum.base = 0;
      u_datanum.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->datanum = u_datanum.real;
      offset += sizeof(this->datanum);
     return offset;
    }

    const char * getType(){ return "s4_msgs/SerialCode"; };
    const char * getMD5(){ return "94d81beac9e8e9fd3b15a71a76b7cfc2"; };

  };

}
#endif
