#ifndef _ROS_s4_msgs_JoyCon_h
#define _ROS_s4_msgs_JoyCon_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace s4_msgs
{

  class JoyCon : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef float _x_type;
      _x_type x;
      typedef float _y_type;
      _y_type y;
      typedef float _z_type;
      _z_type z;
      typedef float _r_type;
      _r_type r;
      typedef float _LT_type;
      _LT_type LT;
      typedef float _RT_type;
      _RT_type RT;
      typedef int32_t _hat_type;
      _hat_type hat;
      typedef uint8_t _triangle_type;
      _triangle_type triangle;
      typedef uint8_t _circle_type;
      _circle_type circle;
      typedef int8_t _square_type;
      _square_type square;
      typedef uint8_t _cross_type;
      _cross_type cross;
      typedef uint8_t _L1_type;
      _L1_type L1;
      typedef uint8_t _L2_type;
      _L2_type L2;
      typedef uint8_t _L3_type;
      _L3_type L3;
      typedef uint8_t _R1_type;
      _R1_type R1;
      typedef uint8_t _R2_type;
      _R2_type R2;
      typedef uint8_t _R3_type;
      _R3_type R3;

    JoyCon():
      header(),
      x(0),
      y(0),
      z(0),
      r(0),
      LT(0),
      RT(0),
      hat(0),
      triangle(0),
      circle(0),
      square(0),
      cross(0),
      L1(0),
      L2(0),
      L3(0),
      R1(0),
      R2(0),
      R3(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      union {
        float real;
        uint32_t base;
      } u_x;
      u_x.real = this->x;
      *(outbuffer + offset + 0) = (u_x.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_x.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_x.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_x.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->x);
      union {
        float real;
        uint32_t base;
      } u_y;
      u_y.real = this->y;
      *(outbuffer + offset + 0) = (u_y.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_y.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_y.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_y.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->y);
      union {
        float real;
        uint32_t base;
      } u_z;
      u_z.real = this->z;
      *(outbuffer + offset + 0) = (u_z.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_z.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_z.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_z.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->z);
      union {
        float real;
        uint32_t base;
      } u_r;
      u_r.real = this->r;
      *(outbuffer + offset + 0) = (u_r.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_r.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_r.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_r.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->r);
      union {
        float real;
        uint32_t base;
      } u_LT;
      u_LT.real = this->LT;
      *(outbuffer + offset + 0) = (u_LT.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_LT.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_LT.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_LT.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->LT);
      union {
        float real;
        uint32_t base;
      } u_RT;
      u_RT.real = this->RT;
      *(outbuffer + offset + 0) = (u_RT.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_RT.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_RT.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_RT.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->RT);
      union {
        int32_t real;
        uint32_t base;
      } u_hat;
      u_hat.real = this->hat;
      *(outbuffer + offset + 0) = (u_hat.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_hat.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_hat.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_hat.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->hat);
      *(outbuffer + offset + 0) = (this->triangle >> (8 * 0)) & 0xFF;
      offset += sizeof(this->triangle);
      *(outbuffer + offset + 0) = (this->circle >> (8 * 0)) & 0xFF;
      offset += sizeof(this->circle);
      union {
        int8_t real;
        uint8_t base;
      } u_square;
      u_square.real = this->square;
      *(outbuffer + offset + 0) = (u_square.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->square);
      *(outbuffer + offset + 0) = (this->cross >> (8 * 0)) & 0xFF;
      offset += sizeof(this->cross);
      *(outbuffer + offset + 0) = (this->L1 >> (8 * 0)) & 0xFF;
      offset += sizeof(this->L1);
      *(outbuffer + offset + 0) = (this->L2 >> (8 * 0)) & 0xFF;
      offset += sizeof(this->L2);
      *(outbuffer + offset + 0) = (this->L3 >> (8 * 0)) & 0xFF;
      offset += sizeof(this->L3);
      *(outbuffer + offset + 0) = (this->R1 >> (8 * 0)) & 0xFF;
      offset += sizeof(this->R1);
      *(outbuffer + offset + 0) = (this->R2 >> (8 * 0)) & 0xFF;
      offset += sizeof(this->R2);
      *(outbuffer + offset + 0) = (this->R3 >> (8 * 0)) & 0xFF;
      offset += sizeof(this->R3);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      union {
        float real;
        uint32_t base;
      } u_x;
      u_x.base = 0;
      u_x.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_x.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_x.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_x.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->x = u_x.real;
      offset += sizeof(this->x);
      union {
        float real;
        uint32_t base;
      } u_y;
      u_y.base = 0;
      u_y.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_y.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_y.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_y.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->y = u_y.real;
      offset += sizeof(this->y);
      union {
        float real;
        uint32_t base;
      } u_z;
      u_z.base = 0;
      u_z.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_z.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_z.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_z.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->z = u_z.real;
      offset += sizeof(this->z);
      union {
        float real;
        uint32_t base;
      } u_r;
      u_r.base = 0;
      u_r.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_r.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_r.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_r.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->r = u_r.real;
      offset += sizeof(this->r);
      union {
        float real;
        uint32_t base;
      } u_LT;
      u_LT.base = 0;
      u_LT.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_LT.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_LT.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_LT.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->LT = u_LT.real;
      offset += sizeof(this->LT);
      union {
        float real;
        uint32_t base;
      } u_RT;
      u_RT.base = 0;
      u_RT.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_RT.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_RT.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_RT.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->RT = u_RT.real;
      offset += sizeof(this->RT);
      union {
        int32_t real;
        uint32_t base;
      } u_hat;
      u_hat.base = 0;
      u_hat.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_hat.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_hat.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_hat.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->hat = u_hat.real;
      offset += sizeof(this->hat);
      this->triangle =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->triangle);
      this->circle =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->circle);
      union {
        int8_t real;
        uint8_t base;
      } u_square;
      u_square.base = 0;
      u_square.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->square = u_square.real;
      offset += sizeof(this->square);
      this->cross =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->cross);
      this->L1 =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->L1);
      this->L2 =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->L2);
      this->L3 =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->L3);
      this->R1 =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->R1);
      this->R2 =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->R2);
      this->R3 =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->R3);
     return offset;
    }

    const char * getType(){ return "s4_msgs/JoyCon"; };
    const char * getMD5(){ return "791850820720ec45ccf4bc53eb989795"; };

  };

}
#endif
