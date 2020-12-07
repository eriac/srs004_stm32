#pragma once

#include "canlink.h"
#include <vector>

namespace CanlinkConvertor {

// #10 LedColor
#define CANLINK_CMD_ID_LED_COLOR 10
struct LedColor {
    static constexpr unsigned char SET_BASE_COLOR = 1;

    unsigned char set_mode{0};
    unsigned char red{0};
    unsigned char green{0};
    unsigned char blue{0};

    unsigned int getID(void)
    {
        return 10;
    }

    bool decode(const CanlinkMsg &msg)
    {
        if (msg.len != 4) {
            return false;
        }
        set_mode = msg.data[0];
        red = msg.data[1];
        green = msg.data[2];
        blue = msg.data[3];
        return true;
    }

    std::vector<unsigned char> encode(void)
    {
        std::vector<unsigned char> output;
        output.push_back(set_mode);
        output.push_back(red);
        output.push_back(green);
        output.push_back(blue);
        return output;
    }

};

// #20 TargetStatus
#define CANLINK_CMD_ID_TARGET_STATUS 20
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

// #21 PropoStatus
#define CANLINK_CMD_ID_PROPO_STATUS 21
struct PropoStatus {
    unsigned int axis_x;
    unsigned int axis_y;
    unsigned int axis_z;
    unsigned int axis_r;
    unsigned char sw_a;
    unsigned char sw_b;
    unsigned char sw_c;
    unsigned char sw_d;

    constexpr static unsigned char low_pos = 0;
    constexpr static unsigned char mid_pos = 1;
    constexpr static unsigned char high_pos = 2;
    
    unsigned int getID(void)
    {
        return 21;
    }

    bool decode(const CanlinkMsg &msg)
    {
        if (msg.len != 7) {
            return false;
        }
        axis_x = (msg.data[1] << 8 | msg.data[0] >> 0) & 0xfff;
        axis_y = (msg.data[2] << 4 | msg.data[1] >> 4) & 0xfff;
        axis_z = (msg.data[4] << 8 | msg.data[3] >> 0) & 0xfff;
        axis_r = (msg.data[5] << 4 | msg.data[4] >> 4) & 0xfff;
        sw_a = (msg.data[6] >> 0) & 0x03;
        sw_b = (msg.data[6] >> 2) & 0x03;
        sw_c = (msg.data[6] >> 4) & 0x03;
        sw_d = (msg.data[6] >> 6) & 0x03;
        return true;
    }

    std::vector<unsigned char> encode(void)
    {
        std::vector<unsigned char> output;
        output.push_back(axis_x & 0xff);
        output.push_back(((axis_y<<4)&0xf0) | ((axis_x>>8)&0x0f));
        output.push_back(axis_y>>4 & 0xff);
        output.push_back(axis_z & 0xff);
        output.push_back(((axis_r<<4)&0xf0) | ((axis_z>>8)&0x0f));
        output.push_back(axis_r>>4 & 0xff);
        output.push_back(((sw_d&0x03)<<6) | ((sw_c&0x03)<<4) | ((sw_b&0x03)<<2)| ((sw_a&0x03)<<0));
        return output;
    }
};

}; // namespace CanlinkConvertor
