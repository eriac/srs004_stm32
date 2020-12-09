#ifndef _ROS_SERVICE_GraphRequest_h
#define _ROS_SERVICE_GraphRequest_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "s4_msgs/Graph.h"

namespace s4_msgs
{

static const char GRAPHREQUEST[] = "s4_msgs/GraphRequest";

  class GraphRequestRequest : public ros::Msg
  {
    public:
      typedef bool _set_default_type;
      _set_default_type set_default;

    GraphRequestRequest():
      set_default(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_set_default;
      u_set_default.real = this->set_default;
      *(outbuffer + offset + 0) = (u_set_default.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->set_default);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_set_default;
      u_set_default.base = 0;
      u_set_default.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->set_default = u_set_default.real;
      offset += sizeof(this->set_default);
     return offset;
    }

    const char * getType(){ return GRAPHREQUEST; };
    const char * getMD5(){ return "cf21403bf6ca4ebf0791d4435cc279a4"; };

  };

  class GraphRequestResponse : public ros::Msg
  {
    public:
      typedef s4_msgs::Graph _graph_type;
      _graph_type graph;

    GraphRequestResponse():
      graph()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->graph.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->graph.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return GRAPHREQUEST; };
    const char * getMD5(){ return "98788a101a0c7f63f3a193902ef35225"; };

  };

  class GraphRequest {
    public:
    typedef GraphRequestRequest Request;
    typedef GraphRequestResponse Response;
  };

}
#endif
