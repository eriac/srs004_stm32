#ifndef _ROS_s4_msgs_GuidanceCommand_h
#define _ROS_s4_msgs_GuidanceCommand_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "geometry_msgs/Pose2D.h"

namespace s4_msgs
{

  class GuidanceCommand : public ros::Msg
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
      enum { MODE_TOPO =  2 };
      enum { MODE_FILLOW =  2 };

    GuidanceCommand():
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

    const char * getType(){ return "s4_msgs/GuidanceCommand"; };
    const char * getMD5(){ return "cd6cf12820c83388f72ea2e4e711c723"; };

  };

}
#endif
