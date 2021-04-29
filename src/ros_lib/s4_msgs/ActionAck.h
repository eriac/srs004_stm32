#ifndef _ROS_s4_msgs_ActionAck_h
#define _ROS_s4_msgs_ActionAck_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "s4_msgs/CommandItem.h"

namespace s4_msgs
{

  class ActionAck : public ros::Msg
  {
    public:
      typedef s4_msgs::CommandItem _command_type;
      _command_type command;
      typedef bool _success_type;
      _success_type success;

    ActionAck():
      command(),
      success(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->command.serialize(outbuffer + offset);
      union {
        bool real;
        uint8_t base;
      } u_success;
      u_success.real = this->success;
      *(outbuffer + offset + 0) = (u_success.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->success);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->command.deserialize(inbuffer + offset);
      union {
        bool real;
        uint8_t base;
      } u_success;
      u_success.base = 0;
      u_success.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->success = u_success.real;
      offset += sizeof(this->success);
     return offset;
    }

    const char * getType(){ return "s4_msgs/ActionAck"; };
    const char * getMD5(){ return "7b5a1e7080a8d5d84681586e2997d384"; };

  };

}
#endif
