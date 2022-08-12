//
// Created by fidel on 8/12/2022.
//
#include "../hack_file/camera_hack.h"

void print_cameraStructs(const std::vector<unsigned int>& cameraStruct){
    for(unsigned int i : cameraStruct)
        std::cout <<  std::hex << i << " ";
    std::cout << "\n";
}