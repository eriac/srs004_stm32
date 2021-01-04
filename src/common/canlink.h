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
    can_.frequency(baudrate);
    // can_.mode(CAN::GlobalTest);
    filter_handle_ = can_.filter(device_id_ << 15, 0x7f << 15, CANExtended);
    printf("filter: %u\n", filter_handle_);

    // can_.mode(CAN::Normal);
    // can_.attach(this, &Canlink::ew_callback, CAN::EwIrq);
    // can_.attach(this, &Canlink::do_callback, CAN::DoIrq);
    // can_.attach(this, &Canlink::wu_callback, CAN::WuIrq);
    // can_.attach(this, &Canlink::ep_callback, CAN::EpIrq);
    // can_.attach(this, &Canlink::al_callback, CAN::AlIrq);
    // can_.attach(this, &Canlink::be_callback, CAN::BeIrq);
  }

  void setID(unsigned char id){
    device_id_ = id & 0x7f;
    filter_handle_ = can_.filter(device_id_ << 15, 0x7f << 15, CANExtended, filter_handle_);
  }

  void register_func(unsigned char command, Callback<void(CanlinkMsg)> func)
  {
    command_list_[command] = func;
  }

  void send(unsigned char target_id, unsigned char command_id, unsigned char extra, std::vector<unsigned char> data){
    CANMessage can_msg;
    can_msg.id = device_id_ << 22 | target_id << 15 | command_id << 8;
    can_msg.format = CANExtended;
    can_msg.len = data.size();
    for(size_t i = 0; i < data.size(); i++){
        can_msg.data[i] = data[i]; 
    }
    can_.write(can_msg);
  }

  void send(unsigned char target_id, unsigned char command_id, std::vector<unsigned char> data){
    send(target_id, command_id, 0, data);
  }

  void process(void)
  {
    // unsigned char re = can_.rderror();
    // unsigned char te = can_.tderror();
    // if(re != 0 || te !=0){
    //   printf("re: %u, tr: %u\n", re, te);
    //   can_.reset();
    //   // can_.monitor(true);
    // }
    // static int counter;
    // counter++;
    // printf("%02u %u %u %u %u %u %u %u %u\n", counter, rx_irq_counter_, tx_irq_counter_, ew_irq_counter_, do_irq_counter_, wu_irq_counter_, ep_irq_counter_, al_irq_counter_, be_irq_counter_);

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

// RxIrq for message received,
// TxIrq for transmitted or aborted,
// EwIrq for error warning,
// DoIrq for data overrun,
// WuIrq for wake-up,
// EpIrq for error passive,
// AlIrq for arbitration lost,
// BeIrq for bus error

  void rx_callback(void){rx_irq_counter_++;}
  void tx_callback(void){tx_irq_counter_++;}
  void ew_callback(void){ew_irq_counter_++;}
  void do_callback(void){do_irq_counter_++;}
  void wu_callback(void){wu_irq_counter_++;}
  void ep_callback(void){ep_irq_counter_++;}
  void al_callback(void){al_irq_counter_++;}
  void be_callback(void){be_irq_counter_++;}

  int rx_irq_counter_;
  int tx_irq_counter_;
  int ew_irq_counter_;
  int do_irq_counter_;
  int wu_irq_counter_;
  int ep_irq_counter_;
  int al_irq_counter_;
  int be_irq_counter_;
};
