#ifndef _ROS_s4_msgs_IntParamInfo_h
#define _ROS_s4_msgs_IntParamInfo_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace s4_msgs
{

  class IntParamInfo : public ros::Msg
  {
    public:
      typedef const char* _name_type;
      _name_type name;
      typedef int32_t _value_type;
      _value_type value;
      typedef int32_t _min_type;
      _min_type min;
      typedef int32_t _max_type;
      _max_type max;
      typedef int32_t _dflt_type;
      _dflt_type dflt;

    IntParamInfo():
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
        int32_t real;
        uint32_t base;
      } u_value;
      u_value.real = this->value;
      *(outbuffer + offset + 0) = (u_value.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_value.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_value.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_value.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->value);
      union {
        int32_t real;
        uint32_t base;
      } u_min;
      u_min.real = this->min;
      *(outbuffer + offset + 0) = (u_min.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_min.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_min.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_min.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->min);
      union {
        int32_t real;
        uint32_t base;
      } u_max;
      u_max.real = this->max;
      *(outbuffer + offset + 0) = (u_max.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_max.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_max.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_max.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->max);
      union {
        int32_t real;
        uint32_t base;
      } u_dflt;
      u_dflt.real = this->dflt;
      *(outbuffer + offset + 0) = (u_dflt.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_dflt.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_dflt.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_dflt.base >> (8 * 3)) & 0xFF;
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
        int32_t real;
        uint32_t base;
      } u_value;
      u_value.base = 0;
      u_value.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_value.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_value.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_value.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->value = u_value.real;
      offset += sizeof(this->value);
      union {
        int32_t real;
        uint32_t base;
      } u_min;
      u_min.base = 0;
      u_min.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_min.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_min.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_min.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->min = u_min.real;
      offset += sizeof(this->min);
      union {
        int32_t real;
        uint32_t base;
      } u_max;
      u_max.base = 0;
      u_max.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_max.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_max.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_max.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->max = u_max.real;
      offset += sizeof(this->max);
      union {
        int32_t real;
        uint32_t base;
      } u_dflt;
      u_dflt.base = 0;
      u_dflt.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_dflt.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_dflt.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_dflt.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->dflt = u_dflt.real;
      offset += sizeof(this->dflt);
     return offset;
    }

    const char * getType(){ return "s4_msgs/IntParamInfo"; };
    const char * getMD5(){ return "682fa5e958573cc166789380571d918e"; };

  };

}
#endif
