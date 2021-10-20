#ifndef _ROS_s4_msgs_JoySetpoint_h
#define _ROS_s4_msgs_JoySetpoint_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "s4_msgs/ButtonItem.h"
#include "s4_msgs/AxisItem.h"

namespace s4_msgs
{

  class JoySetpoint : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      uint32_t buttons_length;
      typedef s4_msgs::ButtonItem _buttons_type;
      _buttons_type st_buttons;
      _buttons_type * buttons;
      uint32_t axes_length;
      typedef s4_msgs::AxisItem _axes_type;
      _axes_type st_axes;
      _axes_type * axes;
      typedef bool _connected_type;
      _connected_type connected;
      typedef bool _axes_active_type;
      _axes_active_type axes_active;
      typedef bool _axes_reach_limit_type;
      _axes_reach_limit_type axes_reach_limit;

    JoySetpoint():
      header(),
      buttons_length(0), buttons(NULL),
      axes_length(0), axes(NULL),
      connected(0),
      axes_active(0),
      axes_reach_limit(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->buttons_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->buttons_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->buttons_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->buttons_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->buttons_length);
      for( uint32_t i = 0; i < buttons_length; i++){
      offset += this->buttons[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset + 0) = (this->axes_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->axes_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->axes_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->axes_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->axes_length);
      for( uint32_t i = 0; i < axes_length; i++){
      offset += this->axes[i].serialize(outbuffer + offset);
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
      offset += this->header.deserialize(inbuffer + offset);
      uint32_t buttons_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      buttons_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      buttons_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      buttons_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->buttons_length);
      if(buttons_lengthT > buttons_length)
        this->buttons = (s4_msgs::ButtonItem*)realloc(this->buttons, buttons_lengthT * sizeof(s4_msgs::ButtonItem));
      buttons_length = buttons_lengthT;
      for( uint32_t i = 0; i < buttons_length; i++){
      offset += this->st_buttons.deserialize(inbuffer + offset);
        memcpy( &(this->buttons[i]), &(this->st_buttons), sizeof(s4_msgs::ButtonItem));
      }
      uint32_t axes_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      axes_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      axes_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      axes_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->axes_length);
      if(axes_lengthT > axes_length)
        this->axes = (s4_msgs::AxisItem*)realloc(this->axes, axes_lengthT * sizeof(s4_msgs::AxisItem));
      axes_length = axes_lengthT;
      for( uint32_t i = 0; i < axes_length; i++){
      offset += this->st_axes.deserialize(inbuffer + offset);
        memcpy( &(this->axes[i]), &(this->st_axes), sizeof(s4_msgs::AxisItem));
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

    const char * getType(){ return "s4_msgs/JoySetpoint"; };
    const char * getMD5(){ return "9412fc8a1613e6f05afec3bda5ad89c0"; };

  };

}
#endif
