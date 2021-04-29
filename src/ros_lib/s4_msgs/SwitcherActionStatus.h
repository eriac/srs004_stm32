#ifndef _ROS_s4_msgs_SwitcherActionStatus_h
#define _ROS_s4_msgs_SwitcherActionStatus_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "s4_msgs/CommandItem.h"

namespace s4_msgs
{

  class SwitcherActionStatus : public ros::Msg
  {
    public:
      typedef s4_msgs::CommandItem _current_mode_type;
      _current_mode_type current_mode;
      uint32_t valid_length;
      typedef s4_msgs::CommandItem _valid_type;
      _valid_type st_valid;
      _valid_type * valid;
      uint32_t invalid_length;
      typedef s4_msgs::CommandItem _invalid_type;
      _invalid_type st_invalid;
      _invalid_type * invalid;

    SwitcherActionStatus():
      current_mode(),
      valid_length(0), valid(NULL),
      invalid_length(0), invalid(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->current_mode.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->valid_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->valid_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->valid_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->valid_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->valid_length);
      for( uint32_t i = 0; i < valid_length; i++){
      offset += this->valid[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset + 0) = (this->invalid_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->invalid_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->invalid_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->invalid_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->invalid_length);
      for( uint32_t i = 0; i < invalid_length; i++){
      offset += this->invalid[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->current_mode.deserialize(inbuffer + offset);
      uint32_t valid_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      valid_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      valid_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      valid_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->valid_length);
      if(valid_lengthT > valid_length)
        this->valid = (s4_msgs::CommandItem*)realloc(this->valid, valid_lengthT * sizeof(s4_msgs::CommandItem));
      valid_length = valid_lengthT;
      for( uint32_t i = 0; i < valid_length; i++){
      offset += this->st_valid.deserialize(inbuffer + offset);
        memcpy( &(this->valid[i]), &(this->st_valid), sizeof(s4_msgs::CommandItem));
      }
      uint32_t invalid_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      invalid_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      invalid_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      invalid_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->invalid_length);
      if(invalid_lengthT > invalid_length)
        this->invalid = (s4_msgs::CommandItem*)realloc(this->invalid, invalid_lengthT * sizeof(s4_msgs::CommandItem));
      invalid_length = invalid_lengthT;
      for( uint32_t i = 0; i < invalid_length; i++){
      offset += this->st_invalid.deserialize(inbuffer + offset);
        memcpy( &(this->invalid[i]), &(this->st_invalid), sizeof(s4_msgs::CommandItem));
      }
     return offset;
    }

    const char * getType(){ return "s4_msgs/SwitcherActionStatus"; };
    const char * getMD5(){ return "d4cb99d9e2e0bbff57bf9af3532c8317"; };

  };

}
#endif
