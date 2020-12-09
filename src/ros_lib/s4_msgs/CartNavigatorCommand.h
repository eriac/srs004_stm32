#ifndef _ROS_s4_msgs_CartNavigatorCommand_h
#define _ROS_s4_msgs_CartNavigatorCommand_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "geometry_msgs/Pose2D.h"

namespace s4_msgs
{

  class CartNavigatorCommand : public ros::Msg
  {
    public:
      typedef uint8_t _mode_type;
      _mode_type mode;
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef geometry_msgs::Pose2D _pose2d_type;
      _pose2d_type pose2d;
      enum { MODE_STOP =  0 };
      enum { MODE_MANUAL =  1 };
      enum { MODE_POSITION =  2 };
      enum { MODE_YAW =  3 };

    CartNavigatorCommand():
      mode(0),
      header(),
      pose2d()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->mode >> (8 * 0)) & 0xFF;
      offset += sizeof(this->mode);
      offset += this->header.serialize(outbuffer + offset);
      offset += this->pose2d.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->mode =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->mode);
      offset += this->header.deserialize(inbuffer + offset);
      offset += this->pose2d.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "s4_msgs/CartNavigatorCommand"; };
    const char * getMD5(){ return "1ee90e6a85130c1c0f76c8c5ca34a1fa"; };

  };

}
#endif
