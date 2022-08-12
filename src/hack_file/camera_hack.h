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

/*
 * struct COORDS. these are the offsets for the camera values.
 * There are more in the memory address but need to figure out how their functions work
 * these are passed in a function that automatically defaults them back to their original values
 * to make the hack work, I had to disable the functions with an assembler nop
 * */

struct COORDS {
    std::vector<unsigned int>heightRotation = { 0x18, 0x0, 0x28, 0x18, 0x164 }; //address = baseExe + 0x036ED368
    std::vector<unsigned int>zoom = { 0x20, 0x28, 0x28, 0x18, 0x178 }; // address = baseExe + 0x036ED358
    std::vector<unsigned int>rotation = { 0x20, 0x38, 0x30, 0x18, 0x158 }; //address = baseExe + 0x036ED358
};

class camera_hack {
private:
    HWND window_name{};
    DWORD processID{};
public:
    explicit camera_hack(const char *window_handle);
    ~camera_hack();
    bool findProcessID();
};


#endif //CAMERA_HACK_H
