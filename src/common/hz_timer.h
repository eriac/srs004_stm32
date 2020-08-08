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
    Ticker ticker;
    float hz;
    bool flag;
};

class HzTimer
{
public:
  HzTimer()
  {
    handles_.clear();
  }

  std::shared_ptr<HzHandler> registerTimer(const float hz){
    std::shared_ptr<HzHandler> handle1 = std::make_shared<HzHandler>();
    handles_.push_back(handle1);
    int interval = 1000 * 1000 / hz;
    handle1->hz = hz;
    handle1->flag = false;

    handle1->ticker.attach_us([&](void){
      handle1->flag = true;
    }, interval);
    return handle1;
  }

  std::vector<std::shared_ptr<HzHandler> >handles_;
};
