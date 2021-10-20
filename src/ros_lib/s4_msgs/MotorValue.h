#ifndef _ROS_s4_msgs_MotorValue_h
#define _ROS_s4_msgs_MotorValue_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace s4_msgs
{

  class MotorValue : public ros::Msg
  {
    public:
      typedef float _mot0_type;
      _mot0_type mot0;
      typedef float _mot1_type;
      _mot1_type mot1;
      typedef float _mot2_type;
      _mot2_type mot2;
      typedef float _mot3_type;
      _mot3_type mot3;

    MotorValue():
      mot0(0),
      mot1(0),
      mot2(0),
      mot3(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_mot0;
      u_mot0.real = this->mot0;
      *(outbuffer + offset + 0) = (u_mot0.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_mot0.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_mot0.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_mot0.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->mot0);
      union {
        float real;
        uint32_t base;
      } u_mot1;
      u_mot1.real = this->mot1;
      *(outbuffer + offset + 0) = (u_mot1.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_mot1.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_mot1.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_mot1.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->mot1);
      union {
        float real;
        uint32_t base;
      } u_mot2;
      u_mot2.real = this->mot2;
      *(outbuffer + offset + 0) = (u_mot2.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_mot2.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_mot2.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_mot2.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->mot2);
      union {
        float real;
        uint32_t base;
      } u_mot3;
      u_mot3.real = this->mot3;
      *(outbuffer + offset + 0) = (u_mot3.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_mot3.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_mot3.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_mot3.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->mot3);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_mot0;
      u_mot0.base = 0;
      u_mot0.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_mot0.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_mot0.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_mot0.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->mot0 = u_mot0.real;
      offset += sizeof(this->mot0);
      union {
        float real;
        uint32_t base;
      } u_mot1;
      u_mot1.base = 0;
      u_mot1.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_mot1.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_mot1.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_mot1.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->mot1 = u_mot1.real;
      offset += sizeof(this->mot1);
      union {
        float real;
        uint32_t base;
      } u_mot2;
      u_mot2.base = 0;
      u_mot2.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_mot2.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_mot2.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_mot2.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->mot2 = u_mot2.real;
      offset += sizeof(this->mot2);
      union {
        float real;
        uint32_t base;
      } u_mot3;
      u_mot3.base = 0;
      u_mot3.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_mot3.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_mot3.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_mot3.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->mot3 = u_mot3.real;
      offset += sizeof(this->mot3);
     return offset;
    }

    const char * getType(){ return "s4_msgs/MotorValue"; };
    const char * getMD5(){ return "d45d712fd01101fdb242c91465aaaf95"; };

  };

}
#endif
