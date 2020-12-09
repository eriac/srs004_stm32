#ifndef _ROS_SERVICE_GraphSetEdge_h
#define _ROS_SERVICE_GraphSetEdge_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "s4_msgs/GraphEdge.h"

namespace s4_msgs
{

static const char GRAPHSETEDGE[] = "s4_msgs/GraphSetEdge";

  class GraphSetEdgeRequest : public ros::Msg
  {
    public:
      typedef s4_msgs::GraphEdge _item_type;
      _item_type item;
      typedef bool _remove_type;
      _remove_type remove;

    GraphSetEdgeRequest():
      item(),
      remove(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->item.serialize(outbuffer + offset);
      union {
        bool real;
        uint8_t base;
      } u_remove;
      u_remove.real = this->remove;
      *(outbuffer + offset + 0) = (u_remove.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->remove);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->item.deserialize(inbuffer + offset);
      union {
        bool real;
        uint8_t base;
      } u_remove;
      u_remove.base = 0;
      u_remove.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->remove = u_remove.real;
      offset += sizeof(this->remove);
     return offset;
    }

    const char * getType(){ return GRAPHSETEDGE; };
    const char * getMD5(){ return "23bc0e24c91ccc3a1a7f3f194cc8db54"; };

  };

  class GraphSetEdgeResponse : public ros::Msg
  {
    public:
      typedef bool _result_type;
      _result_type result;

    GraphSetEdgeResponse():
      result(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_result;
      u_result.real = this->result;
      *(outbuffer + offset + 0) = (u_result.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->result);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_result;
      u_result.base = 0;
      u_result.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->result = u_result.real;
      offset += sizeof(this->result);
     return offset;
    }

    const char * getType(){ return GRAPHSETEDGE; };
    const char * getMD5(){ return "eb13ac1f1354ccecb7941ee8fa2192e8"; };

  };

  class GraphSetEdge {
    public:
    typedef GraphSetEdgeRequest Request;
    typedef GraphSetEdgeResponse Response;
  };

}
#endif
