#ifndef _ROS_s4_msgs_RobotStatus_h
#define _ROS_s4_msgs_RobotStatus_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "s4_msgs/CommanderStatus.h"

namespace s4_msgs
{

  class RobotStatus : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef s4_msgs::CommanderStatus _commander_status_type;
      _commander_status_type commander_status;

    RobotStatus():
      header(),
      commander_status()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      offset += this->commander_status.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      offset += this->commander_status.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "s4_msgs/RobotStatus"; };
    const char * getMD5(){ return "1df88873bef3a354e0c7cd054fb9f1a6"; };

  };

}
#endif
