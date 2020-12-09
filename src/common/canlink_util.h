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
        long l = tstr.length(), sl = separator.length();
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

/* MSG ZONE
 * 0~15: system
 * 16~31: common command
 * 32~47: common telemetry
 */

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

}; // namespace canlink_util
