#ifndef _ROS_s4_msgs_HeartBeat_h
#define _ROS_s4_msgs_HeartBeat_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace s4_msgs
{

  class HeartBeat : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef uint8_t _source_id_type;
      _source_id_type source_id;
      typedef uint8_t _mode_type;
      _mode_type mode;
      bool warning[16];
      bool error[16];
      enum { MODE_UNKNOWN =  0 };
      enum { MODE_BOOT =  1 };
      enum { MODE_ACTIVE =  2 };
      enum { MODE_FAULT =  3 };
      enum { MODE_DEBUG =  4 };

    HeartBeat():
      header(),
      source_id(0),
      mode(0),
      warning(),
      error()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->source_id >> (8 * 0)) & 0xFF;
      offset += sizeof(this->source_id);
      *(outbuffer + offset + 0) = (this->mode >> (8 * 0)) & 0xFF;
      offset += sizeof(this->mode);
      for( uint32_t i = 0; i < 16; i++){
      union {
        bool real;
        uint8_t base;
      } u_warningi;
      u_warningi.real = this->warning[i];
      *(outbuffer + offset + 0) = (u_warningi.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->warning[i]);
      }
      for( uint32_t i = 0; i < 16; i++){
      union {
        bool real;
        uint8_t base;
      } u_errori;
      u_errori.real = this->error[i];
      *(outbuffer + offset + 0) = (u_errori.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->error[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      this->source_id =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->source_id);
      this->mode =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->mode);
      for( uint32_t i = 0; i < 16; i++){
      union {
        bool real;
        uint8_t base;
      } u_warningi;
      u_warningi.base = 0;
      u_warningi.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->warning[i] = u_warningi.real;
      offset += sizeof(this->warning[i]);
      }
      for( uint32_t i = 0; i < 16; i++){
      union {
        bool real;
        uint8_t base;
      } u_errori;
      u_errori.base = 0;
      u_errori.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->error[i] = u_errori.real;
      offset += sizeof(this->error[i]);
      }
     return offset;
    }

    const char * getType(){ return "s4_msgs/HeartBeat"; };
    const char * getMD5(){ return "86e8756a438ae8178ae1402be816d887"; };

  };

}
#endif
