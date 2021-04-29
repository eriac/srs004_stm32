#ifndef _ROS_s4_msgs_LedColor_h
#define _ROS_s4_msgs_LedColor_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/ColorRGBA.h"

namespace s4_msgs
{

  class LedColor : public ros::Msg
  {
    public:
      typedef uint8_t _set_mode_type;
      _set_mode_type set_mode;
      typedef std_msgs::ColorRGBA _color_type;
      _color_type color;
      enum { SET_MODE_BASE_COLOR =  1 };

    LedColor():
      set_mode(0),
      color()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->set_mode >> (8 * 0)) & 0xFF;
      offset += sizeof(this->set_mode);
      offset += this->color.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->set_mode =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->set_mode);
      offset += this->color.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "s4_msgs/LedColor"; };
    const char * getMD5(){ return "b36287c23dfb9a8714d9c4bbb14649ee"; };

  };

}
#endif
