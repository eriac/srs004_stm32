#ifndef _ROS_s4_msgs_Joy_h
#define _ROS_s4_msgs_Joy_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "s4_msgs/JoySide.h"

namespace s4_msgs
{

  class Joy : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef s4_msgs::JoySide _left_type;
      _left_type left;
      typedef s4_msgs::JoySide _right_type;
      _right_type right;
      uint32_t other_length;
      typedef double _other_type;
      _other_type st_other;
      _other_type * other;

    Joy():
      header(),
      left(),
      right(),
      other_length(0), other(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      offset += this->left.serialize(outbuffer + offset);
      offset += this->right.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->other_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->other_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->other_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->other_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->other_length);
      for( uint32_t i = 0; i < other_length; i++){
      union {
        double real;
        uint64_t base;
      } u_otheri;
      u_otheri.real = this->other[i];
      *(outbuffer + offset + 0) = (u_otheri.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_otheri.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_otheri.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_otheri.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_otheri.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_otheri.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_otheri.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_otheri.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->other[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      offset += this->left.deserialize(inbuffer + offset);
      offset += this->right.deserialize(inbuffer + offset);
      uint32_t other_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      other_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      other_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      other_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->other_length);
      if(other_lengthT > other_length)
        this->other = (double*)realloc(this->other, other_lengthT * sizeof(double));
      other_length = other_lengthT;
      for( uint32_t i = 0; i < other_length; i++){
      union {
        double real;
        uint64_t base;
      } u_st_other;
      u_st_other.base = 0;
      u_st_other.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_other.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_other.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_other.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_st_other.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_st_other.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_st_other.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_st_other.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->st_other = u_st_other.real;
      offset += sizeof(this->st_other);
        memcpy( &(this->other[i]), &(this->st_other), sizeof(double));
      }
     return offset;
    }

    const char * getType(){ return "s4_msgs/Joy"; };
    const char * getMD5(){ return "edc2864e3d94e0e90e808c672414d9b4"; };

  };

}
#endif
