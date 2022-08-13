/*
* Created by fidel on 8/11/2022.
**/

#include "./hack_file/camera_hack.h"
#include "./helpers/helper.cpp"

int main(){
    COORDS coords;
    auto hack = *new camera_hack("WWE 2k19");
    hack.findProcessID();
    hack.open_process();
    hack.get_modules();
    hack.get_memory();

    print_cameraStructs(coords.zoom);
    print_cameraStructs(coords.rotation);
    print_cameraStructs(coords.heightRotation);
    return 0;
}
