#ifndef _ROS_s4_msgs_FocusList_h
#define _ROS_s4_msgs_FocusList_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "ros/time.h"
#include "s4_msgs/FocusSet.h"

namespace s4_msgs
{

  class FocusList : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef ros::Time _set_stamp_type;
      _set_stamp_type set_stamp;
      typedef s4_msgs::FocusSet _target_type;
      _target_type target;
      uint32_t sets_length;
      typedef s4_msgs::FocusSet _sets_type;
      _sets_type st_sets;
      _sets_type * sets;

    FocusList():
      header(),
      set_stamp(),
      target(),
      sets_length(0), sets(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->set_stamp.sec >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->set_stamp.sec >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->set_stamp.sec >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->set_stamp.sec >> (8 * 3)) & 0xFF;
      offset += sizeof(this->set_stamp.sec);
      *(outbuffer + offset + 0) = (this->set_stamp.nsec >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->set_stamp.nsec >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->set_stamp.nsec >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->set_stamp.nsec >> (8 * 3)) & 0xFF;
      offset += sizeof(this->set_stamp.nsec);
      offset += this->target.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->sets_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->sets_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->sets_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->sets_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->sets_length);
      for( uint32_t i = 0; i < sets_length; i++){
      offset += this->sets[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      this->set_stamp.sec =  ((uint32_t) (*(inbuffer + offset)));
      this->set_stamp.sec |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->set_stamp.sec |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->set_stamp.sec |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->set_stamp.sec);
      this->set_stamp.nsec =  ((uint32_t) (*(inbuffer + offset)));
      this->set_stamp.nsec |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->set_stamp.nsec |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->set_stamp.nsec |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->set_stamp.nsec);
      offset += this->target.deserialize(inbuffer + offset);
      uint32_t sets_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      sets_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      sets_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      sets_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->sets_length);
      if(sets_lengthT > sets_length)
        this->sets = (s4_msgs::FocusSet*)realloc(this->sets, sets_lengthT * sizeof(s4_msgs::FocusSet));
      sets_length = sets_lengthT;
      for( uint32_t i = 0; i < sets_length; i++){
      offset += this->st_sets.deserialize(inbuffer + offset);
        memcpy( &(this->sets[i]), &(this->st_sets), sizeof(s4_msgs::FocusSet));
      }
     return offset;
    }

    const char * getType(){ return "s4_msgs/FocusList"; };
    const char * getMD5(){ return "c1c616b0d9c53f9775a0e6b3028c8794"; };

  };

}
#endif
