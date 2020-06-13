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
  void register_int(std::string name, int value)
  {
    int_param_[name] = value;
  }
  std::string monCallback(std::vector<std::string> command)
  {
    std::string result = "";
    if (command[1] == "list")
    {
      for (std::map<std::string, int>::iterator iter = int_param_.begin(); iter != int_param_.end(); iter++)
      {
        result += iter->first + " " + std::to_string(iter->second) + "\n";
      }
    }
    else if (command[1] == "set")
    {
      int value = atoi(command[3].c_str());
      register_int(command[2], value);
    }
    return result;
  }

private:
  std::map<std::string, int> int_param_;
};