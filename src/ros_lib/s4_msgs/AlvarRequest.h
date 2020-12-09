#ifndef _ROS_SERVICE_AlvarRequest_h
#define _ROS_SERVICE_AlvarRequest_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "s4_msgs/Item2d.h"

namespace s4_msgs
{

static const char ALVARREQUEST[] = "s4_msgs/AlvarRequest";

  class AlvarRequestRequest : public ros::Msg
  {
    public:
      typedef bool _set_default_type;
      _set_default_type set_default;

    AlvarRequestRequest():
      set_default(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_set_default;
      u_set_default.real = this->set_default;
      *(outbuffer + offset + 0) = (u_set_default.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->set_default);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_set_default;
      u_set_default.base = 0;
      u_set_default.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->set_default = u_set_default.real;
      offset += sizeof(this->set_default);
     return offset;
    }

    const char * getType(){ return ALVARREQUEST; };
    const char * getMD5(){ return "cf21403bf6ca4ebf0791d4435cc279a4"; };

  };

  class AlvarRequestResponse : public ros::Msg
  {
    public:
      uint32_t list_length;
      typedef s4_msgs::Item2d _list_type;
      _list_type st_list;
      _list_type * list;

    AlvarRequestResponse():
      list_length(0), list(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->list_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->list_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->list_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->list_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->list_length);
      for( uint32_t i = 0; i < list_length; i++){
      offset += this->list[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t list_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      list_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      list_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      list_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->list_length);
      if(list_lengthT > list_length)
        this->list = (s4_msgs::Item2d*)realloc(this->list, list_lengthT * sizeof(s4_msgs::Item2d));
      list_length = list_lengthT;
      for( uint32_t i = 0; i < list_length; i++){
      offset += this->st_list.deserialize(inbuffer + offset);
        memcpy( &(this->list[i]), &(this->st_list), sizeof(s4_msgs::Item2d));
      }
     return offset;
    }

    const char * getType(){ return ALVARREQUEST; };
    const char * getMD5(){ return "234db8375cd5e885804a2111e9cac094"; };

  };

  class AlvarRequest {
    public:
    typedef AlvarRequestRequest Request;
    typedef AlvarRequestResponse Response;
  };

}
#endif
