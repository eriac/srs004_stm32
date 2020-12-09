#ifndef _ROS_s4_msgs_CommanderStatus_h
#define _ROS_s4_msgs_CommanderStatus_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "s4_msgs/RobotCommand.h"

namespace s4_msgs
{

  class CommanderStatus : public ros::Msg
  {
    public:
      typedef uint16_t _state_type;
      _state_type state;
      uint32_t task_list_length;
      typedef s4_msgs::RobotCommand _task_list_type;
      _task_list_type st_task_list;
      _task_list_type * task_list;
      enum { STATE_STANDBY =  0 };
      enum { STATE_MANUAL =  1 };
      enum { STATE_FOLLOW =  2 };
      enum { STATE_EXPLORE =  3 };
      enum { STATE_FREE_MOVE =  4 };
      enum { STATE_GRAPH_MOVE =  5 };
      enum { STATE_RETURN =  6 };
      enum { STATE_MISSION =  7 };
      enum { STATE_NAV_GOTO_POINT =  100 };
      enum { STATE_NAV_HEAD_POINT =  101 };

    CommanderStatus():
      state(0),
      task_list_length(0), task_list(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->state >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->state >> (8 * 1)) & 0xFF;
      offset += sizeof(this->state);
      *(outbuffer + offset + 0) = (this->task_list_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->task_list_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->task_list_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->task_list_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->task_list_length);
      for( uint32_t i = 0; i < task_list_length; i++){
      offset += this->task_list[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->state =  ((uint16_t) (*(inbuffer + offset)));
      this->state |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->state);
      uint32_t task_list_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      task_list_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      task_list_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      task_list_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->task_list_length);
      if(task_list_lengthT > task_list_length)
        this->task_list = (s4_msgs::RobotCommand*)realloc(this->task_list, task_list_lengthT * sizeof(s4_msgs::RobotCommand));
      task_list_length = task_list_lengthT;
      for( uint32_t i = 0; i < task_list_length; i++){
      offset += this->st_task_list.deserialize(inbuffer + offset);
        memcpy( &(this->task_list[i]), &(this->st_task_list), sizeof(s4_msgs::RobotCommand));
      }
     return offset;
    }

    const char * getType(){ return "s4_msgs/CommanderStatus"; };
    const char * getMD5(){ return "b42f6214bc87fdda268fe55855aa873d"; };

  };

}
#endif
