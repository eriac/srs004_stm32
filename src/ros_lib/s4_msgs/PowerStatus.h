#ifndef _ROS_s4_msgs_PowerStatus_h
#define _ROS_s4_msgs_PowerStatus_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace s4_msgs
{

  class PowerStatus : public ros::Msg
  {
    public:
      typedef uint8_t _source_type;
      _source_type source;
      typedef float _system_remain_rate_type;
      _system_remain_rate_type system_remain_rate;
      typedef float _wall_v_type;
      _wall_v_type wall_v;
      typedef float _bat1_v_type;
      _bat1_v_type bat1_v;
      typedef float _bat2_v_type;
      _bat2_v_type bat2_v;
      enum { SOURCE_UNKNOWN =  0 };
      enum { SOURCE_WALL =  1 };
      enum { SOURCE_BATTERY1 =  2 };
      enum { SOURCE_BATTERY2 =  3 };

    PowerStatus():
      source(0),
      system_remain_rate(0),
      wall_v(0),
      bat1_v(0),
      bat2_v(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->source >> (8 * 0)) & 0xFF;
      offset += sizeof(this->source);
      union {
        float real;
        uint32_t base;
      } u_system_remain_rate;
      u_system_remain_rate.real = this->system_remain_rate;
      *(outbuffer + offset + 0) = (u_system_remain_rate.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_system_remain_rate.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_system_remain_rate.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_system_remain_rate.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->system_remain_rate);
      union {
        float real;
        uint32_t base;
      } u_wall_v;
      u_wall_v.real = this->wall_v;
      *(outbuffer + offset + 0) = (u_wall_v.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_wall_v.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_wall_v.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_wall_v.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->wall_v);
      union {
        float real;
        uint32_t base;
      } u_bat1_v;
      u_bat1_v.real = this->bat1_v;
      *(outbuffer + offset + 0) = (u_bat1_v.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_bat1_v.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_bat1_v.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_bat1_v.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->bat1_v);
      union {
        float real;
        uint32_t base;
      } u_bat2_v;
      u_bat2_v.real = this->bat2_v;
      *(outbuffer + offset + 0) = (u_bat2_v.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_bat2_v.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_bat2_v.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_bat2_v.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->bat2_v);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->source =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->source);
      union {
        float real;
        uint32_t base;
      } u_system_remain_rate;
      u_system_remain_rate.base = 0;
      u_system_remain_rate.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_system_remain_rate.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_system_remain_rate.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_system_remain_rate.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->system_remain_rate = u_system_remain_rate.real;
      offset += sizeof(this->system_remain_rate);
      union {
        float real;
        uint32_t base;
      } u_wall_v;
      u_wall_v.base = 0;
      u_wall_v.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_wall_v.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_wall_v.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_wall_v.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->wall_v = u_wall_v.real;
      offset += sizeof(this->wall_v);
      union {
        float real;
        uint32_t base;
      } u_bat1_v;
      u_bat1_v.base = 0;
      u_bat1_v.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_bat1_v.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_bat1_v.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_bat1_v.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->bat1_v = u_bat1_v.real;
      offset += sizeof(this->bat1_v);
      union {
        float real;
        uint32_t base;
      } u_bat2_v;
      u_bat2_v.base = 0;
      u_bat2_v.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_bat2_v.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_bat2_v.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_bat2_v.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->bat2_v = u_bat2_v.real;
      offset += sizeof(this->bat2_v);
     return offset;
    }

    const char * getType(){ return "s4_msgs/PowerStatus"; };
    const char * getMD5(){ return "dbd259798cf5f3b7faf8b7ad7ca80b0d"; };

  };

}
#endif
