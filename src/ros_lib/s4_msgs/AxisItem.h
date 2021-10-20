#ifndef _ROS_s4_msgs_AxisItem_h
#define _ROS_s4_msgs_AxisItem_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace s4_msgs
{

  class AxisItem : public ros::Msg
  {
    public:
      typedef uint8_t _assign_type;
      _assign_type assign;
      typedef float _value_type;
      _value_type value;
      enum { ASSIGN_NONE =  0 };
      enum { ASSIGN_MOVE_LINEAR_X =  1 };
      enum { ASSIGN_MOVE_LINEAR_Y =  2 };
      enum { ASSIGN_MOVE_LINEAR_Z =  3 };
      enum { ASSIGN_MOVE_YAW =  4 };

    AxisItem():
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
        float real;
        uint32_t base;
      } u_value;
      u_value.real = this->value;
      *(outbuffer + offset + 0) = (u_value.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_value.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_value.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_value.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->value);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->assign =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->assign);
      union {
        float real;
        uint32_t base;
      } u_value;
      u_value.base = 0;
      u_value.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_value.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_value.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_value.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->value = u_value.real;
      offset += sizeof(this->value);
     return offset;
    }

    const char * getType(){ return "s4_msgs/AxisItem"; };
    const char * getMD5(){ return "c264f62543f746a38b5e89571b08e4ed"; };

  };

}
#endif
