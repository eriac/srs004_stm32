#ifndef _ROS_s4_msgs_CommandItem_h
#define _ROS_s4_msgs_CommandItem_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace s4_msgs
{

  class CommandItem : public ros::Msg
  {
    public:
      typedef uint16_t _id_type;
      _id_type id;
      typedef const char* _name_type;
      _name_type name;
      enum { NONE = 0 };
      enum { SWITCHER_START =  100 };
      enum { SET_MODE_STANDBY =  101 };
      enum { SET_MODE_MANUAL =  102 };
      enum { SET_MODE_GRAPH_MOVE =  103 };
      enum { SET_MODE_INSTRUCTION =  104 };
      enum { SWITCHER_END =  199 };
      enum { GUIDANCE_START =  200 };
      enum { GUIDANCE_TARGET_STOP =  201 };
      enum { GUIDANCE_TARGET_MANUAL =  202 };
      enum { GUIDANCE_TARGET_GRAPH_MOVE =  203 };
      enum { GUIDANCE_TARGET_FOLLOW =  204 };
      enum { GUIDANCE_TARGET_INSTRUCTION =  205 };
      enum { INSTR_POSE =  251 };
      enum { INSTR_YAW =  252 };
      enum { INSTR_POSE_ARRAY =  253 };
      enum { GUIDANCE_END =  299 };
      enum { NAVIGATOR_TARGET_STOP =  401 };
      enum { NAVIGATOR_TARGET_MANUAL =  402 };
      enum { NAVIGATOR_TARGET_POSITION =  403 };
      enum { NAVIGATOR_TARGET_YAW =  404 };

    CommandItem():
      id(0),
      name("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->id >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->id >> (8 * 1)) & 0xFF;
      offset += sizeof(this->id);
      uint32_t length_name = strlen(this->name);
      varToArr(outbuffer + offset, length_name);
      offset += 4;
      memcpy(outbuffer + offset, this->name, length_name);
      offset += length_name;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->id =  ((uint16_t) (*(inbuffer + offset)));
      this->id |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->id);
      uint32_t length_name;
      arrToVar(length_name, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_name-1]=0;
      this->name = (char *)(inbuffer + offset-1);
      offset += length_name;
     return offset;
    }

    const char * getType(){ return "s4_msgs/CommandItem"; };
    const char * getMD5(){ return "6342b18b8ee3e254014864dbc6b6cdcf"; };

  };

}
#endif
