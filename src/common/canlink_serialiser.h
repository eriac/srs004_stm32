#pragma once

#include <vector>
#include <string>

namespace CanLinkSerialiser {

struct CanLinkSerialiser {
    char channel;
    unsigned char source_id;
    unsigned char target_id;
    unsigned char command;
    bool request;
    unsigned char data[8];
    unsigned char size;
    unsigned char extra;
    
    bool decode(std::string msg)
    {
        if(msg.empty()){
            // printf("decode fail: empty\n");
            return false;
        }
        if(msg.front() != '$'){
            // printf("decode fail: not $\n");
            return false;
        }
        int valid_size = msg.find_first_of(';');
        if(valid_size == -1){
            // printf("decode fail: not ;\n");
            return false;
        }
        msg.resize(valid_size);
        auto r = split(msg, ",");

        if(r.size() < 6){
            // printf("decode fail: less item\n");
            return false;
        }

        if(r[0]!="$CL"){
            // printf("decode fail: r[0] != $CL\n");
            return false;
        }

        if(r[1].size()!=1){
            // printf("decode fail: r[1].size() != 1\n");
            return false;
        }
        unsigned char temp_channel = r[1][0];

        int temp_source_id = std::stoi(r[2], nullptr, 16);
        if(temp_source_id < 0 || 32 <= temp_source_id){
            // printf("decode fail: nor 0<=r[2]<32\n");
            return false;
        }

        int temp_target_id = std::stoi(r[3], nullptr, 16);
        if(temp_target_id < 0 || 32 <= temp_target_id){
            // printf("decode fail: nor 0<=r[3]<32\n");
            return false;
        }

        int temp_command = std::stoi(r[4], nullptr, 16);
        if(temp_command < 0 || 32 <= temp_command){
            // printf("decode fail: nor 0<=r[4]<32\n");
            return false;
        }

        int temp_extra = std::stoi(r[5], nullptr, 16);
        if(temp_extra < 0 || 32 <= temp_extra){
            // printf("decode fail: nor 0<=r[5]<32\n");
            return false;
        }

        int temp_data_size = 0;
        unsigned char temp_data[8];
        if(r.size() >= 7){
            int data_size = r[6].size();
            if(data_size%2 != 0){
                // printf("decode fail: r[6].size() is not odd\n");
                return false;
            }
            temp_data_size = data_size/2;
            for(int i=0; i<temp_data_size; i++){
                char c_str[2]={r[6][i*2], r[6][i*2+1]};
                temp_data[i] = std::stoi(std::string(c_str), nullptr, 16);
            }
        }

        channel = temp_channel;
        source_id = temp_source_id;
        target_id = temp_target_id;
        command = temp_command;
        size = temp_data_size;
        for(int i=0; i<temp_data_size; i++){
            data[i] = temp_data[i];
        }
        return true;
    }

    std::string encode(void)
    {
        char output[40];
        int offset = snprintf(output, 40, "$CL,%c,%02X,%02X,%02X,%02X,", channel, source_id, target_id, command, extra);
        for(int i=0; i<size; i++){
            offset += snprintf(output+offset, 40-offset, "%02X", data[i]);
        }
        offset += snprintf(output+offset, 40-offset, ";");
        return std::string(output);
    }
 
    std::vector<std::string> split(std::string str, std::string separator) {
        if (separator == "") return {str};
        std::vector<std::string> result;
        std::string tstr = str + separator;
        long l = tstr.length(), sl = separator.length();
        std::string::size_type pos = 0, prev = 0;
        
        for (;pos < l && (pos = tstr.find(separator, pos)) != std::string::npos; prev = (pos += sl)) {
            result.emplace_back(tstr, prev, pos - prev);
        }
        return result;
    }
};

}; // namespace CanlinkSerialiser
