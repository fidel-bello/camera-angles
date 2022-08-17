//
// Created by fidel on 8/15/2022.
//
#include "./controller.h"
#include "../camera_hack.h"

void Controller::menu()
{
    printf("=======================================================");
    printf("\n");
    printf("                     MENU    ");
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
    } else{

        stop();
    }

}

void Controller::controller_loop()
{
    do
    {
        choices();
    } while (choice == 1 || choice == 2);
}

void Controller::choices() {
    printf("1. Camera Options");
    printf("\n");
    printf("2. Free Camera"); //not done
    printf("\n");
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
