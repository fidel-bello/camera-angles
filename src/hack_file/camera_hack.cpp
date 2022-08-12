//
// Created by fidel on 8/11/2022.
//

#include "camera_hack.h"

camera_hack::camera_hack(const char* window_handle) {
    window_name = FindWindowA(nullptr, window_handle);
    if(!window_name) printf("Error: Window not found");
    else printf("window found");
    processID = 0;
}

camera_hack::~camera_hack() {
    CloseHandle(window_name);
}

bool camera_hack::findProcessID() {
    GetWindowThreadProcessId(window_name, &processID);
    if(processID == 0) {
        printf("\nFailed to get procID from HWND");
        return true;
    }
    printf("\nProcess handle \n >DEC %lu \n >HEX %lx \n\n", processID, processID);
}

