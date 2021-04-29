#ifndef _ROS_s4_msgs_ActionStatus_h
#define _ROS_s4_msgs_ActionStatus_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "s4_msgs/CommandItem.h"
#include "s4_msgs/ActionModeStatus.h"
#include "s4_msgs/ActionDescription.h"

namespace s4_msgs
{

  class ActionStatus : public ros::Msg
  {
    public:
      typedef s4_msgs::CommandItem _main_mode_type;
      _main_mode_type main_mode;
      typedef s4_msgs::CommandItem _operation_mode_type;
      _operation_mode_type operation_mode;
      uint32_t mode_list_length;
      typedef s4_msgs::ActionModeStatus _mode_list_type;
      _mode_list_type st_mode_list;
      _mode_list_type * mode_list;
      uint32_t request_list_length;
      typedef s4_msgs::ActionDescription _request_list_type;
      _request_list_type st_request_list;
      _request_list_type * request_list;

    ActionStatus():
      main_mode(),
      operation_mode(),
      mode_list_length(0), mode_list(NULL),
      request_list_length(0), request_list(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->main_mode.serialize(outbuffer + offset);
      offset += this->operation_mode.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->mode_list_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->mode_list_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->mode_list_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->mode_list_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->mode_list_length);
      for( uint32_t i = 0; i < mode_list_length; i++){
      offset += this->mode_list[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset + 0) = (this->request_list_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->request_list_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->request_list_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->request_list_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->request_list_length);
      for( uint32_t i = 0; i < request_list_length; i++){
      offset += this->request_list[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->main_mode.deserialize(inbuffer + offset);
      offset += this->operation_mode.deserialize(inbuffer + offset);
      uint32_t mode_list_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      mode_list_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      mode_list_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      mode_list_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->mode_list_length);
      if(mode_list_lengthT > mode_list_length)
        this->mode_list = (s4_msgs::ActionModeStatus*)realloc(this->mode_list, mode_list_lengthT * sizeof(s4_msgs::ActionModeStatus));
      mode_list_length = mode_list_lengthT;
      for( uint32_t i = 0; i < mode_list_length; i++){
      offset += this->st_mode_list.deserialize(inbuffer + offset);
        memcpy( &(this->mode_list[i]), &(this->st_mode_list), sizeof(s4_msgs::ActionModeStatus));
      }
      uint32_t request_list_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      request_list_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      request_list_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      request_list_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->request_list_length);
      if(request_list_lengthT > request_list_length)
        this->request_list = (s4_msgs::ActionDescription*)realloc(this->request_list, request_list_lengthT * sizeof(s4_msgs::ActionDescription));
      request_list_length = request_list_lengthT;
      for( uint32_t i = 0; i < request_list_length; i++){
      offset += this->st_request_list.deserialize(inbuffer + offset);
        memcpy( &(this->request_list[i]), &(this->st_request_list), sizeof(s4_msgs::ActionDescription));
      }
     return offset;
    }

    const char * getType(){ return "s4_msgs/ActionStatus"; };
    const char * getMD5(){ return "d623dff9fd10154ca5be8b21a2ab5305"; };

  };

}
#endif
