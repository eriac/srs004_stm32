#pragma once

#include "canlink.h"
#include <vector>

namespace CanlinkConvertor {

// #20 TargetStatus
struct TargetStatus {
    unsigned int hit_count;

    unsigned int getID(void)
    {
        return 20;
    }

    bool decode(const CanlinkMsg &msg)
    {
        if (msg.len != 2) {
            return false;
        }
        hit_count = msg.data[1] << 8 | msg.data[0];
        return true;
    }

    bool encode(CanlinkMsg &msg)
    {
        msg.data[0] = hit_count & 0xff;
        msg.data[1] = (hit_count >> 8) & 0xff;
        msg.len = 2;
        return true;
    }

    std::vector<unsigned char> encode(void)
    {
        std::vector<unsigned char> output;
        output.push_back(hit_count & 0xff);
        output.push_back((hit_count >> 8) & 0xff);
        return output;
    }

};

}; // namespace CanlinkConvertor
