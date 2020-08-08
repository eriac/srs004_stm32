#pragma once

#include <memory>
#include <string>
#include <vector>
#include "mbed.h"

class HzHandler{
  public:
    HzHandler(){}
    bool check(){
      if(flag){
        flag = false;
        return true;
      }
      else{
        return false;
      }
    }
    float hz;
    bool flag;
};

class HzTimer
{
public:
  HzTimer()
  {
    handle1 = std::make_shared<HzHandler>();
  }

  std::shared_ptr<HzHandler> registerTimer(const float hz){
    int interval = 1000 * 1000 / hz;
    handle1->hz = hz;
    handle1->flag = false;


    // flipper.attach_us(callback(this, &HzTimer::timerCallback), interval);
    flipper.attach_us([&](void){
      handle1->flag = true;
    }, interval);
    return handle1;
  }

  void timerCallback() {
    flag = true;
  }

  void timerCallback2(std::shared_ptr<HzHandler> handle) {
    handle->flag = true;
  }
  
  bool flag;
  Ticker flipper;
  std::shared_ptr<HzHandler> handle1;

  // std::vector<std::shared_ptr<EventQueue> > queue_list_;
};
