#pragma once

#include <ctype.h>
#include <map>
#include <string>
#include <vector>
#include "mbed.h"

class MonBase
{
public:
  MonBase(PinName tx_pin, PinName rx_pin) : serial_(tx_pin, rx_pin, 115200)
  {
    serial_.attach(callback(this, &MonBase::rxCallback));
    serial_.printf("\nstart\n");
    serial_.printf("> ");
    input_.reserve(32);
  }

  void register_func(std::string name, Callback<std::string(std::vector<std::string>)> func)
  {
    command_list_[name] = func;
  }

  void process(void)
  {
    if (recv_nl_)
    {
      recv_nl_ = false;
      std::vector<std::string> command = split(input_, ' ');
      input_.clear();
      printf("\n");

      if (command.empty())
      {
        serial_.printf("> ");
        return;
      }

      if (command_list_.count(command[0]) == 0)
      {
        serial_.printf("%s not found\n> ", command[0].c_str());
        return;
      }

      Callback<std::string(std::vector<std::string>)> func = command_list_[command[0]];
      std::string result = func(command);
      serial_.printf("%s\n", result.c_str());
      serial_.printf("> ");
      return;
    }
  }

private:
  std::vector<std::string> split(std::string str, char del)
  {
    std::vector<std::string> result;
    if (str.empty())
    {
      return result;
    }
    size_t first = 0;
    size_t last = str.find_first_of(del);

    while (first < str.size())
    {
      std::string subStr(str, first, last - first);

      result.push_back(subStr);

      first = last + 1;
      last = str.find_first_of(del, first);

      if (last == std::string::npos)
      {
        last = str.size();
      }
    }

    return result;
  }

  void rxCallback(void)
  {
    char recv = serial_.getc();
    if (!recv_nl_)
    {
      if (recv == '\r' || recv == '\n')
      {
        recv_nl_ = true;
      }
      else if (recv == '\b')
      {
        if (!input_.empty())
          input_.resize(input_.size() - 1, ' ');
        serial_.putc('\b');
        serial_.putc(' ');
        serial_.putc('\b');
      }
      else if (isprint(recv))
      {
        if (input_.size() < input_.capacity())
        {
          input_.push_back(recv);
          serial_.putc(recv);
        }
      }
    }
  }

public:
  RawSerial serial_;
  std::string input_;
  bool recv_nl_;

protected:
  std::map<std::string, Callback<std::string(std::vector<std::string>)> > command_list_;
};

class Mon : public MonBase
{
public:
  Mon(PinName tx_pin, PinName rx_pin) : MonBase(tx_pin, rx_pin)
  {
    register_func("help", callback(this, &Mon::helpCommand));
    register_func("date", callback(this, &Mon::dateCommand));
  }

private:
  std::string helpCommand(std::vector<std::string> command)
  {
    std::string result = "";
    for (std::map<std::string, Callback<std::string(std::vector<std::string>)> >::iterator iter = command_list_.begin();
         iter != command_list_.end(); iter++)
    {
      result += iter->first + "\n";
    }
    return result;
  }

  std::string dateCommand(std::vector<std::string> command)
  {
    std::string result = "build at ";
    result += __DATE__;
    result += " ";
    result += __TIME__;
    result += "(UTC)";
    return result;
  }
};
