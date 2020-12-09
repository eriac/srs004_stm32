#ifndef _ROS_s4_msgs_TrackedRayArray_h
#define _ROS_s4_msgs_TrackedRayArray_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "s4_msgs/TrackedRay.h"

namespace s4_msgs
{

  class TrackedRayArray : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      uint32_t rays_length;
      typedef s4_msgs::TrackedRay _rays_type;
      _rays_type st_rays;
      _rays_type * rays;

    TrackedRayArray():
      header(),
      rays_length(0), rays(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->rays_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->rays_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->rays_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->rays_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->rays_length);
      for( uint32_t i = 0; i < rays_length; i++){
      offset += this->rays[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      uint32_t rays_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      rays_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      rays_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      rays_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->rays_length);
      if(rays_lengthT > rays_length)
        this->rays = (s4_msgs::TrackedRay*)realloc(this->rays, rays_lengthT * sizeof(s4_msgs::TrackedRay));
      rays_length = rays_lengthT;
      for( uint32_t i = 0; i < rays_length; i++){
      offset += this->st_rays.deserialize(inbuffer + offset);
        memcpy( &(this->rays[i]), &(this->st_rays), sizeof(s4_msgs::TrackedRay));
      }
     return offset;
    }

    const char * getType(){ return "s4_msgs/TrackedRayArray"; };
    const char * getMD5(){ return "60588295784d64ecf98560a42be72d74"; };

  };

}
#endif
