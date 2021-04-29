#ifndef _ROS_s4_msgs_ActionCommand_h
#define _ROS_s4_msgs_ActionCommand_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "s4_msgs/CommandItem.h"

namespace s4_msgs
{

  class ActionCommand : public ros::Msg
  {
    public:
      typedef s4_msgs::CommandItem _command_type;
      _command_type command;
      uint32_t float_params_length;
      typedef float _float_params_type;
      _float_params_type st_float_params;
      _float_params_type * float_params;
      uint32_t str_params_length;
      typedef char* _str_params_type;
      _str_params_type st_str_params;
      _str_params_type * str_params;

    ActionCommand():
      command(),
      float_params_length(0), float_params(NULL),
      str_params_length(0), str_params(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->command.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->float_params_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->float_params_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->float_params_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->float_params_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->float_params_length);
      for( uint32_t i = 0; i < float_params_length; i++){
      union {
        float real;
        uint32_t base;
      } u_float_paramsi;
      u_float_paramsi.real = this->float_params[i];
      *(outbuffer + offset + 0) = (u_float_paramsi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_float_paramsi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_float_paramsi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_float_paramsi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->float_params[i]);
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
      uint32_t float_params_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      float_params_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      float_params_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      float_params_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->float_params_length);
      if(float_params_lengthT > float_params_length)
        this->float_params = (float*)realloc(this->float_params, float_params_lengthT * sizeof(float));
      float_params_length = float_params_lengthT;
      for( uint32_t i = 0; i < float_params_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_float_params;
      u_st_float_params.base = 0;
      u_st_float_params.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_float_params.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_float_params.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_float_params.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_float_params = u_st_float_params.real;
      offset += sizeof(this->st_float_params);
        memcpy( &(this->float_params[i]), &(this->st_float_params), sizeof(float));
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

    const char * getType(){ return "s4_msgs/ActionCommand"; };
    const char * getMD5(){ return "fc595470264bb3eeac19956251b97b2f"; };

  };

}
#endif
