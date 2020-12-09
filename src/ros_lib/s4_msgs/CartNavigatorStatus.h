#ifndef _ROS_s4_msgs_CartNavigatorStatus_h
#define _ROS_s4_msgs_CartNavigatorStatus_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace s4_msgs
{

  class CartNavigatorStatus : public ros::Msg
  {
    public:
      typedef uint8_t _mode_type;
      _mode_type mode;

    CartNavigatorStatus():
      mode(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->mode >> (8 * 0)) & 0xFF;
      offset += sizeof(this->mode);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->mode =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->mode);
     return offset;
    }

    const char * getType(){ return "s4_msgs/CartNavigatorStatus"; };
    const char * getMD5(){ return "89b81386720be1cd0ce7a3953fcd1b19"; };

  };

}
#endif
