#ifndef _ROS_s4_msgs_ButtonItem_h
#define _ROS_s4_msgs_ButtonItem_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace s4_msgs
{

  class ButtonItem : public ros::Msg
  {
    public:
      typedef uint8_t _assign_type;
      _assign_type assign;
      typedef bool _value_type;
      _value_type value;
      enum { BUTTON_ASSIGN_NONE =  0 };

    ButtonItem():
      assign(0),
      value(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->assign >> (8 * 0)) & 0xFF;
      offset += sizeof(this->assign);
      union {
        bool real;
        uint8_t base;
      } u_value;
      u_value.real = this->value;
      *(outbuffer + offset + 0) = (u_value.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->value);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->assign =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->assign);
      union {
        bool real;
        uint8_t base;
      } u_value;
      u_value.base = 0;
      u_value.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->value = u_value.real;
      offset += sizeof(this->value);
     return offset;
    }

    const char * getType(){ return "s4_msgs/ButtonItem"; };
    const char * getMD5(){ return "d5556633358d802e6732faae941789ad"; };

  };

}
#endif
