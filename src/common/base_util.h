#pragma once

#include "mbed.h"
#include "monitor.h"
#include "param.h"
#include "m24c64.h"
#include "canlink.h"
#include "hz_timer.h"

#define EEPROM_MAX_PAGE 4

class BaseUtil
{
public:
  BaseUtil():led1_(PB_12), led2_(PB_13), monitor_(USBTX, USBRX, 115200), param_(), i2c0_(PB_7, PB_6), eeprom_(i2c0_), canlink_(PA_11, PA_12, 1000000)
  {
    monitor_.register_func("help", callback(this, &BaseUtil::monitorHelpCommand));
    monitor_.register_func("date", callback(this, &BaseUtil::monitorDateCommand));
    monitor_.register_func("param", callback(this, &BaseUtil::monitorParamCallback));
  }

  void process(void)
  {
    monitor_.process();
    canlink_.process();
  }

  bool registerParam(std::string name, auto value){
    return param_.registerParam(name, value);
  }
  bool updateParam(std::string name, auto value){
    return param_.updateParam(name, value);
  }
  bool getParam(std::string name, auto& value){
    return param_.getParam(name, value);
  }

  bool loadParam(){
    param_union pages[EEPROM_MAX_PAGE];
    for(int i = 0; i < EEPROM_MAX_PAGE; i++){
      pages[i] = eeprom_.read_page(i);
    }
    for(int index = 0; index < EEPROM_MAX_PAGE * 2; index++){
      int page = index / 2;
      int side = index % 2;
      auto& target_side = pages[page].param[side];
      if (target_side.type == param_type::TYPE_INT){
        param_.updateParam(target_side.name, target_side.value.int_value.data);
      }
      else if (target_side.type == param_type::TYPE_FLOAT){
        param_.updateParam(target_side.name, target_side.value.float_value.data);
      }
    }
    return true;
  }

  void setCanlinkID(unsigned char id){
    canlink_.setID(id);
  }

  void registerCanlink(unsigned char command, Callback<void(CanlinkMsg)> func){
    canlink_.register_func(command, func);
  }

  void sendCanlink(unsigned char target_id, unsigned char command_id, std::vector<unsigned char> data){
    canlink_.send(target_id, command_id, data);
  }

  void registerMonitor(std::string name, Callback<std::string(std::vector<std::string>)> func){
    monitor_.register_func(name, func);
  }

  void toggleLed(int index){
    if(index == 1)led1_ = !led1_;
    else if(index == 2)led2_ = !led2_;
  }

  void turnOnLed(int index){
    if(index == 1)led1_ = 1;
    else if(index == 2)led2_ = 1;
  }

  void turnOffLed(int index){
    if(index == 1)led1_ = 0;
    else if(index == 2)led2_ = 0;
  }

  std::shared_ptr<HzHandler> registerTimer(const float hz){
    return hz_timer_.registerTimer(hz);
  }

  std::string monitorHelpCommand(std::vector<std::string> command)
  {
    std::string result = "";
    for (std::map<std::string, Callback<std::string(std::vector<std::string>)> >::iterator iter = monitor_.command_list_.begin();
         iter != monitor_.command_list_.end(); iter++)
    {
      result += iter->first + "\n";
    }
    return result;
  }

  std::string monitorDateCommand(std::vector<std::string> command)
  {
    std::string result = "build at ";
    result += __DATE__;
    result += " ";
    result += __TIME__;
    result += "(UTC)";
    return result;
  }

  std::string monitorParamCallback(std::vector<std::string> command)
  {
    std::string result = "";
    if (command[1] == "list")
    {
      result += "[INT]\n";
      for (std::map<std::string, int>::iterator iter = param_.int_param_.begin(); iter != param_.int_param_.end(); iter++)
      {
        result += iter->first + " " + std::to_string(iter->second) + "\n";
      }
      result += "[FLOAT]\n";
      for (std::map<std::string, float>::iterator iter = param_.float_param_.begin(); iter != param_.float_param_.end(); iter++)
      {
        result += iter->first + " " + std::to_string(iter->second) + "\n";
      }
    }
    else if (command[1] == "set")
    {
      std::string s = command[3];
      bool digit = false;
      // bool sign = false;
      bool point = false;
      bool other = false;
      for(auto it = s.begin(); it != s.end(); it++){
        if(std::isdigit(*it))digit = true;
        // else if(*it == '+')sign = true;
        // else if(*it == '-')sign = true;
        else if(*it == '.')point = true;
        else  other = true;
      }

      if(digit && !point && !other){
        int value = std::stoi(command[3]);
        param_.updateParam(command[2], value);
        result = "int param " + std::to_string(value) + " -> " + command[2];
      }
      else if(digit && point && !other){
        float value = std::stof(command[3]);
        param_.updateParam(command[2], value);
        result = "float param " + std::to_string(value) + " -> " + command[2];
      }
      else{
        result = "error: not number";
      }
    }
    else if (command[1] == "clear")
    {
      for (auto& item : param_.int_param_){
        item.second = 0;
      }
    }
    else if (command[1] == "erase")
    {
      for(int i = 0; i < EEPROM_MAX_PAGE; i++){
        eeprom_.clear_page(i);
      }
    }
    else if (command[1] == "store")
    {
      unsigned int index = 0;
      param_union pages[EEPROM_MAX_PAGE];
      for(auto item : param_.int_param_){
        int page = index / 2;
        int side = index % 2;
        auto& target_side = pages[page].param[side];
        strncpy(target_side.name, item.first.c_str(), 7);
        target_side.type = param_type::TYPE_INT;
        target_side.value.int_value.data = item.second;        
        index ++;
        if(index / 2 == EEPROM_MAX_PAGE)break;
      }
      for(auto item : param_.float_param_){
        int page = index / 2;
        int side = index % 2;
        auto& target_side = pages[page].param[side];
        strncpy(target_side.name, item.first.c_str(), 7);
        target_side.type = param_type::TYPE_FLOAT;
        target_side.value.float_value.data = item.second;        
        index ++;
        if(index / 2 == EEPROM_MAX_PAGE)break;
      }
      for(int i = 0; i < EEPROM_MAX_PAGE; i++){
        eeprom_.write_page(i, pages[i]);
        thread_sleep_for(20);
      }
    }
    else if (command[1] == "load")
    {
      param_union pages[EEPROM_MAX_PAGE];
      for(int i = 0; i < EEPROM_MAX_PAGE; i++){
        pages[i] = eeprom_.read_page(i);
      }

      for(int index = 0; index < EEPROM_MAX_PAGE * 2; index++){
        int page = index / 2;
        int side = index % 2;
        auto& target_side = pages[page].param[side];
        if (target_side.type == param_type::TYPE_INT){
          param_.updateParam(target_side.name, target_side.value.int_value.data);
          result += std::string(target_side.name) + " INT: " + std::to_string(target_side.value.int_value.data)+"\n";
        }
        else if (target_side.type == param_type::TYPE_FLOAT){
          param_.updateParam(target_side.name, target_side.value.float_value.data);
          result += std::string(target_side.name) + " FLOAT: " + std::to_string(target_side.value.float_value.data)+"\n";
        }
        else{
          result += "OTHER:" + std::to_string((int)(target_side.type))+"\n";
        }
      }
    }
    return result;
  }

private:
  DigitalOut led1_;
  DigitalOut led2_;
  Monitor monitor_;
  Param param_;
  I2C i2c0_;
  I2CEEprom eeprom_;
  Canlink canlink_;
  HzTimer hz_timer_;
};
