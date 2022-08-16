/*
* Created by fidel on 8/11/2022.
**/

//#include "./controller/controller.h"

#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <vector>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wnon-pod-varargs"
struct cam_address_test
{
    std::vector<int> arrayOfAddress{ 0x1, 0x34D, 0x789, 0x3 };
    std::vector<float> arrayOfFloats { 1.4, 2, 6, 10.5 };
};


#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wformat"
int write_test(unsigned int address){
    printf("%x", address);
    printf("\n");
    return 0;
}
#pragma clang diagnostic pop

void helper_test(std::vector<int> &arrayAddress, std::vector<float>&vals){
    uintptr_t testGameAddy = 14;
    uintptr_t newGameAddy;
    for(int i = 0; i < arrayAddress.size(); i++){
        newGameAddy = testGameAddy + arrayAddress[i];
        write_test(newGameAddy);
    }
    printf("\n");
    printf("");
}

int main()
{
    /*
    Controller start;
    start.menu();
    start.controller_loop();
     */
    cam_address_test test;
    helper_test(test.arrayOfAddress, test.arrayOfFloats);
    return 0;
}

#pragma clang diagnostic pop