#include <stdio.h>
#include <iostream>
#include "../src/common/canlink_util.h"

int main(void){
    printf("start\n");
    // canlink_util::PowerStatus source, cor;

    // canlink_util::BoardInfo source, cor;
    // source.name[0]='A';
    // source.name[1]='B';
    // source.revision = 56156;
    // source.id = 0xABCDEF12;

    // auto data = source.getData();
    // printf("size: [%u]", (unsigned int)data.size());
    // for(auto item : data){
    //     printf(" %02x", item);
    // }
    // printf(",e:%u\n", source.getExtra());

    // cor.decode(source.getData(), source.getExtra());
    // printf("%c %c\n", cor.name[0],cor.name[1]);
    // printf("%u\n", cor.revision);
    // printf("%x\n", cor.id);

    canlink_util::MotorOutput source, cor;
    source.mot0 = 30;
    source.mot1 = 1.234;
    source.mot2 = 0;
    source.mot3 = -15.67;
    printf("%s\n", source.getStr().c_str());

    auto data = source.getData();
    printf("size: [%u]", (unsigned int)data.size());
    for(auto item : data){
        printf(" %02x", item);
    }
    printf(", e:%u\n", source.getExtra());

    cor.decode(source.getData(), source.getExtra());
    printf("%s\n", cor.getStr().c_str());
};