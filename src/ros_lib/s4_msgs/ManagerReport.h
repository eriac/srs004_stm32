#ifndef _ROS_s4_msgs_ManagerReport_h
#define _ROS_s4_msgs_ManagerReport_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "s4_msgs/BoolKeyValue.h"

namespace s4_msgs
{

  class ManagerReport : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      uint32_t bool_set_length;
      typedef s4_msgs::BoolKeyValue _bool_set_type;
      _bool_set_type st_bool_set;
      _bool_set_type * bool_set;

    ManagerReport():
      header(),
      bool_set_length(0), bool_set(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->bool_set_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->bool_set_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->bool_set_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->bool_set_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->bool_set_length);
      for( uint32_t i = 0; i < bool_set_length; i++){
      offset += this->bool_set[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      uint32_t bool_set_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      bool_set_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      bool_set_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      bool_set_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->bool_set_length);
      if(bool_set_lengthT > bool_set_length)
        this->bool_set = (s4_msgs::BoolKeyValue*)realloc(this->bool_set, bool_set_lengthT * sizeof(s4_msgs::BoolKeyValue));
      bool_set_length = bool_set_lengthT;
      for( uint32_t i = 0; i < bool_set_length; i++){
      offset += this->st_bool_set.deserialize(inbuffer + offset);
        memcpy( &(this->bool_set[i]), &(this->st_bool_set), sizeof(s4_msgs::BoolKeyValue));
      }
     return offset;
    }

    const char * getType(){ return "s4_msgs/ManagerReport"; };
    const char * getMD5(){ return "291188feab23528c8e872b9e3ff9fa41"; };

  };

}
#endif
