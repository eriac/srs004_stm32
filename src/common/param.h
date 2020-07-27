#pragma once

#include <map>
#include <string>
#include <vector>

class Param
{
public:
  Param()
  {
  }
  bool registerParam(std::string name, int value)
  {
    int_param_[name] = value;
    return true;
  }
  bool updateParam(std::string name, int value)
  {
    if(int_param_.count(name) != 0){
      int_param_[name] = value;
      return true;
    }
    return false;
  }

  std::map<std::string, int> int_param_;
};