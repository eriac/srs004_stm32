#ifndef _ROS_s4_msgs_CanLink_h
#define _ROS_s4_msgs_CanLink_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace s4_msgs
{

  class CanLink : public ros::Msg
  {
    public:
      typedef const char* _channel_type;
      _channel_type channel;
      typedef bool _remote_type;
      _remote_type remote;
      typedef uint8_t _source_id_type;
      _source_id_type source_id;
      typedef uint8_t _target_id_type;
      _target_id_type target_id;
      typedef uint8_t _command_type;
      _command_type command;
      typedef int32_t _length_type;
      _length_type length;
      int32_t data[8];
      typedef uint8_t _extra_type;
      _extra_type extra;

    CanLink():
      channel(""),
      remote(0),
      source_id(0),
      target_id(0),
      command(0),
      length(0),
      data(),
      extra(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_channel = strlen(this->channel);
      varToArr(outbuffer + offset, length_channel);
      offset += 4;
      memcpy(outbuffer + offset, this->channel, length_channel);
      offset += length_channel;
      union {
        bool real;
        uint8_t base;
      } u_remote;
      u_remote.real = this->remote;
      *(outbuffer + offset + 0) = (u_remote.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->remote);
      *(outbuffer + offset + 0) = (this->source_id >> (8 * 0)) & 0xFF;
      offset += sizeof(this->source_id);
      *(outbuffer + offset + 0) = (this->target_id >> (8 * 0)) & 0xFF;
      offset += sizeof(this->target_id);
      *(outbuffer + offset + 0) = (this->command >> (8 * 0)) & 0xFF;
      offset += sizeof(this->command);
      union {
        int32_t real;
        uint32_t base;
      } u_length;
      u_length.real = this->length;
      *(outbuffer + offset + 0) = (u_length.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_length.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_length.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_length.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->length);
      for( uint32_t i = 0; i < 8; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_datai;
      u_datai.real = this->data[i];
      *(outbuffer + offset + 0) = (u_datai.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_datai.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_datai.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_datai.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->data[i]);
      }
      *(outbuffer + offset + 0) = (this->extra >> (8 * 0)) & 0xFF;
      offset += sizeof(this->extra);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_channel;
      arrToVar(length_channel, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_channel; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_channel-1]=0;
      this->channel = (char *)(inbuffer + offset-1);
      offset += length_channel;
      union {
        bool real;
        uint8_t base;
      } u_remote;
      u_remote.base = 0;
      u_remote.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->remote = u_remote.real;
      offset += sizeof(this->remote);
      this->source_id =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->source_id);
      this->target_id =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->target_id);
      this->command =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->command);
      union {
        int32_t real;
        uint32_t base;
      } u_length;
      u_length.base = 0;
      u_length.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_length.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_length.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_length.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->length = u_length.real;
      offset += sizeof(this->length);
      for( uint32_t i = 0; i < 8; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_datai;
      u_datai.base = 0;
      u_datai.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_datai.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_datai.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_datai.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->data[i] = u_datai.real;
      offset += sizeof(this->data[i]);
      }
      this->extra =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->extra);
     return offset;
    }

    const char * getType(){ return "s4_msgs/CanLink"; };
    const char * getMD5(){ return "1bd545c9a7ba7ce6dd0934b186fff653"; };

  };

}
#endif
