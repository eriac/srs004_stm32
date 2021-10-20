#pragma once

#include <vector>
#include <string>

namespace canlink_util
{

struct CanlinkMsg
{
    unsigned char source;
    unsigned char target;
    unsigned char command;
    bool request;
    unsigned char data[8];
    unsigned char size;
    unsigned char extra;
};

struct Serializer : public CanlinkMsg
{
    bool debug{false};

    bool decode(std::string msg)
    {
        if (msg.empty())
        {
            output_error("decode fail: empty\n");
            return false;
        }
        if (msg.front() != '$')
        {
            output_error("decode fail: not $\n");
            return false;
        }
        int valid_size = msg.find_first_of(';');
        if (valid_size == -1)
        {
            output_error("decode fail: not ;\n");
            return false;
        }
        msg.resize(valid_size);
        auto r = split(msg, ",");

        if (r.size() < 5)
        {
            output_error("decode fail: less item\n");
            return false;
        }

        if (r[0] != "$CLD")
        {
            output_error("decode fail: r[0] != $CLD\n");
            return false;
        }

        int temp_source_id = std::stoi(r[1], nullptr, 16);
        if (temp_source_id < 0 || 32 <= temp_source_id)
        {
            output_error("decode fail: nor 0<=r[1]<32\n");
            return false;
        }

        int temp_target_id = std::stoi(r[2], nullptr, 16);
        if (temp_target_id < 0 || 32 <= temp_target_id)
        {
            output_error("decode fail: nor 0<=r[2]<32\n");
            return false;
        }

        int temp_command = std::stoi(r[3], nullptr, 16);
        if (temp_command < 0 || 32 <= temp_command)
        {
            output_error("decode fail: nor 0<=r[3]<32\n");
            return false;
        }

        int temp_extra = std::stoi(r[4], nullptr, 16);
        if (temp_extra < 0 || 256 <= temp_extra)
        {
            output_error("decode fail: nor 0<=r[4]<256\n");
            return false;
        }

        int temp_data_size = 0;
        unsigned char temp_data[8];
        if (r.size() >= 6)
        {
            int data_size = r[5].size();
            if (data_size % 2 != 0)
            {
                // printf("decode fail: r[5].size() is not odd\n");
                return false;
            }
            temp_data_size = data_size / 2;
            for (int i = 0; i < temp_data_size; i++)
            {
                char c_str[2] = {r[5][i * 2], r[5][i * 2 + 1]};
                temp_data[i] = std::stoi(std::string(c_str), nullptr, 16);
            }
        }

        source = temp_source_id;
        target = temp_target_id;
        command = temp_command;
        extra = temp_extra;
        size = temp_data_size;
        for (int i = 0; i < temp_data_size; i++)
        {
            data[i] = temp_data[i];
        }
        return true;
    }

    std::string encode(void)
    {
        char output[40];
        int offset = snprintf(output, 40, "$CLD,%02X,%02X,%02X,%02X,", source, target, command, extra);
        for (int i = 0; i < size; i++)
        {
            offset += snprintf(output + offset, 40 - offset, "%02X", data[i]);
        }
        offset += snprintf(output + offset, 40 - offset, ";");
        return std::string(output);
    }

    std::vector<std::string> split(std::string str, std::string separator)
    {
        if (separator == "")
            return {str};
        std::vector<std::string> result;
        std::string tstr = str + separator;
        size_t l = tstr.length(), sl = separator.length();
        std::string::size_type pos = 0, prev = 0;

        for (; pos < l && (pos = tstr.find(separator, pos)) != std::string::npos; prev = (pos += sl))
        {
            result.emplace_back(tstr, prev, pos - prev);
        }
        return result;
    }

    void output_error(const char *array)
    {
        if (debug)
        {
            printf("%s\n", array);
        }
    }
};

// Msg Base
struct MsgBase {
    virtual unsigned int getID(void) = 0;
    virtual unsigned char getExtra(void) const = 0;
    virtual std::vector<unsigned char> getData(void) = 0;
    virtual bool decode(const std::vector<unsigned char> data, const unsigned char extra) = 0;
    virtual std::string getStr(void) = 0;
};

/* NODE ZONE
 * 1: receiver(SH)
 * 2: power controller (PW)
 * 3: wheel controller (WL)
 * 6: target sensor1 (TR1)
 */
#define CANLINK_NODE_SH 1
#define CANLINK_NODE_PW 2
#define CANLINK_NODE_WL 3
#define CANLINK_NODE_GN 4
#define CANLINK_NODE_UI 5
#define CANLINK_NODE_LN 6
#define CANLINK_NODE_SN 7
#define CANLINK_NODE_TR1 8
#define CANLINK_NODE_TR2 9
#define CANLINK_NODE_TR3 10
#define CANLINK_NODE_LT 11
#define CANLINK_NODE_ANY 127

/* MSG ZONE
 * 0~15: system
 * 16~31: common command
 * 32~47: common telemetry
 */

// #1 HeartBeat
#define CANLINK_CMD_HEART_BEAT 1
struct HeartBeat
{
    static constexpr unsigned char MODE_UNKNOWN = 0;
    static constexpr unsigned char MODE_BOOT = 1;
    static constexpr unsigned char MODE_ACTIVE = 2;
    static constexpr unsigned char MODE_FAULT = 3;
    static constexpr unsigned char MODE_DEBUG = 4;
    unsigned char mode{0};
    static constexpr unsigned char STATUS_SIZE = 16;
    bool warning[STATUS_SIZE]{0};
    bool error[STATUS_SIZE]{0};

    static unsigned char getID(void)
    {
        return CANLINK_CMD_HEART_BEAT;
    }
    unsigned char getExtra(void) const
    {
        return 0;
    }
    std::vector<unsigned char> getData(void)
    {
        std::vector<unsigned char> output;
        unsigned char warning_0 = 0;
        for(int i = 0; i< 8; i++){
            if(warning[i])warning_0 |= 1<<i;
        }
        unsigned char warning_1 = 0;
        for(int i = 0; i< 8; i++){
            if(warning[i+8])warning_1 |= 1<<i;
        }
        unsigned char error_0 = 0;
        for(int i = 0; i< 8; i++){
            if(error[i])error_0 |= 1<<i;
        }
        unsigned char error_1 = 0;
        for(int i = 0; i< 8; i++){
            if(error[i+8])error_1 |= 1<<i;
        }
        output.push_back(mode);
        output.push_back(warning_0);
        output.push_back(warning_1);
        output.push_back(error_0);
        output.push_back(error_1);
        return output;
    }
    bool decode(const std::vector<unsigned char> data, const unsigned char extra)
    {
        if (data.size() != 5)
        {
            return false;
        }
        mode = data[0];
        for(int i = 0; i < 8; i++){
            if(data[1]&(1<<i))warning[i]=true;
            else warning[i]=false;
        }
        for(int i = 0; i < 8; i++){
            if(data[2]&(1<<i))warning[i+8]=true;
            else warning[i+8]=false;
        }
        for(int i = 0; i < 8; i++){
            if(data[3]&(1<<i))error[i]=true;
            else error[i]=false;
        }
        for(int i = 0; i < 8; i++){
            if(data[4]&(1<<i))error[i+8]=true;
            else error[i+8]=false;
        }
        return true;
    }
};

// #2 BoardInfo
#define CANLINK_CMD_BOARD_INFO 2
struct BoardInfo
{
    unsigned char name[2];
    unsigned int revision{0};
    unsigned int id{0};

    static unsigned char getID(void)
    {
        return CANLINK_CMD_BOARD_INFO;
    }
    unsigned char getExtra(void) const
    {
        return 0;
    }
    std::vector<unsigned char> getData(void)
    {
        std::vector<unsigned char> output;
        output.push_back(name[0]);
        output.push_back(name[1]);
        output.push_back((revision >> 0)&0xff);
        output.push_back((revision >> 8)&0xff);
        output.push_back((id >> 0)&0xff);
        output.push_back((id >> 8)&0xff);
        output.push_back((id >> 16)&0xff);
        output.push_back((id >> 24)&0xff);
        return output;
    }
    bool decode(const std::vector<unsigned char> data, const unsigned char extra)
    {
        if (data.size() != 8)
        {
            return false;
        }
        name[0] = data[0];
        name[1] = data[1];
        revision = (data[3] << 8)|data[2];
        id = (data[7] << 24)|(data[6] << 16)|(data[5] << 8)|data[4];
        return true;
    }
};

// #10 LedColor
#define CANLINK_CMD_LED_COLOR 10
struct LedColor
{
    static constexpr unsigned char SET_BASE_COLOR = 1;
    unsigned char set_mode{0};
    unsigned char red{0};
    unsigned char green{0};
    unsigned char blue{0};

    static unsigned char getID(void)
    {
        return CANLINK_CMD_LED_COLOR;
    }
    unsigned char getExtra(void) const
    {
        return 0;
    }
    std::vector<unsigned char> getData(void)
    {
        std::vector<unsigned char> output;
        output.push_back(set_mode);
        output.push_back(red);
        output.push_back(green);
        output.push_back(blue);
        return output;
    }
    bool decode(const std::vector<unsigned char> data, const unsigned char extra)
    {
        if (data.size() != 4)
        {
            return false;
        }
        set_mode = data[0];
        red = data[1];
        green = data[2];
        blue = data[3];
        return true;
    }
};

// #11 MoveTarget
#define CANLINK_CMD_MOVE_TARGET 11
struct MoveTarget
{
    float vx{0.0f};
    float vy{0.0f};
    float rate{0.0f};

    union u_i_16{
        int16_t signed_value;
        uint16_t unsigned_value;
    };
    const static constexpr float scale = 1024.0f;

    static unsigned char getID(void)
    {
        return CANLINK_CMD_MOVE_TARGET;
    }
    unsigned char getExtra(void) const
    {
        return 0;
    }
    std::vector<unsigned char> getData(void)
    {
        std::vector<unsigned char> output;
        u_i_16 vx_temp, vy_temp, rate_temp;
        vx_temp.signed_value = (int)(vx*scale);
        vy_temp.signed_value = (int)(vy*scale);
        rate_temp.signed_value = (int)(rate*scale);

        output.push_back((vx_temp.unsigned_value>>0)&0xff);
        output.push_back((vx_temp.unsigned_value>>8)&0xff);
        output.push_back((vy_temp.unsigned_value>>0)&0xff);
        output.push_back((vy_temp.unsigned_value>>8)&0xff);
        output.push_back((rate_temp.unsigned_value>>0)&0xff);
        output.push_back((rate_temp.unsigned_value>>8)&0xff);
        return output;
    }
    bool decode(const std::vector<unsigned char> data, const unsigned char extra)
    {        
        if (data.size() != 6)
        {
            return false;
        }
        u_i_16 vx_temp, vy_temp, rate_temp;
        vx_temp.unsigned_value= data[1]<<8|data[0];
        vy_temp.unsigned_value= data[3]<<8|data[2];
        rate_temp.unsigned_value= data[5]<<8|data[4];
        vx = (float)vx_temp.signed_value/scale; 
        vy = (float)vy_temp.signed_value/scale; 
        rate = (float)rate_temp.signed_value/scale; 
        return true;
    }
};

// #20 TargetStatus
#define CANLINK_CMD_TARGET_STATUS 20
struct TargetStatus {
    unsigned int hit_count;

    unsigned int getID(void)
    {
        return CANLINK_CMD_TARGET_STATUS;
    }
    unsigned char getExtra(void) const
    {
        return 0;
    }
    std::vector<unsigned char> getData(void)
    {
        std::vector<unsigned char> output;
        output.push_back(hit_count & 0xff);
        output.push_back((hit_count >> 8) & 0xff);
        return output;
    }
    bool decode(const std::vector<unsigned char> data, const unsigned char extra)
    {
        if (data.size() != 2) {
            return false;
        }
        hit_count = data[1] << 8 | data[0];
        return true;
    }
};

// #21 PropoStatus
#define CANLINK_CMD_PROPO_STATUS 21
struct PropoStatus {
    float x{0.0f};
    float y{0.0f};
    float z{0.0f};
    float r{0.0f};
    unsigned char sw_a{0};
    unsigned char sw_b{0};
    unsigned char sw_c{0};
    unsigned char sw_d{0};

    union u_i_16{
        int16_t signed_value;
        uint16_t unsigned_value;
    };
    const int scale = 2000;

    unsigned int getID(void)
    {
        return CANLINK_CMD_PROPO_STATUS;
    }
    unsigned char getExtra(void) const
    {
        return 0;
    }
    std::vector<unsigned char> getData(void)
    {
        std::vector<unsigned char> output;
        u_i_16 x_temp, y_temp, z_temp, r_temp;
        x_temp.signed_value = std::min(std::max((int)(x * scale), -scale), scale);
        y_temp.signed_value = std::min(std::max((int)(y * scale), -scale), scale);
        z_temp.signed_value = std::min(std::max((int)(z * scale), -scale), scale);
        r_temp.signed_value = std::min(std::max((int)(r * scale), -scale), scale);
        output.push_back(x_temp.unsigned_value & 0xff);
        output.push_back(((y_temp.unsigned_value<<4) & 0xf0) | ((x_temp.unsigned_value>>8) & 0x0f));
        output.push_back((y_temp.unsigned_value>>4)&0xff);
        output.push_back(z_temp.unsigned_value&0xff);
        output.push_back(((r_temp.unsigned_value<<4)&0xf0) | ((z_temp.unsigned_value>>8)&0x0f));
        output.push_back((r_temp.unsigned_value>>4)&0xff);
        unsigned char sw_bits=0;
        sw_bits |= (sw_a<<0)&0x03;
        sw_bits |= (sw_b<<2)&0x0c;
        sw_bits |= (sw_c<<4)&0x30;
        sw_bits |= (sw_d<<6)&0xc0;
        output.push_back(sw_bits);
        return output;
    }
    bool decode(const std::vector<unsigned char> data, const unsigned char extra)
    {
        if (data.size() != 7) {
            return false;
        }
        u_i_16 x_temp, y_temp, z_temp, r_temp;
        uint16_t x_add = data[1]&1<<3 ? 0xf000 : 0;
        uint16_t y_add = data[2]&1<<7 ? 0xf000 : 0;
        uint16_t z_add = data[4]&1<<3 ? 0xf000 : 0;
        uint16_t r_add = data[5]&1<<7 ? 0xf000 : 0;
        x_temp.unsigned_value = x_add | (((data[1]<<8)&0xf00) | (data[0]&0xff));
        y_temp.unsigned_value = y_add | (((data[2]<<4)&0xff0) | ((data[1]>>4)&0x0f));
        z_temp.unsigned_value = z_add | (((data[4]<<8)&0xf00) | (data[3]&0xff));
        r_temp.unsigned_value = r_add | (((data[5]<<4)&0xff0) | ((data[4]>>4)&0x0f));
        x = (float)x_temp.signed_value/scale;
        y = (float)y_temp.signed_value/scale;
        z = (float)z_temp.signed_value/scale;
        r = (float)r_temp.signed_value/scale;
        sw_a = (data[6]>>0)&0x03;
        sw_b = (data[6]>>2)&0x03;
        sw_c = (data[6]>>4)&0x03;
        sw_d = (data[6]>>6)&0x03;
        return true;
    }
    std::string getStr(void){
        std::string output = "PropoStatus: ";
        char str[32];
        snprintf(str, 32, "%+5.2f %+5.2f %+5.2f %+5.2f %u %u %u %u", x, y, z, r, sw_a, sw_b, sw_c, sw_d);
        output += std::string(str);
        return output;
    }
};

// #22 LocalPosition
#define CANLINK_CMD_LOCAL_POSITION 22
struct LocalPosition {
    float x{0.0f};
    float y{0.0f};
    float theta{0.0f};

    union u_i_16{
        int16_t signed_value;
        uint16_t unsigned_value;
    };
    const int scale = 512;
    const int max_value = 0x7fff;

    unsigned int getID(void)
    {
        return CANLINK_CMD_LOCAL_POSITION;
    }
    unsigned char getExtra(void) const
    {
        return 0;
    }
    std::vector<unsigned char> getData(void)
    {
        std::vector<unsigned char> output;
        u_i_16 x_temp, y_temp, t_temp;
        x_temp.signed_value = std::min(std::max((int)(x * scale), -max_value), max_value);
        y_temp.signed_value = std::min(std::max((int)(y * scale), -max_value), max_value);
        t_temp.signed_value = std::min(std::max((int)(theta * scale), -max_value), max_value);
        output.push_back((x_temp.unsigned_value>>0) & 0xff);
        output.push_back((x_temp.unsigned_value>>8) & 0xff);
        output.push_back((y_temp.unsigned_value>>0) & 0xff);
        output.push_back((y_temp.unsigned_value>>8) & 0xff);
        output.push_back((t_temp.unsigned_value>>0) & 0xff);
        output.push_back((t_temp.unsigned_value>>8) & 0xff);
        return output;
    }
    bool decode(const std::vector<unsigned char> data, const unsigned char extra)
    {
        if (data.size() != 6) {
            return false;
        }
        u_i_16 x_temp, y_temp, t_temp;
        x_temp.unsigned_value = ((data[1]<<8)&0xff00) | (data[0]&0xff);
        y_temp.unsigned_value = ((data[3]<<8)&0xff00) | (data[2]&0xff);
        t_temp.unsigned_value = ((data[5]<<8)&0xff00) | (data[4]&0xff);
        x = (float)x_temp.signed_value/scale;
        y = (float)y_temp.signed_value/scale;
        theta = (float)t_temp.signed_value/scale;
        return true;
    }
    std::string getStr(void){
        std::string output = "LocalPosition: ";
        char str[32];
        snprintf(str, 32, "%+5.2f %+5.2f %+5.2f", x, y, theta);
        output += std::string(str);
        return output;
    }
};

// #23 PowerStatus
#define CANLINK_CMD_POWER_STATUS 23
struct PowerStatus
{
    static constexpr unsigned char SOURCE_UNKNOWN = 0;
    static constexpr unsigned char SOURCE_WALL = 1;
    static constexpr unsigned char SOURCE_BATTERY1 = 2;
    static constexpr unsigned char SOURCE_BATTERY2 = 3;

    unsigned char source{0};
    unsigned char system_remain_percent{0};
    unsigned int voltage_wall_mv{0}; // [mV]
    unsigned int voltage_bat1_mv{0}; // [mV]
    unsigned int voltage_bat2_mv{0}; // [mV]

    static unsigned char getID(void)
    {
        return CANLINK_CMD_POWER_STATUS;
    }
    unsigned char getExtra(void) const
    {
        return 0;
    }
    std::vector<unsigned char> getData(void)
    {
        std::vector<unsigned char> output;
        output.push_back(source);
        output.push_back(system_remain_percent & 0xff);
        output.push_back((voltage_wall_mv >> 0) & 0xff);
        output.push_back((voltage_wall_mv >> 8) & 0xff);
        output.push_back((voltage_bat1_mv >> 0) & 0xff);
        output.push_back((voltage_bat1_mv >> 8) & 0xff);
        output.push_back((voltage_bat2_mv >> 0) & 0xff);
        output.push_back((voltage_bat2_mv >> 8) & 0xff);
        return output;
    }
    bool decode(const std::vector<unsigned char> data, const unsigned char extra)
    {
        if (data.size() != 8)
        {
            return false;
        }
        source = data[0];
        system_remain_percent = data[1];
        voltage_wall_mv = (data[3] <<8) | data[2]; 
        voltage_bat1_mv = (data[5] <<8) | data[4]; 
        voltage_bat2_mv = (data[7] <<8) | data[6]; 
        return true;
    }
};

// #24 LocalVelocity
#define CANLINK_CMD_LOCAL_VELOCITY 24
struct LocalVelocity {
    float x{0.0f};
    float y{0.0f};
    float theta{0.0f};

    union u_i_16{
        int16_t signed_value;
        uint16_t unsigned_value;
    };
    const int linear_scale = 4096;
    const int angular_scale = 1024;
    const int max_value = 0x7fff;

    unsigned int getID(void)
    {
        return CANLINK_CMD_LOCAL_VELOCITY;
    }
    unsigned char getExtra(void) const
    {
        return 0;
    }
    std::vector<unsigned char> getData(void)
    {
        std::vector<unsigned char> output;
        u_i_16 x_temp, y_temp, t_temp;
        x_temp.signed_value = std::min(std::max((int)(x * linear_scale), -max_value), max_value);
        y_temp.signed_value = std::min(std::max((int)(y * linear_scale), -max_value), max_value);
        t_temp.signed_value = std::min(std::max((int)(theta * angular_scale), -max_value), max_value);
        output.push_back((x_temp.unsigned_value>>0) & 0xff);
        output.push_back((x_temp.unsigned_value>>8) & 0xff);
        output.push_back((y_temp.unsigned_value>>0) & 0xff);
        output.push_back((y_temp.unsigned_value>>8) & 0xff);
        output.push_back((t_temp.unsigned_value>>0) & 0xff);
        output.push_back((t_temp.unsigned_value>>8) & 0xff);
        return output;
    }
    bool decode(const std::vector<unsigned char> data, const unsigned char extra)
    {
        if (data.size() != 6) {
            return false;
        }
        u_i_16 x_temp, y_temp, t_temp;
        x_temp.unsigned_value = ((data[1]<<8)&0xff00) | (data[0]&0xff);
        y_temp.unsigned_value = ((data[3]<<8)&0xff00) | (data[2]&0xff);
        t_temp.unsigned_value = ((data[5]<<8)&0xff00) | (data[4]&0xff);
        x = (float)x_temp.signed_value/linear_scale;
        y = (float)y_temp.signed_value/linear_scale;
        theta = (float)t_temp.signed_value/angular_scale;
        return true;
    }
    std::string getStr(void){
        std::string output = "LocalVelocity: ";
        char str[32];
        snprintf(str, 32, "%+5.2f %+5.2f %+5.2f", x, y, theta);
        output += std::string(str);
        return output;
    }
};

// #25 MotorStatus
#define CANLINK_CMD_MOTOR_STATUS 25
struct MotorStatus {
    int mot0;
    int mot1;
    int mot2;
    int mot3;

    union u_i_16{
        int16_t signed_value;
        uint16_t unsigned_value;
    };

    unsigned int getID(void)
    {
        return CANLINK_CMD_MOTOR_STATUS;
    }
    unsigned char getExtra(void) const
    {
        return 0;
    }
    std::vector<unsigned char> getData(void)
    {
        std::vector<unsigned char> output;
        u_i_16 c0_temp, c1_temp, c2_temp, c3_temp;
        c0_temp.signed_value = mot0;
        c1_temp.signed_value = mot1;
        c2_temp.signed_value = mot2;
        c3_temp.signed_value = mot3;
        output.push_back((c0_temp.unsigned_value>>0) & 0xff);
        output.push_back((c0_temp.unsigned_value>>8) & 0xff);
        output.push_back((c1_temp.unsigned_value>>0) & 0xff);
        output.push_back((c1_temp.unsigned_value>>8) & 0xff);
        output.push_back((c2_temp.unsigned_value>>0) & 0xff);
        output.push_back((c2_temp.unsigned_value>>8) & 0xff);
        output.push_back((c3_temp.unsigned_value>>0) & 0xff);
        output.push_back((c3_temp.unsigned_value>>8) & 0xff);
        return output;
    }
    bool decode(const std::vector<unsigned char> data, const unsigned char extra)
    {
        if (data.size() != 8) {
            return false;
        }
        u_i_16 c0_temp, c1_temp, c2_temp, c3_temp;
        c0_temp.unsigned_value = ((data[1]<<8)&0xff00) | (data[0]&0xff);
        c1_temp.unsigned_value = ((data[3]<<8)&0xff00) | (data[2]&0xff);
        c2_temp.unsigned_value = ((data[5]<<8)&0xff00) | (data[4]&0xff);
        c3_temp.unsigned_value = ((data[7]<<8)&0xff00) | (data[6]&0xff);
        mot0 = c0_temp.signed_value;
        mot1 = c1_temp.signed_value;
        mot2 = c2_temp.signed_value;
        mot3 = c3_temp.signed_value;
        return true;
    }
    std::string getStr(void){
        std::string output = "MotorStatus: ";
        char str[32];
        snprintf(str, 32, "%d %d %d %d", mot0, mot1, mot2, mot3);
        output += std::string(str);
        return output;
    }
};

// #26 MotorTarget
#define CANLINK_CMD_MOTOR_TARGET 26
struct MotorTarget {
    int mot0;
    int mot1;
    int mot2;
    int mot3;

    union u_i_16{
        int16_t signed_value;
        uint16_t unsigned_value;
    };

    unsigned int getID(void)
    {
        return CANLINK_CMD_MOTOR_TARGET;
    }
    unsigned char getExtra(void) const
    {
        return 0;
    }
    std::vector<unsigned char> getData(void)
    {
        std::vector<unsigned char> output;
        u_i_16 c0_temp, c1_temp, c2_temp, c3_temp;
        c0_temp.signed_value = mot0;
        c1_temp.signed_value = mot1;
        c2_temp.signed_value = mot2;
        c3_temp.signed_value = mot3;
        output.push_back((c0_temp.unsigned_value>>0) & 0xff);
        output.push_back((c0_temp.unsigned_value>>8) & 0xff);
        output.push_back((c1_temp.unsigned_value>>0) & 0xff);
        output.push_back((c1_temp.unsigned_value>>8) & 0xff);
        output.push_back((c2_temp.unsigned_value>>0) & 0xff);
        output.push_back((c2_temp.unsigned_value>>8) & 0xff);
        output.push_back((c3_temp.unsigned_value>>0) & 0xff);
        output.push_back((c3_temp.unsigned_value>>8) & 0xff);
        return output;
    }
    bool decode(const std::vector<unsigned char> data, const unsigned char extra)
    {
        if (data.size() != 8) {
            return false;
        }
        u_i_16 c0_temp, c1_temp, c2_temp, c3_temp;
        c0_temp.unsigned_value = ((data[1]<<8)&0xff00) | (data[0]&0xff);
        c1_temp.unsigned_value = ((data[3]<<8)&0xff00) | (data[2]&0xff);
        c2_temp.unsigned_value = ((data[5]<<8)&0xff00) | (data[4]&0xff);
        c3_temp.unsigned_value = ((data[7]<<8)&0xff00) | (data[6]&0xff);
        mot0 = c0_temp.signed_value;
        mot1 = c1_temp.signed_value;
        mot2 = c2_temp.signed_value;
        mot3 = c3_temp.signed_value;
        return true;
    }
    std::string getStr(void){
        std::string output = "MotorTarget: ";
        char str[32];
        snprintf(str, 32, "%d %d %d %d", mot0, mot1, mot2, mot3);
        output += std::string(str);
        return output;
    }
};

// #27 MotorTarget
#define CANLINK_CMD_MOTOR_OUTPUT 27
struct MotorOutput {
    float mot0;
    float mot1;
    float mot2;
    float mot3;

    union u_i_16{
        int16_t signed_value;
        uint16_t unsigned_value;
    };

    const int scale = 1024;

    unsigned int getID(void)
    {
        return CANLINK_CMD_MOTOR_OUTPUT;
    }
    unsigned char getExtra(void) const
    {
        return 0;
    }
    std::vector<unsigned char> getData(void)
    {
        std::vector<unsigned char> output;
        u_i_16 c0_temp, c1_temp, c2_temp, c3_temp;
        c0_temp.signed_value = mot0 * scale;
        c1_temp.signed_value = mot1 * scale;
        c2_temp.signed_value = mot2 * scale;
        c3_temp.signed_value = mot3 * scale;
        output.push_back((c0_temp.unsigned_value>>0) & 0xff);
        output.push_back((c0_temp.unsigned_value>>8) & 0xff);
        output.push_back((c1_temp.unsigned_value>>0) & 0xff);
        output.push_back((c1_temp.unsigned_value>>8) & 0xff);
        output.push_back((c2_temp.unsigned_value>>0) & 0xff);
        output.push_back((c2_temp.unsigned_value>>8) & 0xff);
        output.push_back((c3_temp.unsigned_value>>0) & 0xff);
        output.push_back((c3_temp.unsigned_value>>8) & 0xff);
        return output;
    }
    bool decode(const std::vector<unsigned char> data, const unsigned char extra)
    {
        if (data.size() != 8) {
            return false;
        }
        u_i_16 c0_temp, c1_temp, c2_temp, c3_temp;
        c0_temp.unsigned_value = ((data[1]<<8)&0xff00) | (data[0]&0xff);
        c1_temp.unsigned_value = ((data[3]<<8)&0xff00) | (data[2]&0xff);
        c2_temp.unsigned_value = ((data[5]<<8)&0xff00) | (data[4]&0xff);
        c3_temp.unsigned_value = ((data[7]<<8)&0xff00) | (data[6]&0xff);
        mot0 = (float)c0_temp.signed_value / scale;
        mot1 = (float)c1_temp.signed_value / scale;
        mot2 = (float)c2_temp.signed_value / scale;
        mot3 = (float)c3_temp.signed_value / scale;
        return true;
    }
    std::string getStr(void){
        std::string output = "MotorOutput: ";
        char str[32];
        snprintf(str, 32, "%+5.2f %+5.2f %+5.2f %+5.2f", mot0, mot1, mot2, mot3);
        output += std::string(str);
        return output;
    }
};

}; // namespace canlink_util
