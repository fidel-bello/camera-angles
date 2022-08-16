//
// Created by fidel on 8/15/2022.
//
#include <iostream>
#include "./controller.h"

void Controller::menu()
{
    printf("=================");
    printf("\n");
    printf("     MENU    ");
    printf("\n");
    printf("================");
    printf("\n");
}

// this will have list of manual camera options from myself;
void Controller::camera_options()
{
    printf("yoooo \n");
}

void Controller::controller_loop()
{
    do
    {
        choices();
    } while (choice == 1);
}

void Controller::choices() {
    printf("press 1 for camera options or 2 for free camera");
    printf("\n");
    std::cin >> choice;
    if(choice == 1){
        camera_options();
    } else{
        exit(1);
    }
}
