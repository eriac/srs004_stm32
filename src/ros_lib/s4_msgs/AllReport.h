#ifndef _ROS_s4_msgs_AllReport_h
#define _ROS_s4_msgs_AllReport_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "s4_msgs/ConnectionReport.h"

namespace s4_msgs
{

  class AllReport : public ros::Msg
  {
    public:
      typedef s4_msgs::ConnectionReport _connection_type;
      _connection_type connection;
      typedef uint8_t _mode_type;
      _mode_type mode;

    AllReport():
      connection(),
      mode(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->connection.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->mode >> (8 * 0)) & 0xFF;
      offset += sizeof(this->mode);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->connection.deserialize(inbuffer + offset);
      this->mode =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->mode);
     return offset;
    }

    const char * getType(){ return "s4_msgs/AllReport"; };
    const char * getMD5(){ return "e67660415c04ae5f66bab0c65f9a8543"; };

  };

}
#endif
