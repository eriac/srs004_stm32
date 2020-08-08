#pragma once

#include <ctype.h>
#include <map>
#include <string>
#include <vector>
#include "mbed.h"

struct CanlinkMsg{
    unsigned char source_id;
    unsigned char target_id;
    unsigned char command_id;
    unsigned char ext_data;
    unsigned char data[8];
    signed char len;
};

class Canlink
{
public:
  Canlink(PinName rd_pin, PinName td_pin, int baudrate) : can_(rd_pin, td_pin, baudrate), device_id_(0)
  {
     can_.frequency(1000000);
    filter_handle_ = can_.filter(device_id_ << 15, 0x7f << 15, CANExtended);
    printf("filter: %u\n", filter_handle_);
  }

  void setID(unsigned char id){
    device_id_ = id & 0x7f;
    filter_handle_ = can_.filter(device_id_ << 15, 0x7f << 15, CANExtended, filter_handle_);
  }

  void register_func(unsigned char command, Callback<void(CanlinkMsg)> func)
  {
    command_list_[command] = func;
  }

  void send(unsigned char target_id, unsigned char command_id, std::vector<unsigned char> data){
    CANMessage can_msg;
    can_msg.id = device_id_ << 22 | target_id << 15 | command_id << 8;
    can_msg.format = CANExtended;
    can_msg.len = data.size();
    for(size_t i = 0; i < data.size(); i++){
        can_msg.data[i] = data[i]; 
    }
    can_.write(can_msg);
  }

  void process(void)
  {
    CANMessage can_msg;
    while(can_.read(can_msg)) {
      if(can_msg.format == CANExtended){
        CanlinkMsg canlink_msg;
        canlink_msg.source_id = (can_msg.id >> 22) & 0x7f;
        canlink_msg.target_id = (can_msg.id >> 15) & 0x7f;
        canlink_msg.command_id = (can_msg.id >> 8) & 0x7f;
        canlink_msg.ext_data = (can_msg.id >> 0) & 0xff;
        canlink_msg.len = can_msg.len;
        for(int i = 0; i < can_msg.len; i++){
            canlink_msg.data[i] = can_msg.data[i];
        }        
        if(canlink_msg.target_id == device_id_){
            if(command_list_.count(canlink_msg.command_id) == 1){
                Callback<void(CanlinkMsg)> func = command_list_[canlink_msg.command_id];
                func(canlink_msg);
            }
        }
      }
    } 
  }

public:
  CAN can_;
  unsigned char device_id_;
  std::map<unsigned int, Callback<void(CanlinkMsg)> > command_list_;
  int filter_handle_;
};
