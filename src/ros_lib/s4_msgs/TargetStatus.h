#ifndef _ROS_s4_msgs_TargetStatus_h
#define _ROS_s4_msgs_TargetStatus_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace s4_msgs
{

  class TargetStatus : public ros::Msg
  {
    public:
      typedef uint32_t _hit_count_type;
      _hit_count_type hit_count;

    TargetStatus():
      hit_count(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->hit_count >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->hit_count >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->hit_count >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->hit_count >> (8 * 3)) & 0xFF;
      offset += sizeof(this->hit_count);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->hit_count =  ((uint32_t) (*(inbuffer + offset)));
      this->hit_count |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->hit_count |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->hit_count |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->hit_count);
     return offset;
    }

    const char * getType(){ return "s4_msgs/TargetStatus"; };
    const char * getMD5(){ return "d2a5ba0ef6561e3f4314e20e8bfc25a8"; };

  };

}
#endif
