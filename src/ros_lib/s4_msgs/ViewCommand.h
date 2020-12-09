#ifndef _ROS_s4_msgs_ViewCommand_h
#define _ROS_s4_msgs_ViewCommand_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "s4_msgs/TrackedInfo.h"

namespace s4_msgs
{

  class ViewCommand : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef s4_msgs::TrackedInfo _info_type;
      _info_type info;
      typedef double _hp_type;
      _hp_type hp;
      typedef double _light_type;
      _light_type light;
      typedef int32_t _lamp_type;
      _lamp_type lamp;
      enum { NONE =  0 };
      enum { RED =  1 };
      enum { YELLOW =  2 };

    ViewCommand():
      header(),
      info(),
      hp(0),
      light(0),
      lamp(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      offset += this->info.serialize(outbuffer + offset);
      union {
        double real;
        uint64_t base;
      } u_hp;
      u_hp.real = this->hp;
      *(outbuffer + offset + 0) = (u_hp.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_hp.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_hp.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_hp.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_hp.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_hp.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_hp.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_hp.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->hp);
      union {
        double real;
        uint64_t base;
      } u_light;
      u_light.real = this->light;
      *(outbuffer + offset + 0) = (u_light.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_light.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_light.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_light.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_light.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_light.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_light.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_light.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->light);
      union {
        int32_t real;
        uint32_t base;
      } u_lamp;
      u_lamp.real = this->lamp;
      *(outbuffer + offset + 0) = (u_lamp.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_lamp.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_lamp.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_lamp.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->lamp);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      offset += this->info.deserialize(inbuffer + offset);
      union {
        double real;
        uint64_t base;
      } u_hp;
      u_hp.base = 0;
      u_hp.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_hp.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_hp.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_hp.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_hp.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_hp.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_hp.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_hp.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->hp = u_hp.real;
      offset += sizeof(this->hp);
      union {
        double real;
        uint64_t base;
      } u_light;
      u_light.base = 0;
      u_light.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_light.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_light.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_light.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_light.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_light.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_light.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_light.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->light = u_light.real;
      offset += sizeof(this->light);
      union {
        int32_t real;
        uint32_t base;
      } u_lamp;
      u_lamp.base = 0;
      u_lamp.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_lamp.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_lamp.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_lamp.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->lamp = u_lamp.real;
      offset += sizeof(this->lamp);
     return offset;
    }

    const char * getType(){ return "s4_msgs/ViewCommand"; };
    const char * getMD5(){ return "3b53e9ccdebe99e4ba2b612bf26d03be"; };

  };

}
#endif
