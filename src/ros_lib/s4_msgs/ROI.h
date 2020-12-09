#ifndef _ROS_s4_msgs_ROI_h
#define _ROS_s4_msgs_ROI_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace s4_msgs
{

  class ROI : public ros::Msg
  {
    public:
      typedef const char* _camera_name_type;
      _camera_name_type camera_name;
      typedef uint32_t _x_offset_type;
      _x_offset_type x_offset;
      typedef uint32_t _y_offset_type;
      _y_offset_type y_offset;
      typedef uint32_t _height_type;
      _height_type height;
      typedef uint32_t _width_type;
      _width_type width;

    ROI():
      camera_name(""),
      x_offset(0),
      y_offset(0),
      height(0),
      width(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_camera_name = strlen(this->camera_name);
      varToArr(outbuffer + offset, length_camera_name);
      offset += 4;
      memcpy(outbuffer + offset, this->camera_name, length_camera_name);
      offset += length_camera_name;
      *(outbuffer + offset + 0) = (this->x_offset >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->x_offset >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->x_offset >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->x_offset >> (8 * 3)) & 0xFF;
      offset += sizeof(this->x_offset);
      *(outbuffer + offset + 0) = (this->y_offset >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->y_offset >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->y_offset >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->y_offset >> (8 * 3)) & 0xFF;
      offset += sizeof(this->y_offset);
      *(outbuffer + offset + 0) = (this->height >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->height >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->height >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->height >> (8 * 3)) & 0xFF;
      offset += sizeof(this->height);
      *(outbuffer + offset + 0) = (this->width >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->width >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->width >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->width >> (8 * 3)) & 0xFF;
      offset += sizeof(this->width);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_camera_name;
      arrToVar(length_camera_name, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_camera_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_camera_name-1]=0;
      this->camera_name = (char *)(inbuffer + offset-1);
      offset += length_camera_name;
      this->x_offset =  ((uint32_t) (*(inbuffer + offset)));
      this->x_offset |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->x_offset |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->x_offset |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->x_offset);
      this->y_offset =  ((uint32_t) (*(inbuffer + offset)));
      this->y_offset |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->y_offset |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->y_offset |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->y_offset);
      this->height =  ((uint32_t) (*(inbuffer + offset)));
      this->height |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->height |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->height |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->height);
      this->width =  ((uint32_t) (*(inbuffer + offset)));
      this->width |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->width |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->width |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->width);
     return offset;
    }

    const char * getType(){ return "s4_msgs/ROI"; };
    const char * getMD5(){ return "27a63b21f36e80ef87d81e946e0ace56"; };

  };

}
#endif
