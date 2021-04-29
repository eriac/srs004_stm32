#ifndef _ROS_s4_msgs_JoyCommand_h
#define _ROS_s4_msgs_JoyCommand_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace s4_msgs
{

  class JoyCommand : public ros::Msg
  {
    public:
      uint32_t buttons_name_length;
      typedef char* _buttons_name_type;
      _buttons_name_type st_buttons_name;
      _buttons_name_type * buttons_name;
      uint32_t buttons_config_length;
      typedef uint8_t _buttons_config_type;
      _buttons_config_type st_buttons_config;
      _buttons_config_type * buttons_config;
      uint32_t buttons_value_length;
      typedef uint8_t _buttons_value_type;
      _buttons_value_type st_buttons_value;
      _buttons_value_type * buttons_value;
      uint32_t axes_name_length;
      typedef char* _axes_name_type;
      _axes_name_type st_axes_name;
      _axes_name_type * axes_name;
      uint32_t axes_config_length;
      typedef uint8_t _axes_config_type;
      _axes_config_type st_axes_config;
      _axes_config_type * axes_config;
      uint32_t axes_value_length;
      typedef float _axes_value_type;
      _axes_value_type st_axes_value;
      _axes_value_type * axes_value;
      typedef bool _connected_type;
      _connected_type connected;
      typedef bool _axes_active_type;
      _axes_active_type axes_active;
      typedef bool _axes_reach_limit_type;
      _axes_reach_limit_type axes_reach_limit;
      enum { BUTTONS_CONFIG_NONE =  0 };
      enum { AXES_CONFIG_NONE =  0 };
      enum { AXES_CONFIG_MOVE_LINEAR_X =  1 };
      enum { AXES_CONFIG_MOVE_LINEAR_Y =  2 };
      enum { AXES_CONFIG_MOVE_LINEAR_Z =  3 };
      enum { AXES_CONFIG_MOVE_YAW =  4 };

    JoyCommand():
      buttons_name_length(0), buttons_name(NULL),
      buttons_config_length(0), buttons_config(NULL),
      buttons_value_length(0), buttons_value(NULL),
      axes_name_length(0), axes_name(NULL),
      axes_config_length(0), axes_config(NULL),
      axes_value_length(0), axes_value(NULL),
      connected(0),
      axes_active(0),
      axes_reach_limit(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->buttons_name_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->buttons_name_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->buttons_name_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->buttons_name_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->buttons_name_length);
      for( uint32_t i = 0; i < buttons_name_length; i++){
      uint32_t length_buttons_namei = strlen(this->buttons_name[i]);
      varToArr(outbuffer + offset, length_buttons_namei);
      offset += 4;
      memcpy(outbuffer + offset, this->buttons_name[i], length_buttons_namei);
      offset += length_buttons_namei;
      }
      *(outbuffer + offset + 0) = (this->buttons_config_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->buttons_config_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->buttons_config_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->buttons_config_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->buttons_config_length);
      for( uint32_t i = 0; i < buttons_config_length; i++){
      *(outbuffer + offset + 0) = (this->buttons_config[i] >> (8 * 0)) & 0xFF;
      offset += sizeof(this->buttons_config[i]);
      }
      *(outbuffer + offset + 0) = (this->buttons_value_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->buttons_value_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->buttons_value_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->buttons_value_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->buttons_value_length);
      for( uint32_t i = 0; i < buttons_value_length; i++){
      *(outbuffer + offset + 0) = (this->buttons_value[i] >> (8 * 0)) & 0xFF;
      offset += sizeof(this->buttons_value[i]);
      }
      *(outbuffer + offset + 0) = (this->axes_name_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->axes_name_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->axes_name_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->axes_name_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->axes_name_length);
      for( uint32_t i = 0; i < axes_name_length; i++){
      uint32_t length_axes_namei = strlen(this->axes_name[i]);
      varToArr(outbuffer + offset, length_axes_namei);
      offset += 4;
      memcpy(outbuffer + offset, this->axes_name[i], length_axes_namei);
      offset += length_axes_namei;
      }
      *(outbuffer + offset + 0) = (this->axes_config_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->axes_config_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->axes_config_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->axes_config_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->axes_config_length);
      for( uint32_t i = 0; i < axes_config_length; i++){
      *(outbuffer + offset + 0) = (this->axes_config[i] >> (8 * 0)) & 0xFF;
      offset += sizeof(this->axes_config[i]);
      }
      *(outbuffer + offset + 0) = (this->axes_value_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->axes_value_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->axes_value_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->axes_value_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->axes_value_length);
      for( uint32_t i = 0; i < axes_value_length; i++){
      union {
        float real;
        uint32_t base;
      } u_axes_valuei;
      u_axes_valuei.real = this->axes_value[i];
      *(outbuffer + offset + 0) = (u_axes_valuei.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_axes_valuei.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_axes_valuei.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_axes_valuei.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->axes_value[i]);
      }
      union {
        bool real;
        uint8_t base;
      } u_connected;
      u_connected.real = this->connected;
      *(outbuffer + offset + 0) = (u_connected.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->connected);
      union {
        bool real;
        uint8_t base;
      } u_axes_active;
      u_axes_active.real = this->axes_active;
      *(outbuffer + offset + 0) = (u_axes_active.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->axes_active);
      union {
        bool real;
        uint8_t base;
      } u_axes_reach_limit;
      u_axes_reach_limit.real = this->axes_reach_limit;
      *(outbuffer + offset + 0) = (u_axes_reach_limit.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->axes_reach_limit);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t buttons_name_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      buttons_name_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      buttons_name_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      buttons_name_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->buttons_name_length);
      if(buttons_name_lengthT > buttons_name_length)
        this->buttons_name = (char**)realloc(this->buttons_name, buttons_name_lengthT * sizeof(char*));
      buttons_name_length = buttons_name_lengthT;
      for( uint32_t i = 0; i < buttons_name_length; i++){
      uint32_t length_st_buttons_name;
      arrToVar(length_st_buttons_name, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_buttons_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_buttons_name-1]=0;
      this->st_buttons_name = (char *)(inbuffer + offset-1);
      offset += length_st_buttons_name;
        memcpy( &(this->buttons_name[i]), &(this->st_buttons_name), sizeof(char*));
      }
      uint32_t buttons_config_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      buttons_config_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      buttons_config_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      buttons_config_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->buttons_config_length);
      if(buttons_config_lengthT > buttons_config_length)
        this->buttons_config = (uint8_t*)realloc(this->buttons_config, buttons_config_lengthT * sizeof(uint8_t));
      buttons_config_length = buttons_config_lengthT;
      for( uint32_t i = 0; i < buttons_config_length; i++){
      this->st_buttons_config =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->st_buttons_config);
        memcpy( &(this->buttons_config[i]), &(this->st_buttons_config), sizeof(uint8_t));
      }
      uint32_t buttons_value_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      buttons_value_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      buttons_value_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      buttons_value_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->buttons_value_length);
      if(buttons_value_lengthT > buttons_value_length)
        this->buttons_value = (uint8_t*)realloc(this->buttons_value, buttons_value_lengthT * sizeof(uint8_t));
      buttons_value_length = buttons_value_lengthT;
      for( uint32_t i = 0; i < buttons_value_length; i++){
      this->st_buttons_value =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->st_buttons_value);
        memcpy( &(this->buttons_value[i]), &(this->st_buttons_value), sizeof(uint8_t));
      }
      uint32_t axes_name_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      axes_name_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      axes_name_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      axes_name_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->axes_name_length);
      if(axes_name_lengthT > axes_name_length)
        this->axes_name = (char**)realloc(this->axes_name, axes_name_lengthT * sizeof(char*));
      axes_name_length = axes_name_lengthT;
      for( uint32_t i = 0; i < axes_name_length; i++){
      uint32_t length_st_axes_name;
      arrToVar(length_st_axes_name, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_axes_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_axes_name-1]=0;
      this->st_axes_name = (char *)(inbuffer + offset-1);
      offset += length_st_axes_name;
        memcpy( &(this->axes_name[i]), &(this->st_axes_name), sizeof(char*));
      }
      uint32_t axes_config_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      axes_config_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      axes_config_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      axes_config_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->axes_config_length);
      if(axes_config_lengthT > axes_config_length)
        this->axes_config = (uint8_t*)realloc(this->axes_config, axes_config_lengthT * sizeof(uint8_t));
      axes_config_length = axes_config_lengthT;
      for( uint32_t i = 0; i < axes_config_length; i++){
      this->st_axes_config =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->st_axes_config);
        memcpy( &(this->axes_config[i]), &(this->st_axes_config), sizeof(uint8_t));
      }
      uint32_t axes_value_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      axes_value_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      axes_value_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      axes_value_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->axes_value_length);
      if(axes_value_lengthT > axes_value_length)
        this->axes_value = (float*)realloc(this->axes_value, axes_value_lengthT * sizeof(float));
      axes_value_length = axes_value_lengthT;
      for( uint32_t i = 0; i < axes_value_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_axes_value;
      u_st_axes_value.base = 0;
      u_st_axes_value.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_axes_value.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_axes_value.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_axes_value.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_axes_value = u_st_axes_value.real;
      offset += sizeof(this->st_axes_value);
        memcpy( &(this->axes_value[i]), &(this->st_axes_value), sizeof(float));
      }
      union {
        bool real;
        uint8_t base;
      } u_connected;
      u_connected.base = 0;
      u_connected.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->connected = u_connected.real;
      offset += sizeof(this->connected);
      union {
        bool real;
        uint8_t base;
      } u_axes_active;
      u_axes_active.base = 0;
      u_axes_active.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->axes_active = u_axes_active.real;
      offset += sizeof(this->axes_active);
      union {
        bool real;
        uint8_t base;
      } u_axes_reach_limit;
      u_axes_reach_limit.base = 0;
      u_axes_reach_limit.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->axes_reach_limit = u_axes_reach_limit.real;
      offset += sizeof(this->axes_reach_limit);
     return offset;
    }

    const char * getType(){ return "s4_msgs/JoyCommand"; };
    const char * getMD5(){ return "18f10ab90d986b4f4d5b2ec4fbd6bf62"; };

  };

}
#endif
