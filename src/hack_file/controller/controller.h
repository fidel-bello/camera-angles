//
// Created by fidel on 8/15/2022.
//
#ifndef NEW_CAMERA_HACK_CONTROLLER_H
#define NEW_CAMERA_HACK_CONTROLLER_H

#include "../camera_hack.h"

struct Controller
{
    int choice;
    void camera_options();
    void choices();
    void controller_loop();
    void stop();
    void menu();
};

void Controller::menu()
{
    printf("=======================================================");
    printf("\n");
    printf("                     MENU              ");
    printf("\n");
    printf("=======================================================");
    printf("\n");
    printf("\n");
    printf("========================================================");
    printf("\n");
}

// this will have list of manual camera options from myself;
void Controller::camera_options()
{
    printf("========================================================");
    printf("\n");
    printf("1. HCTP camera angle");
    printf("\n");
    printf("2. Nose Bleeds camera angle");
    printf("\n");
    printf("3. Default Camera");
    printf("\n\n");
    camera_hack hack("WWE 2K19");
    hack.findProcessID();
    hack.open_process();
    hack.get_modules();
    std::cin >> choice;

    if(choice == 1){
        hack.hctpCamera();
    } else if(choice == 2){
        hack.nose_bleeds();
    } else if(choice == 3){
        hack.default_cam();
    } else{
        stop();
    }

}

void Controller::controller_loop()
{
    do
    {
        choices();
    } while (choice == 1 || choice == 2 || choice == 3);
}

void Controller::choices() {
    printf("1. Camera Options");
    printf("\n");
    printf("2. Free Camera"); //not done
    printf("\n");

    std::cin >> choice;
    if(choice == 1) {
        do {
            camera_options();
        } while (choice == 1 || choice == 2);
    } else {
        stop();
    }
}

void Controller::stop() {
    exit(1);
}


#endif //NEW_CAMERA_HACK_CONTROLLER_H
