#ifndef _ROS_s4_msgs_GraphPose_h
#define _ROS_s4_msgs_GraphPose_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "geometry_msgs/Pose2D.h"
#include "s4_msgs/Graph.h"

namespace s4_msgs
{

  class GraphPose : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef bool _valid_type;
      _valid_type valid;
      typedef geometry_msgs::Pose2D _pose_type;
      _pose_type pose;
      typedef int32_t _nearest_node_type;
      _nearest_node_type nearest_node;
      uint32_t nearest_edge_length;
      typedef int32_t _nearest_edge_type;
      _nearest_edge_type st_nearest_edge;
      _nearest_edge_type * nearest_edge;
      typedef float _scale_type;
      _scale_type scale;
      typedef s4_msgs::Graph _scaled_graph_type;
      _scaled_graph_type scaled_graph;

    GraphPose():
      header(),
      valid(0),
      pose(),
      nearest_node(0),
      nearest_edge_length(0), nearest_edge(NULL),
      scale(0),
      scaled_graph()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      union {
        bool real;
        uint8_t base;
      } u_valid;
      u_valid.real = this->valid;
      *(outbuffer + offset + 0) = (u_valid.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->valid);
      offset += this->pose.serialize(outbuffer + offset);
      union {
        int32_t real;
        uint32_t base;
      } u_nearest_node;
      u_nearest_node.real = this->nearest_node;
      *(outbuffer + offset + 0) = (u_nearest_node.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_nearest_node.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_nearest_node.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_nearest_node.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->nearest_node);
      *(outbuffer + offset + 0) = (this->nearest_edge_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->nearest_edge_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->nearest_edge_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->nearest_edge_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->nearest_edge_length);
      for( uint32_t i = 0; i < nearest_edge_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_nearest_edgei;
      u_nearest_edgei.real = this->nearest_edge[i];
      *(outbuffer + offset + 0) = (u_nearest_edgei.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_nearest_edgei.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_nearest_edgei.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_nearest_edgei.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->nearest_edge[i]);
      }
      union {
        float real;
        uint32_t base;
      } u_scale;
      u_scale.real = this->scale;
      *(outbuffer + offset + 0) = (u_scale.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_scale.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_scale.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_scale.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->scale);
      offset += this->scaled_graph.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      union {
        bool real;
        uint8_t base;
      } u_valid;
      u_valid.base = 0;
      u_valid.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->valid = u_valid.real;
      offset += sizeof(this->valid);
      offset += this->pose.deserialize(inbuffer + offset);
      union {
        int32_t real;
        uint32_t base;
      } u_nearest_node;
      u_nearest_node.base = 0;
      u_nearest_node.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_nearest_node.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_nearest_node.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_nearest_node.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->nearest_node = u_nearest_node.real;
      offset += sizeof(this->nearest_node);
      uint32_t nearest_edge_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      nearest_edge_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      nearest_edge_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      nearest_edge_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->nearest_edge_length);
      if(nearest_edge_lengthT > nearest_edge_length)
        this->nearest_edge = (int32_t*)realloc(this->nearest_edge, nearest_edge_lengthT * sizeof(int32_t));
      nearest_edge_length = nearest_edge_lengthT;
      for( uint32_t i = 0; i < nearest_edge_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_st_nearest_edge;
      u_st_nearest_edge.base = 0;
      u_st_nearest_edge.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_nearest_edge.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_nearest_edge.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_nearest_edge.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_nearest_edge = u_st_nearest_edge.real;
      offset += sizeof(this->st_nearest_edge);
        memcpy( &(this->nearest_edge[i]), &(this->st_nearest_edge), sizeof(int32_t));
      }
      union {
        float real;
        uint32_t base;
      } u_scale;
      u_scale.base = 0;
      u_scale.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_scale.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_scale.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_scale.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->scale = u_scale.real;
      offset += sizeof(this->scale);
      offset += this->scaled_graph.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "s4_msgs/GraphPose"; };
    const char * getMD5(){ return "5de1a42f14dabfe99567a045c4534a7f"; };

  };

}
#endif
