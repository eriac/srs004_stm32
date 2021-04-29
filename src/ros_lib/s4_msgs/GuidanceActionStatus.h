#ifndef _ROS_s4_msgs_GuidanceActionStatus_h
#define _ROS_s4_msgs_GuidanceActionStatus_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "s4_msgs/CommandItem.h"

namespace s4_msgs
{

  class GuidanceActionStatus : public ros::Msg
  {
    public:
      typedef s4_msgs::CommandItem _current_mode_type;
      _current_mode_type current_mode;
      uint32_t list_length;
      typedef s4_msgs::CommandItem _list_type;
      _list_type st_list;
      _list_type * list;

    GuidanceActionStatus():
      current_mode(),
      list_length(0), list(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->current_mode.serialize(outbuffer + offset);
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
      offset += this->current_mode.deserialize(inbuffer + offset);
      uint32_t list_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      list_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      list_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      list_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->list_length);
      if(list_lengthT > list_length)
        this->list = (s4_msgs::CommandItem*)realloc(this->list, list_lengthT * sizeof(s4_msgs::CommandItem));
      list_length = list_lengthT;
      for( uint32_t i = 0; i < list_length; i++){
      offset += this->st_list.deserialize(inbuffer + offset);
        memcpy( &(this->list[i]), &(this->st_list), sizeof(s4_msgs::CommandItem));
      }
     return offset;
    }

    const char * getType(){ return "s4_msgs/GuidanceActionStatus"; };
    const char * getMD5(){ return "224a430203e5f963f4c99c2d315bed50"; };

  };

}
#endif
