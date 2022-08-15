/*
* Created by fidel on 8/11/2022.
**/
#include "./hack_file/camera_hack.h"

int main(){
    COORDS coords;
    auto hack = *new camera_hack("WWE 2k19");
    hack.findProcessID();
    hack.open_process();
    hack.get_modules();
    hack.nop_test();
    //hack.get_memory();
    ///hack.hctpCamera(); //hctp = here comes the pain camera from older games

    //print_cameraStructs(coords.zoom);
   // print_cameraStructs(coords.rotation);
   // print_cameraStructs(coords.heightRotation);
    return 0;
}
