//
// Created by fidel on 8/11/2022.
//

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wconstant-conversion"
#ifndef CAMERA_HACK_H
#define CAMERA_HACK_H

#include <windows.h>
#include <windows.h>
#include <winuser.h>
#include <psapi.h>
#include <ostream>
#include <iostream>
#include <vector>

#include "../constants/wwe_19/wwe_19_constants.h"


/*
 * struct COORDS. these are the offsets for the camera values.
 * There are more in the memory address but need to figure out how their functions work
 * these are passed in a function that automatically defaults them back to their original values
 * to make the hack work, I had to disable the functions with an assembler nop
 * */
/*
struct COORDS { for future use WWE 2K22
    std::vector<unsigned int>heightRotation = { 0x18, 0x0, 0x28, 0x18, 0x164 }; //address = baseExe + 0x036ED368
    std::vector<unsigned int>zoom = { 0x20, 0x28, 0x28, 0x18, 0x178 }; // address = baseExe + 0x036ED358
    std::vector<unsigned int>rotation = { 0x20, 0x38, 0x30, 0x18, 0x158 }; //address = baseExe + 0x036ED358
};
*/

class camera_hack {
private:
    struct camera_struct
    {
        float zoom_out_ring;
        float zoom_in_ring;
        float zoom_all;
        float y_tilt;
        float y_tilt_2;
        float x_rotation;
    };

    HWND window_name{};
    DWORD processID{};
    HANDLE l_handle{};
    MODULEINFO modInfo{};
    uintptr_t baseAddr;
    uintptr_t zoomInRing;
    uintptr_t zoomOutRing;
    uintptr_t zoomAll;
    uintptr_t yTiltIn;
    uintptr_t yTiltOut;
    uintptr_t xRotate;

    uint16_t zoom_in_ring;
    uint16_t zoom_out_ring;
    uint16_t zoom_all;
    uint16_t y_tilt_in;
    uint16_t y_tilt_out;
    uint16_t x_rotate;

    float default_zoom_out_ring;
    float default_zoom_in_ring;
    float default_zoom_all;
    float default_y_tilt_in;
    float default_y_tilt_out;
    float default_x_rotate;

    int set_angle(const camera_struct &angle);
public:
    explicit camera_hack(const char *window_handle);
    ~camera_hack();
    bool findProcessID();
    int open_process();
    int get_modules();
    int get_memory();

    void nop_test() const;
    void revert_test();

    //camera angles for mod menu of choices
    int hctpCamera();
    int nose_bleeds();
    int default_cam();
};


#endif //CAMERA_HACK_H

#pragma clang diagnostic pop