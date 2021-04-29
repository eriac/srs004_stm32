#ifndef _ROS_s4_msgs_ConnectionReport_h
#define _ROS_s4_msgs_ConnectionReport_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace s4_msgs
{

  class ConnectionReport : public ros::Msg
  {
    public:
      typedef uint8_t _joy_state_type;
      _joy_state_type joy_state;
      enum { JOY_STATE_UNKNOWN =  0 };
      enum { JOY_STATE_DISCONNECTED =  1 };
      enum { JOY_STATE_CONNECTED =  2 };
      enum { JOY_STATE_ACTIVE =  3 };
      enum { JOY_STATE_REACH_LIMIT =  4 };

    ConnectionReport():
      joy_state(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->joy_state >> (8 * 0)) & 0xFF;
      offset += sizeof(this->joy_state);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->joy_state =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->joy_state);
     return offset;
    }

    const char * getType(){ return "s4_msgs/ConnectionReport"; };
    const char * getMD5(){ return "c8297b97de068bb42009218c4db04cfb"; };

  };

}
#endif
