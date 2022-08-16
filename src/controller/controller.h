//
// Created by fidel on 8/15/2022.
//
#ifndef NEW_CAMERA_HACK_CONTROLLER_H
#define NEW_CAMERA_HACK_CONTROLLER_H

#include "../hack_file/camera_hack.h"

struct Controller
{
    int choice;
    void camera_options();
    void choices();
    void controller_loop();
    void stop();
    void menu();
};

#endif //NEW_CAMERA_HACK_CONTROLLER_H
