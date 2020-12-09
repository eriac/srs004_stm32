#ifndef _ROS_s4_msgs_CollectorCommand_h
#define _ROS_s4_msgs_CollectorCommand_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace s4_msgs
{

  class CollectorCommand : public ros::Msg
  {
    public:
      typedef uint8_t _type_type;
      _type_type type;
      enum { TYPE_HEAD_CAMERA =  1 };
      enum { TYPE_MAP =  2 };

    CollectorCommand():
      type(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->type >> (8 * 0)) & 0xFF;
      offset += sizeof(this->type);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->type =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->type);
     return offset;
    }

    const char * getType(){ return "s4_msgs/CollectorCommand"; };
    const char * getMD5(){ return "7129940c7138276c60e751f458598088"; };

  };

}
#endif
