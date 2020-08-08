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
    led1_ = !led1_;
  }

  bool registerParam(std::string name, auto value){
    return param_.registerParam(name, value);
  }

  bool updateParam(std::string name, auto value){
    return param_.updateParam(name, value);
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
      for (std::map<std::string, int>::iterator iter = param_.int_param_.begin(); iter != param_.int_param_.end(); iter++)
      {
        result += iter->first + " " + std::to_string(iter->second) + "\n";
      }
    }
    else if (command[1] == "set")
    {
      int value = atoi(command[3].c_str());
      param_.updateParam(command[2], value);
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
        else if (target_side.type == param_type::TYPE_FLOAT)
          result += std::string(target_side.name) + " FLOAT: " + std::to_string(target_side.value.float_value.data)+"\n";
        else
          result += "OTHER:" + std::to_string((int)(target_side.type))+"\n";
      }
    }
    return result;
  }

  DigitalOut led1_;
  DigitalOut led2_;
  Monitor monitor_;
  Param param_;
  I2C i2c0_;
  I2CEEprom eeprom_;
  Canlink canlink_;
  HzTimer hz_timer_;
};
