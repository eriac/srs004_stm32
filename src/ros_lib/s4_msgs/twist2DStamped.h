#ifndef _ROS_s4_msgs_twist2DStamped_h
#define _ROS_s4_msgs_twist2DStamped_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "s4_msgs/twist2D.h"

namespace s4_msgs
{

  class twist2DStamped : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef s4_msgs::twist2D _twist_type;
      _twist_type twist;

    twist2DStamped():
      header(),
      twist()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      offset += this->twist.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      offset += this->twist.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "s4_msgs/twist2DStamped"; };
    const char * getMD5(){ return "745d448630ae50a94bdd805e8227691a"; };

  };

}
#endif
