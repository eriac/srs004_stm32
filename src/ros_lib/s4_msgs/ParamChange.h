#ifndef _ROS_s4_msgs_ParamChange_h
#define _ROS_s4_msgs_ParamChange_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "dynamic_reconfigure/BoolParameter.h"
#include "dynamic_reconfigure/IntParameter.h"
#include "dynamic_reconfigure/DoubleParameter.h"

namespace s4_msgs
{

  class ParamChange : public ros::Msg
  {
    public:
      typedef const char* _name_type;
      _name_type name;
      uint32_t bools_length;
      typedef dynamic_reconfigure::BoolParameter _bools_type;
      _bools_type st_bools;
      _bools_type * bools;
      uint32_t ints_length;
      typedef dynamic_reconfigure::IntParameter _ints_type;
      _ints_type st_ints;
      _ints_type * ints;
      uint32_t doubles_length;
      typedef dynamic_reconfigure::DoubleParameter _doubles_type;
      _doubles_type st_doubles;
      _doubles_type * doubles;

    ParamChange():
      name(""),
      bools_length(0), bools(NULL),
      ints_length(0), ints(NULL),
      doubles_length(0), doubles(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_name = strlen(this->name);
      varToArr(outbuffer + offset, length_name);
      offset += 4;
      memcpy(outbuffer + offset, this->name, length_name);
      offset += length_name;
      *(outbuffer + offset + 0) = (this->bools_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->bools_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->bools_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->bools_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->bools_length);
      for( uint32_t i = 0; i < bools_length; i++){
      offset += this->bools[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset + 0) = (this->ints_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->ints_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->ints_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->ints_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->ints_length);
      for( uint32_t i = 0; i < ints_length; i++){
      offset += this->ints[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset + 0) = (this->doubles_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->doubles_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->doubles_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->doubles_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->doubles_length);
      for( uint32_t i = 0; i < doubles_length; i++){
      offset += this->doubles[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_name;
      arrToVar(length_name, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_name-1]=0;
      this->name = (char *)(inbuffer + offset-1);
      offset += length_name;
      uint32_t bools_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      bools_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      bools_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      bools_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->bools_length);
      if(bools_lengthT > bools_length)
        this->bools = (dynamic_reconfigure::BoolParameter*)realloc(this->bools, bools_lengthT * sizeof(dynamic_reconfigure::BoolParameter));
      bools_length = bools_lengthT;
      for( uint32_t i = 0; i < bools_length; i++){
      offset += this->st_bools.deserialize(inbuffer + offset);
        memcpy( &(this->bools[i]), &(this->st_bools), sizeof(dynamic_reconfigure::BoolParameter));
      }
      uint32_t ints_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      ints_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      ints_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      ints_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->ints_length);
      if(ints_lengthT > ints_length)
        this->ints = (dynamic_reconfigure::IntParameter*)realloc(this->ints, ints_lengthT * sizeof(dynamic_reconfigure::IntParameter));
      ints_length = ints_lengthT;
      for( uint32_t i = 0; i < ints_length; i++){
      offset += this->st_ints.deserialize(inbuffer + offset);
        memcpy( &(this->ints[i]), &(this->st_ints), sizeof(dynamic_reconfigure::IntParameter));
      }
      uint32_t doubles_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      doubles_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      doubles_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      doubles_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->doubles_length);
      if(doubles_lengthT > doubles_length)
        this->doubles = (dynamic_reconfigure::DoubleParameter*)realloc(this->doubles, doubles_lengthT * sizeof(dynamic_reconfigure::DoubleParameter));
      doubles_length = doubles_lengthT;
      for( uint32_t i = 0; i < doubles_length; i++){
      offset += this->st_doubles.deserialize(inbuffer + offset);
        memcpy( &(this->doubles[i]), &(this->st_doubles), sizeof(dynamic_reconfigure::DoubleParameter));
      }
     return offset;
    }

    const char * getType(){ return "s4_msgs/ParamChange"; };
    const char * getMD5(){ return "e897b677f5b9db8c6970f7e385ca6350"; };

  };

}
#endif
