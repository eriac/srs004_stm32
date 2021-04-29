#ifndef _ROS_s4_msgs_SwitcherActionCommand_h
#define _ROS_s4_msgs_SwitcherActionCommand_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "s4_msgs/CommandItem.h"

namespace s4_msgs
{

  class SwitcherActionCommand : public ros::Msg
  {
    public:
      typedef s4_msgs::CommandItem _command_type;
      _command_type command;

    SwitcherActionCommand():
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

    const char * getType(){ return "s4_msgs/SwitcherActionCommand"; };
    const char * getMD5(){ return "5e2be74ad1ffc1de29e033421b2401a2"; };

  };

}
#endif
