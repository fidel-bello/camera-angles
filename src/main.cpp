/*
* Created by fidel on 8/11/2022.
**/
#include "./hack_file/camera_hack.h"


int main()
{
    camera_hack hack("WWE 2K19");
    hack.findProcessID();
    hack.open_process();
    hack.get_modules();
    //hack.hctpCamera();
    hack.nose_bleeds();
    //Controller start;
    //start.menu();
    //start.controller_loop();
    return 0;
}