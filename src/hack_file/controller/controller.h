//
// Created by fidel on 8/15/2022.
//
#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"

#ifndef NEW_CAMERA_HACK_CONTROLLER_H
#define NEW_CAMERA_HACK_CONTROLLER_H

#include "../camera_hack.h"

struct Controller
{
    int choice;
    void camera_options();
    void choices();

    void controller_loop();
    void menu();
};

void Controller::menu()
{
    printf("\n");
    printf("MENU              ");
    printf("\n");
}

// this will have list of manual camera options from myself;
void Controller::camera_options() {
    printf("========================================================");
    printf("\n");
    printf("1. HCTP Camera");
    printf("\n");
    printf("2. Nose Bleeds Camera");
    printf("\n");
    printf("3. Ring Side Camera");
    printf("\n");
    printf("4. Default Camera");
    printf("\n\n");
    camera_hack hack("WWE 2K19");
    hack.findProcessID();
    hack.open_process();
    hack.get_modules();
    std::cin >> choice;

    if (choice == 1) {
        hack.hctpCamera();
    } else if (choice == 2) {
        hack.nose_bleeds();
    } else if (choice == 3){
        hack.ring_side();
    }else if (choice == 4) {
        hack.default_cam();
    }
}

void Controller::controller_loop()
{
    do
    {
        choices();
    } while (true);
}

void Controller::choices() {
    printf("1. Camera Options -> press 1 for camera options");
    printf("\n");
    printf("2. More Options Coming Soon");
    printf("\n");

    std::cin >> choice;
    if(choice == 1) {
        do {
            camera_options();
        } while (true);
    }
}

#endif //NEW_CAMERA_HACK_CONTROLLER_H

#pragma clang diagnostic pop