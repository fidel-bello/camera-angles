//
// Created by fidel on 8/11/2022.
//
#include "camera_hack.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wformat"

camera_hack::camera_hack(const char* window_handle) {
    window_name = FindWindowA(nullptr, window_handle);
    if(!window_name) printf("Error: Window not found");
    else printf("window found");
    processID = 0;
    l_handle = nullptr;
}

camera_hack::~camera_hack() {
    CloseHandle(window_name);
}

bool camera_hack::findProcessID() {
    GetWindowThreadProcessId(window_name, &processID);
    if(processID == 0) {
        printf("\nFailed to get procID from HWND\n");
        return true;
    }
    printf("\nWindow ID \n >DEC %lu \n >HEX %lx \n\n", processID, processID);
}

int camera_hack::open_process() {
    l_handle = OpenProcess(PROCESS_ALL_ACCESS, true, processID);
    if(l_handle == nullptr) {
        GetLastError();
        printf("Error: failed to open process\n");
        return -1;
    }
    printf("Process handle \n >DEC %lu \n >HEX %lx \n\n", l_handle, l_handle);
}

#pragma clang diagnostic pop