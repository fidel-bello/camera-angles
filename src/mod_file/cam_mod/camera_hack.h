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
#include <array>


/*
 * struct COORDS. these are the offsets for the camera values.
 * There are more in the memory address but need to figure out how their functions work
 * these are passed in a function that automatically defaults them back to their original values
 * to make the hack work, I had to disable the functions with an assembler nop
 * */

class camera_hack {
private:
    HWND window_name{};
    DWORD processID{};
    HANDLE l_handle{};
    MODULEINFO modInfo{};
    bool isInitialized;

    struct camera_struct
    {
        float x_axis;//default is 1.75 -> 0x252E190
        float x_rotation;//default is 1.57 -> 0x252E158
        float y_all;//default 25 -> 0x14252E1C4
        float y_out_ring;//default 10 -> 0x252E1C8
        float y_tilt_in_ring;//default 3 -> 0x252E1E4
        float y_tilt_out_ring;//default 6.5 -> 0x252E1E8
        float z_all;//default 12.5 -> 0x252E1E0
        float z_in_ring;//default 300 -> 0x252E1A0
        float z_out_ring;//default 290 -> 0x252E1AC
    };

    struct camera_addresses_22
    {
        std::vector<unsigned int> xRotate = { 0x20, 0x38, 0x30, 0x18, 0x158 };
        std::vector<unsigned int> yTilt = { 0x18, 0x0, 0x28, 0x18, 0x164 };
        std::vector<unsigned int> zAxis = { 0x20, 0x28, 0x28, 0x18, 0x178 };
        std::vector<unsigned int>y_axis = { 0x18, 0x0, 0x28, 0x18, 0x1314 };
    };

    struct camera_struct_22
    {
        float new_x_rotate;
        float new_y_tilt;
        float new_z;
        float new_y;
    };

    struct camera_struct_noY
    {
        float new_x_rotate;
        float new_y_tilt;
        float new_z;
    };

    /**
     * @param angle takes in angle from camera_struct_22
     * sets angle with a static feel. the camera will disable movement from y axis and just stays
     */
    void set_angle_no_follow(const camera_struct_22 &angle);

    /**
     *
     * @param angle takes in angle from camera_struct_noY
     * Does not take in y axis values
     * camera will not be static from the y axis and follow the player
     */
    void set_angle_follow(const camera_struct_noY &angle);

    /**
     * 2k19 only
     * @param angle takes in angles of customized floats from the camera_struct
     * @return returns the angles value that is not 0
     */
    int set_angle(const camera_struct &angle);

    /**
     * for pointers with offsets
     * @param address takes in vector of offsets
     * @param ptr takes in in the pointer address
     * @param newVal takes in custom float
     * @return  the lowest offset of the pointer
     */

    std::vector<unsigned int> get_offsetsHelper(std::vector<unsigned int> address, uintptr_t ptr, float newVal);

public:
    /**
     * constructor for class
     * @param window_handle takes in the name of window
     */
    explicit camera_hack(const char *window_handle);
    ~camera_hack();
    bool findProcessID();
    int open_process();
    int get_modules();

//camera angles for mod menu of choices #2k19
    void hctpCamera();
    void nose_bleeds();
    void ring_side();
    void default_cam();

//# 2k22
    void nose_bleeds22();
    void default_cam22();
    void hctp22();
    void ring_side22();
    void north_medium22();
    void north_tv22();
    void east_tv22();
    void south_tv22();
    void west_tv22();
    void k_1922();

};


#endif //CAMERA_HACK_H