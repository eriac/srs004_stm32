#ifndef _ROS_s4_msgs_GuidanceActionCommand_h
#define _ROS_s4_msgs_GuidanceActionCommand_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "s4_msgs/CommandItem.h"
#include "geometry_msgs/Pose2D.h"

namespace s4_msgs
{

  class GuidanceActionCommand : public ros::Msg
  {
    public:
      typedef s4_msgs::CommandItem _command_type;
      _command_type command;
      typedef geometry_msgs::Pose2D _pose_2d_type;
      _pose_2d_type pose_2d;

    GuidanceActionCommand():
      command(),
      pose_2d()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->command.serialize(outbuffer + offset);
      offset += this->pose_2d.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->command.deserialize(inbuffer + offset);
      offset += this->pose_2d.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "s4_msgs/GuidanceActionCommand"; };
    const char * getMD5(){ return "558f114de7ae8c71d0eb0b94e5a7cbd3"; };

  };

}
#endif
