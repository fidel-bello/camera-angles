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
    void controller_loop();
    void menu();
    void choose_game();
    void camera_options_19();
    void camera_options_22();
};

void Controller::menu()
{
    printf("\n");
    printf("MENU              ");
    printf("\n");
}

// this will have list of manual camera options from myself;
void Controller::camera_options_19() {
    printf("========================================================");
    printf("\n");
    printf("1. HCTP");
    printf("\n");
    printf("2. Nose Bleed");
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

void Controller::camera_options_22() {
    printf("1. HCTP");
    printf("\n");
    printf("2. Nose Bleeds");
    printf("\n");
    printf("3. Ring Side");
    printf("\n");
    printf("4. Default\n");
    camera_hack hack("WWE 2K22");
    hack.findProcessID();
    hack.open_process();
    hack.get_modules();
    std::cin >> choice;

    if(choice == 1){
        hack.hctp22();
    } else if(choice == 2){
        hack.nose_bleeds22();
    } else if(choice == 3){
        hack.ring_side22();
    } else if(choice == 4){
        hack.default_cam22();
    }
}

void Controller::controller_loop()
{
    do
    {
        choose_game();
    } while (true);
}


void Controller::choose_game() {
    printf("Which game are you playing?\n");
    printf("1. 2K19");
    printf("\n");
    printf("2. 2K22");
    printf("\n");
    std::cin >> choice;

    if(choice == 1){
        do {
            camera_options_19();
        } while (true);
    } else if(choice == 2){
        do {
            camera_options_22();
        } while (true);
    }
}

#endif //NEW_CAMERA_HACK_CONTROLLER_H

#pragma clang diagnostic pop