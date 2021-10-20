#ifndef _ROS_s4_msgs_DoubleParamInfo_h
#define _ROS_s4_msgs_DoubleParamInfo_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace s4_msgs
{

  class DoubleParamInfo : public ros::Msg
  {
    public:
      typedef const char* _name_type;
      _name_type name;
      typedef double _value_type;
      _value_type value;
      typedef double _min_type;
      _min_type min;
      typedef double _max_type;
      _max_type max;
      typedef double _dflt_type;
      _dflt_type dflt;

    DoubleParamInfo():
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
        double real;
        uint64_t base;
      } u_value;
      u_value.real = this->value;
      *(outbuffer + offset + 0) = (u_value.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_value.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_value.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_value.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_value.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_value.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_value.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_value.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->value);
      union {
        double real;
        uint64_t base;
      } u_min;
      u_min.real = this->min;
      *(outbuffer + offset + 0) = (u_min.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_min.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_min.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_min.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_min.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_min.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_min.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_min.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->min);
      union {
        double real;
        uint64_t base;
      } u_max;
      u_max.real = this->max;
      *(outbuffer + offset + 0) = (u_max.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_max.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_max.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_max.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_max.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_max.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_max.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_max.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->max);
      union {
        double real;
        uint64_t base;
      } u_dflt;
      u_dflt.real = this->dflt;
      *(outbuffer + offset + 0) = (u_dflt.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_dflt.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_dflt.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_dflt.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_dflt.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_dflt.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_dflt.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_dflt.base >> (8 * 7)) & 0xFF;
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
        double real;
        uint64_t base;
      } u_value;
      u_value.base = 0;
      u_value.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_value.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_value.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_value.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_value.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_value.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_value.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_value.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->value = u_value.real;
      offset += sizeof(this->value);
      union {
        double real;
        uint64_t base;
      } u_min;
      u_min.base = 0;
      u_min.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_min.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_min.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_min.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_min.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_min.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_min.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_min.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->min = u_min.real;
      offset += sizeof(this->min);
      union {
        double real;
        uint64_t base;
      } u_max;
      u_max.base = 0;
      u_max.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_max.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_max.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_max.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_max.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_max.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_max.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_max.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->max = u_max.real;
      offset += sizeof(this->max);
      union {
        double real;
        uint64_t base;
      } u_dflt;
      u_dflt.base = 0;
      u_dflt.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_dflt.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_dflt.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_dflt.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_dflt.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_dflt.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_dflt.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_dflt.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->dflt = u_dflt.real;
      offset += sizeof(this->dflt);
     return offset;
    }

    const char * getType(){ return "s4_msgs/DoubleParamInfo"; };
    const char * getMD5(){ return "f153fde139aedbedc29131e84dfd8c43"; };

  };

}
#endif
