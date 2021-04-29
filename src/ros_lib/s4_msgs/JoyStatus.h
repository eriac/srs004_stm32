#ifndef _ROS_s4_msgs_JoyStatus_h
#define _ROS_s4_msgs_JoyStatus_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace s4_msgs
{

  class JoyStatus : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef const char* _axis_x_assign_type;
      _axis_x_assign_type axis_x_assign;
      typedef const char* _axis_y_assign_type;
      _axis_y_assign_type axis_y_assign;
      typedef const char* _axis_z_assign_type;
      _axis_z_assign_type axis_z_assign;
      typedef const char* _axis_r_assign_type;
      _axis_r_assign_type axis_r_assign;

    JoyStatus():
      header(),
      axis_x_assign(""),
      axis_y_assign(""),
      axis_z_assign(""),
      axis_r_assign("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      uint32_t length_axis_x_assign = strlen(this->axis_x_assign);
      varToArr(outbuffer + offset, length_axis_x_assign);
      offset += 4;
      memcpy(outbuffer + offset, this->axis_x_assign, length_axis_x_assign);
      offset += length_axis_x_assign;
      uint32_t length_axis_y_assign = strlen(this->axis_y_assign);
      varToArr(outbuffer + offset, length_axis_y_assign);
      offset += 4;
      memcpy(outbuffer + offset, this->axis_y_assign, length_axis_y_assign);
      offset += length_axis_y_assign;
      uint32_t length_axis_z_assign = strlen(this->axis_z_assign);
      varToArr(outbuffer + offset, length_axis_z_assign);
      offset += 4;
      memcpy(outbuffer + offset, this->axis_z_assign, length_axis_z_assign);
      offset += length_axis_z_assign;
      uint32_t length_axis_r_assign = strlen(this->axis_r_assign);
      varToArr(outbuffer + offset, length_axis_r_assign);
      offset += 4;
      memcpy(outbuffer + offset, this->axis_r_assign, length_axis_r_assign);
      offset += length_axis_r_assign;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      uint32_t length_axis_x_assign;
      arrToVar(length_axis_x_assign, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_axis_x_assign; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_axis_x_assign-1]=0;
      this->axis_x_assign = (char *)(inbuffer + offset-1);
      offset += length_axis_x_assign;
      uint32_t length_axis_y_assign;
      arrToVar(length_axis_y_assign, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_axis_y_assign; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_axis_y_assign-1]=0;
      this->axis_y_assign = (char *)(inbuffer + offset-1);
      offset += length_axis_y_assign;
      uint32_t length_axis_z_assign;
      arrToVar(length_axis_z_assign, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_axis_z_assign; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_axis_z_assign-1]=0;
      this->axis_z_assign = (char *)(inbuffer + offset-1);
      offset += length_axis_z_assign;
      uint32_t length_axis_r_assign;
      arrToVar(length_axis_r_assign, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_axis_r_assign; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_axis_r_assign-1]=0;
      this->axis_r_assign = (char *)(inbuffer + offset-1);
      offset += length_axis_r_assign;
     return offset;
    }

    const char * getType(){ return "s4_msgs/JoyStatus"; };
    const char * getMD5(){ return "1ddae450b2da78762c879df0c49c0cc0"; };

  };

}
#endif
