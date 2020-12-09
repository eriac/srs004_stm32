#ifndef _ROS_s4_msgs_RobotCommand_h
#define _ROS_s4_msgs_RobotCommand_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace s4_msgs
{

  class RobotCommand : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef uint16_t _command_type;
      _command_type command;
      typedef float _param1_type;
      _param1_type param1;
      typedef float _param2_type;
      _param2_type param2;
      typedef float _param3_type;
      _param3_type param3;
      typedef float _param4_type;
      _param4_type param4;
      typedef float _param5_type;
      _param5_type param5;
      enum { CMD_MODE_MANUAL =  100 };
      enum { CMD_MODE_GRAPH_MOVE =  200 };
      enum { CMD_MODE_FREE_MOVE =  300 };
      enum { NAV_HEAD_NODE_ID =  1100 };
      enum { NAV_TARGET_NODE_ID =  1210 };
      enum { NAV_TARGET_POSITION =  1220 };
      enum { NAV_SET_HP =  1999 };
      enum { COL_GRAPH_SET_NODE =  2011 };
      enum { COL_GRAPH_SET_EDGE =  2012 };
      enum { COL_GRAPH_REQUEST =  2013 };
      enum { COL_ALVAR_SET_ITEM =  2021 };
      enum { COL_ALVAR_REQUEST =  2022 };

    RobotCommand():
      header(),
      command(0),
      param1(0),
      param2(0),
      param3(0),
      param4(0),
      param5(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->command >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->command >> (8 * 1)) & 0xFF;
      offset += sizeof(this->command);
      union {
        float real;
        uint32_t base;
      } u_param1;
      u_param1.real = this->param1;
      *(outbuffer + offset + 0) = (u_param1.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_param1.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_param1.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_param1.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->param1);
      union {
        float real;
        uint32_t base;
      } u_param2;
      u_param2.real = this->param2;
      *(outbuffer + offset + 0) = (u_param2.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_param2.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_param2.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_param2.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->param2);
      union {
        float real;
        uint32_t base;
      } u_param3;
      u_param3.real = this->param3;
      *(outbuffer + offset + 0) = (u_param3.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_param3.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_param3.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_param3.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->param3);
      union {
        float real;
        uint32_t base;
      } u_param4;
      u_param4.real = this->param4;
      *(outbuffer + offset + 0) = (u_param4.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_param4.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_param4.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_param4.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->param4);
      union {
        float real;
        uint32_t base;
      } u_param5;
      u_param5.real = this->param5;
      *(outbuffer + offset + 0) = (u_param5.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_param5.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_param5.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_param5.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->param5);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      this->command =  ((uint16_t) (*(inbuffer + offset)));
      this->command |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->command);
      union {
        float real;
        uint32_t base;
      } u_param1;
      u_param1.base = 0;
      u_param1.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_param1.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_param1.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_param1.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->param1 = u_param1.real;
      offset += sizeof(this->param1);
      union {
        float real;
        uint32_t base;
      } u_param2;
      u_param2.base = 0;
      u_param2.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_param2.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_param2.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_param2.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->param2 = u_param2.real;
      offset += sizeof(this->param2);
      union {
        float real;
        uint32_t base;
      } u_param3;
      u_param3.base = 0;
      u_param3.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_param3.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_param3.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_param3.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->param3 = u_param3.real;
      offset += sizeof(this->param3);
      union {
        float real;
        uint32_t base;
      } u_param4;
      u_param4.base = 0;
      u_param4.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_param4.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_param4.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_param4.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->param4 = u_param4.real;
      offset += sizeof(this->param4);
      union {
        float real;
        uint32_t base;
      } u_param5;
      u_param5.base = 0;
      u_param5.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_param5.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_param5.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_param5.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->param5 = u_param5.real;
      offset += sizeof(this->param5);
     return offset;
    }

    const char * getType(){ return "s4_msgs/RobotCommand"; };
    const char * getMD5(){ return "2fc3237255b1c5443b068f723524b583"; };

  };

}
#endif
