//
// Created by fidel on 8/15/2022.
//
#include <iostream>
#include "./controller.h"

void Controller::menu() {
    printf("=================");
    printf("\n");
    printf("     MENU    ");
    printf("\n");
}

void Controller::camera_options() {
    printf("hello \n");
    std::cin >> choice;
}

void Controller::controller_loop()
{
    do
    {
      camera_options();
    } while (choice == 1);
}
