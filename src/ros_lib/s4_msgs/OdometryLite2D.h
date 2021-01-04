#ifndef _ROS_s4_msgs_OdometryLite2D_h
#define _ROS_s4_msgs_OdometryLite2D_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "geometry_msgs/Pose2D.h"
#include "s4_msgs/twist2D.h"

namespace s4_msgs
{

  class OdometryLite2D : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef geometry_msgs::Pose2D _pose_type;
      _pose_type pose;
      typedef s4_msgs::twist2D _twist_type;
      _twist_type twist;

    OdometryLite2D():
      header(),
      pose(),
      twist()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      offset += this->pose.serialize(outbuffer + offset);
      offset += this->twist.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      offset += this->pose.deserialize(inbuffer + offset);
      offset += this->twist.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "s4_msgs/OdometryLite2D"; };
    const char * getMD5(){ return "7ff57babefd512ec42c8fac47d746056"; };

  };

}
#endif
