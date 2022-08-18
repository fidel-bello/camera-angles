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


    HWND window_name{};
    DWORD processID{};
    HANDLE l_handle{};
    MODULEINFO modInfo{};

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