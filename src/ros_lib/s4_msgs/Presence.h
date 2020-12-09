#ifndef _ROS_s4_msgs_Presence_h
#define _ROS_s4_msgs_Presence_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geometry_msgs/Pose.h"
#include "geometry_msgs/Vector3.h"
#include "std_msgs/Float64.h"

namespace s4_msgs
{

  class Presence : public ros::Msg
  {
    public:
      typedef geometry_msgs::Pose _pose_type;
      _pose_type pose;
      typedef geometry_msgs::Vector3 _velocity_type;
      _velocity_type velocity;
      typedef std_msgs::Float64 _height_type;
      _height_type height;
      typedef std_msgs::Float64 _radius_type;
      _radius_type radius;

    Presence():
      pose(),
      velocity(),
      height(),
      radius()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->pose.serialize(outbuffer + offset);
      offset += this->velocity.serialize(outbuffer + offset);
      offset += this->height.serialize(outbuffer + offset);
      offset += this->radius.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->pose.deserialize(inbuffer + offset);
      offset += this->velocity.deserialize(inbuffer + offset);
      offset += this->height.deserialize(inbuffer + offset);
      offset += this->radius.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "s4_msgs/Presence"; };
    const char * getMD5(){ return "e19bf3ea343bfec28ea348aad1c18bd1"; };

  };

}
#endif
