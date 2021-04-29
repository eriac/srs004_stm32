#ifndef _ROS_s4_msgs_FocusCommand_h
#define _ROS_s4_msgs_FocusCommand_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace s4_msgs
{

  class FocusCommand : public ros::Msg
  {
    public:
      typedef uint8_t _command_type;
      _command_type command;
      typedef const char* _category_type;
      _category_type category;
      typedef int32_t _id_type;
      _id_type id;
      enum { COMMAND_SET_FOCUS =  1 };
      enum { COMMAND_CLEAR_FOCUS =  2 };

    FocusCommand():
      command(0),
      category(""),
      id(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->command >> (8 * 0)) & 0xFF;
      offset += sizeof(this->command);
      uint32_t length_category = strlen(this->category);
      varToArr(outbuffer + offset, length_category);
      offset += 4;
      memcpy(outbuffer + offset, this->category, length_category);
      offset += length_category;
      union {
        int32_t real;
        uint32_t base;
      } u_id;
      u_id.real = this->id;
      *(outbuffer + offset + 0) = (u_id.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_id.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_id.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_id.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->id);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->command =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->command);
      uint32_t length_category;
      arrToVar(length_category, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_category; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_category-1]=0;
      this->category = (char *)(inbuffer + offset-1);
      offset += length_category;
      union {
        int32_t real;
        uint32_t base;
      } u_id;
      u_id.base = 0;
      u_id.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_id.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_id.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_id.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->id = u_id.real;
      offset += sizeof(this->id);
     return offset;
    }

    const char * getType(){ return "s4_msgs/FocusCommand"; };
    const char * getMD5(){ return "1735fc3bc979fef62d9833916da892df"; };

  };

}
#endif
