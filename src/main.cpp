/*
* Created by fidel on 8/11/2022.
**/
#include "./mod_file/controller/controller.h"

Controller *control = nullptr;
int choice;




int main()
{
    control = new Controller();
    control->title_options();
    std::cin >> choice;

    if(choice == 1)
    {
        control->init();
    } else if(choice == 2)
    {
        control->init_22();
    }

    while (control->running())
    {
        if(choice == 1)
        {
            control->cam_options_19();
        } else if(choice == 2)
        {
            control->cam_options_22();
        }

    }
    return 0;
}

