#ifndef _ROS_s4_msgs_Item2d_h
#define _ROS_s4_msgs_Item2d_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geometry_msgs/Pose2D.h"

namespace s4_msgs
{

  class Item2d : public ros::Msg
  {
    public:
      typedef uint16_t _id_type;
      _id_type id;
      typedef geometry_msgs::Pose2D _pose_type;
      _pose_type pose;

    Item2d():
      id(0),
      pose()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->id >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->id >> (8 * 1)) & 0xFF;
      offset += sizeof(this->id);
      offset += this->pose.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->id =  ((uint16_t) (*(inbuffer + offset)));
      this->id |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->id);
      offset += this->pose.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "s4_msgs/Item2d"; };
    const char * getMD5(){ return "e7129b0fa6958199b1ccb899ff3951c8"; };

  };

}
#endif
