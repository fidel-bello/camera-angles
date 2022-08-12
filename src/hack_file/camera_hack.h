//
// Created by fidel on 8/11/2022.
//

#ifndef CAMERA_HACK_H
#define CAMERA_HACK_H

#include <windows.h>
#include <windows.h>
#include <winuser.h>
#include <psapi.h>
#include <ostream>
#include <iostream>
#include <vector>

class camera_hack {
private:
    HWND window_name{};
    DWORD processID{};
public:
    explicit camera_hack(const char *window_handle);
    bool findProcessID();
    ~camera_hack();

};


#endif //CAMERA_HACK_H
