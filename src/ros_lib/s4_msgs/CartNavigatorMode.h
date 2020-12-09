#ifndef _ROS_s4_msgs_CartNavigatorMode_h
#define _ROS_s4_msgs_CartNavigatorMode_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace s4_msgs
{

  class CartNavigatorMode : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef uint8_t _mode_type;
      _mode_type mode;
      enum { MODE_NONE =  0 };
      enum { MODE_MANUAL =  1 };
      enum { MODE_AUTO =  2 };
      enum { MODE_POSITION =  3 };

    CartNavigatorMode():
      header(),
      mode(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->mode >> (8 * 0)) & 0xFF;
      offset += sizeof(this->mode);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      this->mode =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->mode);
     return offset;
    }

    const char * getType(){ return "s4_msgs/CartNavigatorMode"; };
    const char * getMD5(){ return "f20573b496f5bae6f408e185ac3a32d0"; };

  };

}
#endif
