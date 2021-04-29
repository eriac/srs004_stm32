#ifndef _ROS_s4_msgs_UiCommand_h
#define _ROS_s4_msgs_UiCommand_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace s4_msgs
{

  class UiCommand : public ros::Msg
  {
    public:
      typedef uint16_t _command_type;
      _command_type command;
      uint32_t float_param_length;
      typedef float _float_param_type;
      _float_param_type st_float_param;
      _float_param_type * float_param;
      uint32_t string_param_length;
      typedef char* _string_param_type;
      _string_param_type st_string_param;
      _string_param_type * string_param;

    UiCommand():
      command(0),
      float_param_length(0), float_param(NULL),
      string_param_length(0), string_param(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->command >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->command >> (8 * 1)) & 0xFF;
      offset += sizeof(this->command);
      *(outbuffer + offset + 0) = (this->float_param_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->float_param_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->float_param_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->float_param_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->float_param_length);
      for( uint32_t i = 0; i < float_param_length; i++){
      union {
        float real;
        uint32_t base;
      } u_float_parami;
      u_float_parami.real = this->float_param[i];
      *(outbuffer + offset + 0) = (u_float_parami.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_float_parami.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_float_parami.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_float_parami.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->float_param[i]);
      }
      *(outbuffer + offset + 0) = (this->string_param_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->string_param_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->string_param_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->string_param_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->string_param_length);
      for( uint32_t i = 0; i < string_param_length; i++){
      uint32_t length_string_parami = strlen(this->string_param[i]);
      varToArr(outbuffer + offset, length_string_parami);
      offset += 4;
      memcpy(outbuffer + offset, this->string_param[i], length_string_parami);
      offset += length_string_parami;
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->command =  ((uint16_t) (*(inbuffer + offset)));
      this->command |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->command);
      uint32_t float_param_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      float_param_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      float_param_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      float_param_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->float_param_length);
      if(float_param_lengthT > float_param_length)
        this->float_param = (float*)realloc(this->float_param, float_param_lengthT * sizeof(float));
      float_param_length = float_param_lengthT;
      for( uint32_t i = 0; i < float_param_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_float_param;
      u_st_float_param.base = 0;
      u_st_float_param.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_float_param.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_float_param.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_float_param.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_float_param = u_st_float_param.real;
      offset += sizeof(this->st_float_param);
        memcpy( &(this->float_param[i]), &(this->st_float_param), sizeof(float));
      }
      uint32_t string_param_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      string_param_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      string_param_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      string_param_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->string_param_length);
      if(string_param_lengthT > string_param_length)
        this->string_param = (char**)realloc(this->string_param, string_param_lengthT * sizeof(char*));
      string_param_length = string_param_lengthT;
      for( uint32_t i = 0; i < string_param_length; i++){
      uint32_t length_st_string_param;
      arrToVar(length_st_string_param, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_string_param; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_string_param-1]=0;
      this->st_string_param = (char *)(inbuffer + offset-1);
      offset += length_st_string_param;
        memcpy( &(this->string_param[i]), &(this->st_string_param), sizeof(char*));
      }
     return offset;
    }

    const char * getType(){ return "s4_msgs/UiCommand"; };
    const char * getMD5(){ return "ddaa40eb239bea429fc260041f561eef"; };

  };

}
#endif
