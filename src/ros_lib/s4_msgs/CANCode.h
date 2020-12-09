#ifndef _ROS_s4_msgs_CANCode_h
#define _ROS_s4_msgs_CANCode_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace s4_msgs
{

  class CANCode : public ros::Msg
  {
    public:
      typedef const char* _channel_type;
      _channel_type channel;
      typedef int32_t _id_type;
      _id_type id;
      typedef int32_t _com_type;
      _com_type com;
      typedef bool _remote_type;
      _remote_type remote;
      typedef int32_t _length_type;
      _length_type length;
      int32_t data[8];

    CANCode():
      channel(""),
      id(0),
      com(0),
      remote(0),
      length(0),
      data()
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
        int32_t real;
        uint32_t base;
      } u_id;
      u_id.real = this->id;
      *(outbuffer + offset + 0) = (u_id.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_id.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_id.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_id.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->id);
      union {
        int32_t real;
        uint32_t base;
      } u_com;
      u_com.real = this->com;
      *(outbuffer + offset + 0) = (u_com.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_com.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_com.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_com.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->com);
      union {
        bool real;
        uint8_t base;
      } u_remote;
      u_remote.real = this->remote;
      *(outbuffer + offset + 0) = (u_remote.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->remote);
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
        int32_t real;
        uint32_t base;
      } u_id;
      u_id.base = 0;
      u_id.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_id.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_id.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_id.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->id = u_id.real;
      offset += sizeof(this->id);
      union {
        int32_t real;
        uint32_t base;
      } u_com;
      u_com.base = 0;
      u_com.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_com.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_com.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_com.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->com = u_com.real;
      offset += sizeof(this->com);
      union {
        bool real;
        uint8_t base;
      } u_remote;
      u_remote.base = 0;
      u_remote.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->remote = u_remote.real;
      offset += sizeof(this->remote);
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
     return offset;
    }

    const char * getType(){ return "s4_msgs/CANCode"; };
    const char * getMD5(){ return "2db5933651ed09bcecad79a5dd353897"; };

  };

}
#endif
