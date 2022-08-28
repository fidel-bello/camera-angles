//
// Created by fidel on 8/26/2022.
//

#include "controller.h"

Controller::Controller() {}

Controller::~Controller(){}

bool Controller::running() { return isRunning;}

void Controller::init()
{

    if(hack->findProcessID()!= 0)
    {
        hack->open_process();
        hack->get_modules();
        isRunning = true;
    } else {
        isRunning = false;
    }
}

void Controller::init_22()
{

    if(hack_2->findProcessID() != 0)
    {
        hack_2->open_process();
        hack_2->get_modules();
        isRunning = true;
    } else {
        isRunning = false;
    }
}


void Controller::cam_options_19()
{
    int choice;

    printf("1. HCTP");
    printf("\n");
    printf("2. Nose Bleeds");
    printf("\n");
    printf("3. Ring Side");
    printf("\n");
    printf("4. Default\n");

    std::cin >> choice;

    if(choice == 1)
    {
        hack->hctpCamera();
    } else if(choice == 2)
    {
        hack->nose_bleeds();
    } else if(choice == 3)
    {
        hack->ring_side();
    } else if(choice == 4)
    {
        hack->default_cam();
    }
}

void Controller::cam_options_22()
{
    int  choice;

    printf("1. HCTP\n");
    printf("2. Nose Bleeds\n");
    printf("3. Ring Side\n");
    printf("4. Default\n");
    printf("5. North Medium\n");

    std::cin >> choice;

    if(choice == 1)
    {
        hack_2->hctp22();
    } else if(choice == 2)
    {
        hack_2->nose_bleeds22();
    } else if(choice == 3)
    {
        hack_2->ring_side22();
    } else if(choice == 4)
    {
        hack_2->default_cam22();
    } else if(choice == 5)
    {
        hack_2->north_medium22();
    }
}


void Controller::title_options()
{
    printf("What Game?\n");
    printf("1. WWE 2K19\n");
    printf("2. WWE 2K22\n");
}

