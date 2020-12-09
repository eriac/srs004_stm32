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
      typedef uint8_t _manual_connected_type;
      _manual_connected_type manual_connected;
      typedef uint8_t _manual_active_type;
      _manual_active_type manual_active;

    ConnectionReport():
      manual_connected(0),
      manual_active(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->manual_connected >> (8 * 0)) & 0xFF;
      offset += sizeof(this->manual_connected);
      *(outbuffer + offset + 0) = (this->manual_active >> (8 * 0)) & 0xFF;
      offset += sizeof(this->manual_active);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->manual_connected =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->manual_connected);
      this->manual_active =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->manual_active);
     return offset;
    }

    const char * getType(){ return "s4_msgs/ConnectionReport"; };
    const char * getMD5(){ return "7332e871c98cfc9edf81b4e151c941de"; };

  };

}
#endif
