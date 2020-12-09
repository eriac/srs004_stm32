#ifndef _ROS_s4_msgs_Graph_h
#define _ROS_s4_msgs_Graph_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "s4_msgs/GraphNode.h"
#include "s4_msgs/GraphEdge.h"

namespace s4_msgs
{

  class Graph : public ros::Msg
  {
    public:
      uint32_t nodes_length;
      typedef s4_msgs::GraphNode _nodes_type;
      _nodes_type st_nodes;
      _nodes_type * nodes;
      uint32_t edges_length;
      typedef s4_msgs::GraphEdge _edges_type;
      _edges_type st_edges;
      _edges_type * edges;

    Graph():
      nodes_length(0), nodes(NULL),
      edges_length(0), edges(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->nodes_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->nodes_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->nodes_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->nodes_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->nodes_length);
      for( uint32_t i = 0; i < nodes_length; i++){
      offset += this->nodes[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset + 0) = (this->edges_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->edges_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->edges_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->edges_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->edges_length);
      for( uint32_t i = 0; i < edges_length; i++){
      offset += this->edges[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t nodes_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      nodes_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      nodes_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      nodes_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->nodes_length);
      if(nodes_lengthT > nodes_length)
        this->nodes = (s4_msgs::GraphNode*)realloc(this->nodes, nodes_lengthT * sizeof(s4_msgs::GraphNode));
      nodes_length = nodes_lengthT;
      for( uint32_t i = 0; i < nodes_length; i++){
      offset += this->st_nodes.deserialize(inbuffer + offset);
        memcpy( &(this->nodes[i]), &(this->st_nodes), sizeof(s4_msgs::GraphNode));
      }
      uint32_t edges_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      edges_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      edges_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      edges_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->edges_length);
      if(edges_lengthT > edges_length)
        this->edges = (s4_msgs::GraphEdge*)realloc(this->edges, edges_lengthT * sizeof(s4_msgs::GraphEdge));
      edges_length = edges_lengthT;
      for( uint32_t i = 0; i < edges_length; i++){
      offset += this->st_edges.deserialize(inbuffer + offset);
        memcpy( &(this->edges[i]), &(this->st_edges), sizeof(s4_msgs::GraphEdge));
      }
     return offset;
    }

    const char * getType(){ return "s4_msgs/Graph"; };
    const char * getMD5(){ return "7d4dcc13395d9e8ff4218fd2df66516a"; };

  };

}
#endif
