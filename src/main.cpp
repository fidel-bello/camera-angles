/*
 * Created by fidel on 8/11/2022.
 * */

#include "./hack_file/camera_hack.h"

int main(){
    auto hack = *new camera_hack("game window here");
    hack.findProcessID();
    return 0;
}