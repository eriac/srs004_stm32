#ifndef _ROS_s4_msgs_GraphEdge_h
#define _ROS_s4_msgs_GraphEdge_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace s4_msgs
{

  class GraphEdge : public ros::Msg
  {
    public:
      typedef uint16_t _id1_type;
      _id1_type id1;
      typedef uint16_t _id2_type;
      _id2_type id2;

    GraphEdge():
      id1(0),
      id2(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->id1 >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->id1 >> (8 * 1)) & 0xFF;
      offset += sizeof(this->id1);
      *(outbuffer + offset + 0) = (this->id2 >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->id2 >> (8 * 1)) & 0xFF;
      offset += sizeof(this->id2);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->id1 =  ((uint16_t) (*(inbuffer + offset)));
      this->id1 |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->id1);
      this->id2 =  ((uint16_t) (*(inbuffer + offset)));
      this->id2 |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->id2);
     return offset;
    }

    const char * getType(){ return "s4_msgs/GraphEdge"; };
    const char * getMD5(){ return "e1285ad3424f5d74cd38b7aa51da680c"; };

  };

}
#endif
