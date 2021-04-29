#ifndef _ROS_s4_msgs_ActionModeStatus_h
#define _ROS_s4_msgs_ActionModeStatus_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "s4_msgs/CommandItem.h"

namespace s4_msgs
{

  class ActionModeStatus : public ros::Msg
  {
    public:
      typedef s4_msgs::CommandItem _command_type;
      _command_type command;
      typedef const char* _description_type;
      _description_type description;
      typedef bool _valid_type;
      _valid_type valid;

    ActionModeStatus():
      command(),
      description(""),
      valid(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->command.serialize(outbuffer + offset);
      uint32_t length_description = strlen(this->description);
      varToArr(outbuffer + offset, length_description);
      offset += 4;
      memcpy(outbuffer + offset, this->description, length_description);
      offset += length_description;
      union {
        bool real;
        uint8_t base;
      } u_valid;
      u_valid.real = this->valid;
      *(outbuffer + offset + 0) = (u_valid.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->valid);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->command.deserialize(inbuffer + offset);
      uint32_t length_description;
      arrToVar(length_description, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_description; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_description-1]=0;
      this->description = (char *)(inbuffer + offset-1);
      offset += length_description;
      union {
        bool real;
        uint8_t base;
      } u_valid;
      u_valid.base = 0;
      u_valid.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->valid = u_valid.real;
      offset += sizeof(this->valid);
     return offset;
    }

    const char * getType(){ return "s4_msgs/ActionModeStatus"; };
    const char * getMD5(){ return "05c799c702c645e98722d5706e67e78c"; };

  };

}
#endif
