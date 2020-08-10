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
  bool registerParam(std::string name, float value)
  {
    float_param_[name] = value;
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
  bool updateParam(std::string name, float value)
  {
    if(float_param_.count(name) != 0){
      float_param_[name] = value;
      return true;
    }
    return false;
  }
  bool getParam(std::string name, int& value)
  {
    if(int_param_.count(name) != 0){
      value = int_param_[name];
      return true;
    }
    return false;
  }
  bool getParam(std::string name, float& value)
  {
    if(float_param_.count(name) != 0){
      value = float_param_[name];
      return true;
    }
    return false;
  }

  std::map<std::string, int> int_param_;
  std::map<std::string, float> float_param_;
};