/*
 * Created by fidel on 8/11/2022.
 *
 * */
#include "./hack_file/camera_hack.h"

//for testing
void print_cameraStructs(const std::vector<unsigned int>& cameraStruct){
    for(unsigned int i : cameraStruct)
        std::cout <<  std::hex << i << " ";
    std::cout << "\n";
}

int main(){
    COORDS coords;
    auto hack = *new camera_hack("game window here");
    hack.findProcessID();
    print_cameraStructs(coords.zoom);
    print_cameraStructs(coords.rotation);
    print_cameraStructs(coords.heightRotation);
    return 0;
}