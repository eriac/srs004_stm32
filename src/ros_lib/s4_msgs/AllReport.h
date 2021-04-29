#ifndef _ROS_s4_msgs_AllReport_h
#define _ROS_s4_msgs_AllReport_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "s4_msgs/ConnectionReport.h"

namespace s4_msgs
{

  class AllReport : public ros::Msg
  {
    public:
      typedef uint8_t _mode_type;
      _mode_type mode;
      typedef s4_msgs::ConnectionReport _connection_type;
      _connection_type connection;
      typedef bool _booting_type;
      _booting_type booting;

    AllReport():
      mode(0),
      connection(),
      booting(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->mode >> (8 * 0)) & 0xFF;
      offset += sizeof(this->mode);
      offset += this->connection.serialize(outbuffer + offset);
      union {
        bool real;
        uint8_t base;
      } u_booting;
      u_booting.real = this->booting;
      *(outbuffer + offset + 0) = (u_booting.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->booting);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->mode =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->mode);
      offset += this->connection.deserialize(inbuffer + offset);
      union {
        bool real;
        uint8_t base;
      } u_booting;
      u_booting.base = 0;
      u_booting.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->booting = u_booting.real;
      offset += sizeof(this->booting);
     return offset;
    }

    const char * getType(){ return "s4_msgs/AllReport"; };
    const char * getMD5(){ return "8fdfa53e01a634308539056347cbfe11"; };

  };

}
#endif
