#ifndef _ROS_s4_msgs_DataCommand_h
#define _ROS_s4_msgs_DataCommand_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace s4_msgs
{

  class DataCommand : public ros::Msg
  {
    public:
      typedef uint8_t _command_type;
      _command_type command;
      typedef const char* _data_type;
      _data_type data;
      enum { COMMAND_GRAPH_SET_GRAPH =  10 };
      enum { COMMAND_GRAPH_CLEAR_GRAPH =  11 };
      enum { COMMAND_GRAPH_REQUEST_GRAPH =  12 };
      enum { COMMAND_GRAPH_LOAD_GRAPH =  13 };
      enum { COMMAND_GRAPH_ADD_NODE =  15 };
      enum { COMMAND_GRAPH_REMOVE_NODE =  16 };
      enum { COMMAND_GRAPH_ADD_EDGE =  17 };
      enum { COMMAND_GRAPH_REMOVE_EDGE =  18 };
      enum { COMMAND_ALVAR_SET_LIST =  30 };
      enum { COMMAND_ALVAR_CLEAR_LIST =  31 };
      enum { COMMAND_ALVAR_REQUEST_LIST =  32 };
      enum { COMMAND_ALVAR_LOAD_LIST =  33 };
      enum { COMMAND_GRAPH_ADD_ITEM =  35 };
      enum { COMMAND_GRAPH_REMOTE_ =  36 };

    DataCommand():
      command(0),
      data("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->command >> (8 * 0)) & 0xFF;
      offset += sizeof(this->command);
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
      this->command =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->command);
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

    const char * getType(){ return "s4_msgs/DataCommand"; };
    const char * getMD5(){ return "153024381c11666728e637fde50cbf04"; };

  };

}
#endif
