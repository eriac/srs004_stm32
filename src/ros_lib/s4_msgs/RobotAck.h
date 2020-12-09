#ifndef _ROS_s4_msgs_RobotAck_h
#define _ROS_s4_msgs_RobotAck_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace s4_msgs
{

  class RobotAck : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef uint16_t _ack_type;
      _ack_type ack;
      typedef uint16_t _reason_type;
      _reason_type reason;
      typedef const char* _data_type;
      _data_type data;
      enum { OK =  0 };
      enum { NG =  0 };

    RobotAck():
      header(),
      ack(0),
      reason(0),
      data("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->ack >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->ack >> (8 * 1)) & 0xFF;
      offset += sizeof(this->ack);
      *(outbuffer + offset + 0) = (this->reason >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->reason >> (8 * 1)) & 0xFF;
      offset += sizeof(this->reason);
      uint32_t length_data = strlen(this->data);
      varToArr(outbuffer + offset, length_data);
      offset += 4;
      memcpy(outbuffer + offset, this->data, length_data);
      offset += length_data;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      this->ack =  ((uint16_t) (*(inbuffer + offset)));
      this->ack |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->ack);
      this->reason =  ((uint16_t) (*(inbuffer + offset)));
      this->reason |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->reason);
      uint32_t length_data;
      arrToVar(length_data, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_data; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_data-1]=0;
      this->data = (char *)(inbuffer + offset-1);
      offset += length_data;
     return offset;
    }

    const char * getType(){ return "s4_msgs/RobotAck"; };
    const char * getMD5(){ return "7e39f9f09259e1bd3fe2bebdcf0ae120"; };

  };

}
#endif
