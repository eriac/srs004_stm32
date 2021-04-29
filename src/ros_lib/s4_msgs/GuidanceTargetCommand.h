#ifndef _ROS_s4_msgs_GuidanceTargetCommand_h
#define _ROS_s4_msgs_GuidanceTargetCommand_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "s4_msgs/CommandItem.h"
#include "geometry_msgs/Pose2D.h"

namespace s4_msgs
{

  class GuidanceTargetCommand : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef s4_msgs::CommandItem _command_type;
      _command_type command;
      typedef geometry_msgs::Pose2D _pose2d_type;
      _pose2d_type pose2d;

    GuidanceTargetCommand():
      header(),
      command(),
      pose2d()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      offset += this->command.serialize(outbuffer + offset);
      offset += this->pose2d.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      offset += this->command.deserialize(inbuffer + offset);
      offset += this->pose2d.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "s4_msgs/GuidanceTargetCommand"; };
    const char * getMD5(){ return "23c02dad695bd4fdda4da060ca28263a"; };

  };

}
#endif
