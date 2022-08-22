/*
* Created by fidel on 8/11/2022.
**/
#include "./hack_file/controller/controller.h"


int main()
{
   camera_hack hack("WWE 2K22");
    hack.findProcessID();
    hack.open_process();
    hack.get_modules();
    hack.hctp();
    hack.default_cam22();
    return 0;
}
