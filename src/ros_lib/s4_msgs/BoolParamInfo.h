#ifndef _ROS_s4_msgs_BoolParamInfo_h
#define _ROS_s4_msgs_BoolParamInfo_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace s4_msgs
{

  class BoolParamInfo : public ros::Msg
  {
    public:
      typedef const char* _name_type;
      _name_type name;
      typedef bool _value_type;
      _value_type value;
      typedef bool _min_type;
      _min_type min;
      typedef bool _max_type;
      _max_type max;
      typedef bool _dflt_type;
      _dflt_type dflt;

    BoolParamInfo():
      name(""),
      value(0),
      min(0),
      max(0),
      dflt(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_name = strlen(this->name);
      varToArr(outbuffer + offset, length_name);
      offset += 4;
      memcpy(outbuffer + offset, this->name, length_name);
      offset += length_name;
      union {
        bool real;
        uint8_t base;
      } u_value;
      u_value.real = this->value;
      *(outbuffer + offset + 0) = (u_value.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->value);
      union {
        bool real;
        uint8_t base;
      } u_min;
      u_min.real = this->min;
      *(outbuffer + offset + 0) = (u_min.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->min);
      union {
        bool real;
        uint8_t base;
      } u_max;
      u_max.real = this->max;
      *(outbuffer + offset + 0) = (u_max.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->max);
      union {
        bool real;
        uint8_t base;
      } u_dflt;
      u_dflt.real = this->dflt;
      *(outbuffer + offset + 0) = (u_dflt.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->dflt);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_name;
      arrToVar(length_name, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_name-1]=0;
      this->name = (char *)(inbuffer + offset-1);
      offset += length_name;
      union {
        bool real;
        uint8_t base;
      } u_value;
      u_value.base = 0;
      u_value.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->value = u_value.real;
      offset += sizeof(this->value);
      union {
        bool real;
        uint8_t base;
      } u_min;
      u_min.base = 0;
      u_min.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->min = u_min.real;
      offset += sizeof(this->min);
      union {
        bool real;
        uint8_t base;
      } u_max;
      u_max.base = 0;
      u_max.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->max = u_max.real;
      offset += sizeof(this->max);
      union {
        bool real;
        uint8_t base;
      } u_dflt;
      u_dflt.base = 0;
      u_dflt.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->dflt = u_dflt.real;
      offset += sizeof(this->dflt);
     return offset;
    }

    const char * getType(){ return "s4_msgs/BoolParamInfo"; };
    const char * getMD5(){ return "33403dc21fa65a2ccb0671aceea664ec"; };

  };

}
#endif
