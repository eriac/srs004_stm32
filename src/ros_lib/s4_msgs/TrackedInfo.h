#ifndef _ROS_s4_msgs_TrackedInfo_h
#define _ROS_s4_msgs_TrackedInfo_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace s4_msgs
{

  class TrackedInfo : public ros::Msg
  {
    public:
      typedef int32_t _id_type;
      _id_type id;
      typedef const char* _category_type;
      _category_type category;
      typedef int32_t _age_type;
      _age_type age;

    TrackedInfo():
      id(0),
      category(""),
      age(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_id;
      u_id.real = this->id;
      *(outbuffer + offset + 0) = (u_id.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_id.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_id.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_id.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->id);
      uint32_t length_category = strlen(this->category);
      varToArr(outbuffer + offset, length_category);
      offset += 4;
      memcpy(outbuffer + offset, this->category, length_category);
      offset += length_category;
      union {
        int32_t real;
        uint32_t base;
      } u_age;
      u_age.real = this->age;
      *(outbuffer + offset + 0) = (u_age.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_age.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_age.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_age.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->age);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_id;
      u_id.base = 0;
      u_id.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_id.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_id.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_id.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->id = u_id.real;
      offset += sizeof(this->id);
      uint32_t length_category;
      arrToVar(length_category, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_category; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_category-1]=0;
      this->category = (char *)(inbuffer + offset-1);
      offset += length_category;
      union {
        int32_t real;
        uint32_t base;
      } u_age;
      u_age.base = 0;
      u_age.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_age.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_age.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_age.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->age = u_age.real;
      offset += sizeof(this->age);
     return offset;
    }

    const char * getType(){ return "s4_msgs/TrackedInfo"; };
    const char * getMD5(){ return "bb74324f8118dad3000e3640fee9aaaf"; };

  };

}
#endif
