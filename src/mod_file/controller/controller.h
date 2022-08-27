//
// Created by fidel on 8/15/2022.
//

#ifndef NEW_CAMERA_HACK_CONTROLLER_H
#define NEW_CAMERA_HACK_CONTROLLER_H

#include "../cam_mod/camera_hack.h"

class Controller
{
private:
    bool isRunning;

    camera_hack *hack = new camera_hack("WWE 2K19");
    camera_hack *hack_2 = new camera_hack("WWE 2K22");

public:
    Controller();
    ~Controller();
    void init();
    void init_22();
    void title_options();
    void cam_options_19();
    void cam_options_22();
    bool running();
};

#endif //NEW_CAMERA_HACK_CONTROLLER_H
