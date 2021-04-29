#ifndef _ROS_s4_msgs_BoardInfo_h
#define _ROS_s4_msgs_BoardInfo_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace s4_msgs
{

  class BoardInfo : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef uint8_t _source_id_type;
      _source_id_type source_id;
      typedef const char* _name_type;
      _name_type name;
      typedef uint16_t _revision_type;
      _revision_type revision;
      typedef uint32_t _id_type;
      _id_type id;

    BoardInfo():
      header(),
      source_id(0),
      name(""),
      revision(0),
      id(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->source_id >> (8 * 0)) & 0xFF;
      offset += sizeof(this->source_id);
      uint32_t length_name = strlen(this->name);
      varToArr(outbuffer + offset, length_name);
      offset += 4;
      memcpy(outbuffer + offset, this->name, length_name);
      offset += length_name;
      *(outbuffer + offset + 0) = (this->revision >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->revision >> (8 * 1)) & 0xFF;
      offset += sizeof(this->revision);
      *(outbuffer + offset + 0) = (this->id >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->id >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->id >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->id >> (8 * 3)) & 0xFF;
      offset += sizeof(this->id);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      this->source_id =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->source_id);
      uint32_t length_name;
      arrToVar(length_name, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_name-1]=0;
      this->name = (char *)(inbuffer + offset-1);
      offset += length_name;
      this->revision =  ((uint16_t) (*(inbuffer + offset)));
      this->revision |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->revision);
      this->id =  ((uint32_t) (*(inbuffer + offset)));
      this->id |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->id |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->id |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->id);
     return offset;
    }

    const char * getType(){ return "s4_msgs/BoardInfo"; };
    const char * getMD5(){ return "f6ef3a0e727dbbb60a4a99e2382eaa1b"; };

  };

}
#endif
