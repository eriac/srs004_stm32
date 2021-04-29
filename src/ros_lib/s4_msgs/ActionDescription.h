#ifndef _ROS_s4_msgs_ActionDescription_h
#define _ROS_s4_msgs_ActionDescription_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "s4_msgs/CommandItem.h"

namespace s4_msgs
{

  class ActionDescription : public ros::Msg
  {
    public:
      typedef s4_msgs::CommandItem _command_type;
      _command_type command;
      typedef const char* _description_type;
      _description_type description;
      uint32_t float_params_length;
      typedef char* _float_params_type;
      _float_params_type st_float_params;
      _float_params_type * float_params;
      uint32_t str_params_length;
      typedef char* _str_params_type;
      _str_params_type st_str_params;
      _str_params_type * str_params;

    ActionDescription():
      command(),
      description(""),
      float_params_length(0), float_params(NULL),
      str_params_length(0), str_params(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->command.serialize(outbuffer + offset);
      uint32_t length_description = strlen(this->description);
      varToArr(outbuffer + offset, length_description);
      offset += 4;
      memcpy(outbuffer + offset, this->description, length_description);
      offset += length_description;
      *(outbuffer + offset + 0) = (this->float_params_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->float_params_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->float_params_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->float_params_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->float_params_length);
      for( uint32_t i = 0; i < float_params_length; i++){
      uint32_t length_float_paramsi = strlen(this->float_params[i]);
      varToArr(outbuffer + offset, length_float_paramsi);
      offset += 4;
      memcpy(outbuffer + offset, this->float_params[i], length_float_paramsi);
      offset += length_float_paramsi;
      }
      *(outbuffer + offset + 0) = (this->str_params_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->str_params_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->str_params_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->str_params_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->str_params_length);
      for( uint32_t i = 0; i < str_params_length; i++){
      uint32_t length_str_paramsi = strlen(this->str_params[i]);
      varToArr(outbuffer + offset, length_str_paramsi);
      offset += 4;
      memcpy(outbuffer + offset, this->str_params[i], length_str_paramsi);
      offset += length_str_paramsi;
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->command.deserialize(inbuffer + offset);
      uint32_t length_description;
      arrToVar(length_description, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_description; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_description-1]=0;
      this->description = (char *)(inbuffer + offset-1);
      offset += length_description;
      uint32_t float_params_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      float_params_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      float_params_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      float_params_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->float_params_length);
      if(float_params_lengthT > float_params_length)
        this->float_params = (char**)realloc(this->float_params, float_params_lengthT * sizeof(char*));
      float_params_length = float_params_lengthT;
      for( uint32_t i = 0; i < float_params_length; i++){
      uint32_t length_st_float_params;
      arrToVar(length_st_float_params, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_float_params; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_float_params-1]=0;
      this->st_float_params = (char *)(inbuffer + offset-1);
      offset += length_st_float_params;
        memcpy( &(this->float_params[i]), &(this->st_float_params), sizeof(char*));
      }
      uint32_t str_params_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      str_params_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      str_params_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      str_params_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->str_params_length);
      if(str_params_lengthT > str_params_length)
        this->str_params = (char**)realloc(this->str_params, str_params_lengthT * sizeof(char*));
      str_params_length = str_params_lengthT;
      for( uint32_t i = 0; i < str_params_length; i++){
      uint32_t length_st_str_params;
      arrToVar(length_st_str_params, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_str_params; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_str_params-1]=0;
      this->st_str_params = (char *)(inbuffer + offset-1);
      offset += length_st_str_params;
        memcpy( &(this->str_params[i]), &(this->st_str_params), sizeof(char*));
      }
     return offset;
    }

    const char * getType(){ return "s4_msgs/ActionDescription"; };
    const char * getMD5(){ return "62ec9182dd2b025e1321fb426416d827"; };

  };

}
#endif
