#ifndef _ROS_SERVICE_RobotService_h
#define _ROS_SERVICE_RobotService_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "s4_msgs/RobotAck.h"
#include "s4_msgs/RobotCommand.h"

namespace s4_msgs
{

static const char ROBOTSERVICE[] = "s4_msgs/RobotService";

  class RobotServiceRequest : public ros::Msg
  {
    public:
      typedef s4_msgs::RobotCommand _command_type;
      _command_type command;

    RobotServiceRequest():
      command()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->command.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->command.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return ROBOTSERVICE; };
    const char * getMD5(){ return "81758a039edb56526f44bff8a6688c3e"; };

  };

  class RobotServiceResponse : public ros::Msg
  {
    public:
      typedef s4_msgs::RobotAck _ack_type;
      _ack_type ack;

    RobotServiceResponse():
      ack()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->ack.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->ack.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return ROBOTSERVICE; };
    const char * getMD5(){ return "cd11cb4955b4ad4d465fa3f4930f1ddc"; };

  };

  class RobotService {
    public:
    typedef RobotServiceRequest Request;
    typedef RobotServiceResponse Response;
  };

}
#endif
