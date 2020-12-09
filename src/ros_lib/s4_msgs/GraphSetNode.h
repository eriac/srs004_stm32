#ifndef _ROS_SERVICE_GraphSetNode_h
#define _ROS_SERVICE_GraphSetNode_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "s4_msgs/GraphNode.h"

namespace s4_msgs
{

static const char GRAPHSETNODE[] = "s4_msgs/GraphSetNode";

  class GraphSetNodeRequest : public ros::Msg
  {
    public:
      typedef s4_msgs::GraphNode _item_type;
      _item_type item;
      typedef bool _remove_type;
      _remove_type remove;

    GraphSetNodeRequest():
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

    const char * getType(){ return GRAPHSETNODE; };
    const char * getMD5(){ return "5c2a14bd1eb9d5159c2ba77b52dc7aed"; };

  };

  class GraphSetNodeResponse : public ros::Msg
  {
    public:
      typedef bool _result_type;
      _result_type result;

    GraphSetNodeResponse():
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

    const char * getType(){ return GRAPHSETNODE; };
    const char * getMD5(){ return "eb13ac1f1354ccecb7941ee8fa2192e8"; };

  };

  class GraphSetNode {
    public:
    typedef GraphSetNodeRequest Request;
    typedef GraphSetNodeResponse Response;
  };

}
#endif
