#ifndef _ROS_s4_msgs_TrackedObject_h
#define _ROS_s4_msgs_TrackedObject_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "s4_msgs/TrackedInfo.h"
#include "s4_msgs/ROI.h"
#include "s4_msgs/Presence.h"

namespace s4_msgs
{

  class TrackedObject : public ros::Msg
  {
    public:
      typedef s4_msgs::TrackedInfo _info_type;
      _info_type info;
      typedef s4_msgs::ROI _roi_type;
      _roi_type roi;
      typedef s4_msgs::Presence _presence_type;
      _presence_type presence;

    TrackedObject():
      info(),
      roi(),
      presence()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->info.serialize(outbuffer + offset);
      offset += this->roi.serialize(outbuffer + offset);
      offset += this->presence.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->info.deserialize(inbuffer + offset);
      offset += this->roi.deserialize(inbuffer + offset);
      offset += this->presence.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "s4_msgs/TrackedObject"; };
    const char * getMD5(){ return "8a4e2a37560926c310bdde72ba9b5a4d"; };

  };

}
#endif
