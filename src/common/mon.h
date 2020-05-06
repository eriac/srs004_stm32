#pragma once

#include "mbed.h"
#include <ctype.h>
#include <string>
#include <vector>
#include <map>

class Mon
{
public:
    Mon(PinName tx_pin, PinName rx_pin) : serial_(tx_pin, rx_pin, 115200)
    {
        serial_.printf("\nstart\n");
        serial_.printf("> ");
        serial_.attach(callback(this, &Mon::rxCallback));
        register_func("help", callback(this, &Mon::helpCommand));
        register_func("date", callback(this, &Mon::dateCommand));
    }

    void register_func(std::string name, Callback<void(std::vector<std::string>)> func)
    {
        command_list_[name] = func;
    }

    void process(void)
    {
        if(recv_nl_) {
            recv_nl_ = false;
            std::vector<std::string> command = split(input_, ' ');
            input_.clear();
            printf("\n");

            if(command.empty()) {
                serial_.printf("> ");
                return;
            }

            if(command_list_.count(command[0])==0) {
                serial_.printf("%s not found\n> ", command[0].c_str());
                return;
            }

            Callback<void(std::vector<std::string>)> func = command_list_[command[0]];
            func(command);
            serial_.printf("> ");
            return;
        }
    }

private:
    std::vector<std::string> split(std::string str, char del)
    {
        std::vector<std::string> result;
        if(str.empty()) {
            return result;
        }
        size_t first = 0;
        size_t last = str.find_first_of(del);


        while (first < str.size()) {
            std::string subStr(str, first, last - first);

            result.push_back(subStr);

            first = last + 1;
            last = str.find_first_of(del, first);

            if (last == std::string::npos) {
                last = str.size();
            }
        }

        return result;
    }

    void rxCallback(void)
    {
        char recv = serial_.getc();
        if(!recv_nl_) {
            if(recv == '\r' || recv == '\n') {
                recv_nl_ = true;
            } else if(recv == '\b') {
                if(!input_.empty())input_.resize(input_.size()-1, ' ');
                serial_.putc('\b');
                serial_.putc(' ');
                serial_.putc('\b');
            } else if(isprint(recv)) {
                input_.push_back(recv);
                serial_.putc(recv);
            }
        }
    }

    void helpCommand(std::vector<std::string> command)
    {
        for(std::map<std::string,Callback<void(std::vector<std::string>)> >::iterator iter = command_list_.begin(); iter != command_list_.end(); iter++) {
            printf("%s\n", iter->first.c_str());
        }
    }

    void dateCommand(std::vector<std::string> command)
    {
        printf("build at %s %s (UTC)\n", __DATE__, __TIME__);
    }

    RawSerial serial_;
    std::string input_;
    bool recv_nl_;
    std::map<std::string,Callback<void(std::vector<std::string>)> > command_list_;
};

class Param
{
public:
    Param() {}
    void register_int(std::string name, int value)
    {
        int_param_[name] = value;
    }
    void monCallback(std::vector<std::string> command)
    {
        if(command[1] == "list") {
            for(std::map<std::string, int>::iterator iter = int_param_.begin(); iter != int_param_.end(); iter++) {
                printf("%s\t%i\n", iter->first.c_str(), iter->second);
            }
        } else if(command[1] == "set") {
            int value = atoi(command[3].c_str());
            register_int(command[2], value);
        }
    }

private:
    std::map<std::string,int>int_param_;

};