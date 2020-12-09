#ifndef _ROS_s4_msgs_JoySide_h
#define _ROS_s4_msgs_JoySide_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace s4_msgs
{

  class JoySide : public ros::Msg
  {
    public:
      typedef double _AH_type;
      _AH_type AH;
      typedef double _AV_type;
      _AV_type AV;
      typedef double _B1_type;
      _B1_type B1;
      typedef double _B2_type;
      _B2_type B2;
      typedef double _B3_type;
      _B3_type B3;
      typedef double _CU_type;
      _CU_type CU;
      typedef double _CD_type;
      _CD_type CD;
      typedef double _CL_type;
      _CL_type CL;
      typedef double _CR_type;
      _CR_type CR;

    JoySide():
      AH(0),
      AV(0),
      B1(0),
      B2(0),
      B3(0),
      CU(0),
      CD(0),
      CL(0),
      CR(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        double real;
        uint64_t base;
      } u_AH;
      u_AH.real = this->AH;
      *(outbuffer + offset + 0) = (u_AH.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_AH.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_AH.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_AH.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_AH.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_AH.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_AH.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_AH.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->AH);
      union {
        double real;
        uint64_t base;
      } u_AV;
      u_AV.real = this->AV;
      *(outbuffer + offset + 0) = (u_AV.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_AV.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_AV.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_AV.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_AV.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_AV.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_AV.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_AV.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->AV);
      union {
        double real;
        uint64_t base;
      } u_B1;
      u_B1.real = this->B1;
      *(outbuffer + offset + 0) = (u_B1.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_B1.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_B1.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_B1.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_B1.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_B1.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_B1.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_B1.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->B1);
      union {
        double real;
        uint64_t base;
      } u_B2;
      u_B2.real = this->B2;
      *(outbuffer + offset + 0) = (u_B2.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_B2.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_B2.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_B2.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_B2.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_B2.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_B2.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_B2.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->B2);
      union {
        double real;
        uint64_t base;
      } u_B3;
      u_B3.real = this->B3;
      *(outbuffer + offset + 0) = (u_B3.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_B3.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_B3.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_B3.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_B3.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_B3.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_B3.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_B3.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->B3);
      union {
        double real;
        uint64_t base;
      } u_CU;
      u_CU.real = this->CU;
      *(outbuffer + offset + 0) = (u_CU.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_CU.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_CU.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_CU.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_CU.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_CU.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_CU.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_CU.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->CU);
      union {
        double real;
        uint64_t base;
      } u_CD;
      u_CD.real = this->CD;
      *(outbuffer + offset + 0) = (u_CD.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_CD.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_CD.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_CD.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_CD.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_CD.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_CD.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_CD.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->CD);
      union {
        double real;
        uint64_t base;
      } u_CL;
      u_CL.real = this->CL;
      *(outbuffer + offset + 0) = (u_CL.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_CL.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_CL.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_CL.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_CL.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_CL.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_CL.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_CL.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->CL);
      union {
        double real;
        uint64_t base;
      } u_CR;
      u_CR.real = this->CR;
      *(outbuffer + offset + 0) = (u_CR.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_CR.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_CR.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_CR.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_CR.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_CR.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_CR.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_CR.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->CR);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        double real;
        uint64_t base;
      } u_AH;
      u_AH.base = 0;
      u_AH.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_AH.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_AH.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_AH.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_AH.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_AH.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_AH.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_AH.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->AH = u_AH.real;
      offset += sizeof(this->AH);
      union {
        double real;
        uint64_t base;
      } u_AV;
      u_AV.base = 0;
      u_AV.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_AV.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_AV.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_AV.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_AV.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_AV.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_AV.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_AV.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->AV = u_AV.real;
      offset += sizeof(this->AV);
      union {
        double real;
        uint64_t base;
      } u_B1;
      u_B1.base = 0;
      u_B1.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_B1.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_B1.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_B1.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_B1.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_B1.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_B1.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_B1.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->B1 = u_B1.real;
      offset += sizeof(this->B1);
      union {
        double real;
        uint64_t base;
      } u_B2;
      u_B2.base = 0;
      u_B2.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_B2.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_B2.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_B2.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_B2.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_B2.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_B2.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_B2.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->B2 = u_B2.real;
      offset += sizeof(this->B2);
      union {
        double real;
        uint64_t base;
      } u_B3;
      u_B3.base = 0;
      u_B3.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_B3.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_B3.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_B3.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_B3.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_B3.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_B3.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_B3.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->B3 = u_B3.real;
      offset += sizeof(this->B3);
      union {
        double real;
        uint64_t base;
      } u_CU;
      u_CU.base = 0;
      u_CU.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_CU.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_CU.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_CU.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_CU.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_CU.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_CU.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_CU.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->CU = u_CU.real;
      offset += sizeof(this->CU);
      union {
        double real;
        uint64_t base;
      } u_CD;
      u_CD.base = 0;
      u_CD.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_CD.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_CD.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_CD.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_CD.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_CD.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_CD.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_CD.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->CD = u_CD.real;
      offset += sizeof(this->CD);
      union {
        double real;
        uint64_t base;
      } u_CL;
      u_CL.base = 0;
      u_CL.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_CL.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_CL.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_CL.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_CL.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_CL.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_CL.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_CL.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->CL = u_CL.real;
      offset += sizeof(this->CL);
      union {
        double real;
        uint64_t base;
      } u_CR;
      u_CR.base = 0;
      u_CR.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_CR.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_CR.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_CR.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_CR.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_CR.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_CR.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_CR.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->CR = u_CR.real;
      offset += sizeof(this->CR);
     return offset;
    }

    const char * getType(){ return "s4_msgs/JoySide"; };
    const char * getMD5(){ return "ba459d36dfa844f7791239a9bdaae817"; };

  };

}
#endif
