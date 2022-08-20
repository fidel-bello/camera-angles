//
// Created by fidel on 8/11/2022.
//
#include "camera_hack.h"
#include "./helpers/helpers.cpp"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "ConstantFunctionResult"
#pragma clang diagnostic ignored "-Wconstant-conversion"
#pragma ide diagnostic ignored "ArrayIndexOutOfBounds"
#pragma clang diagnostic ignored "-Wunused-value"
#pragma ide diagnostic ignored "cppcoreguidelines-narrowing-conversions"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wformat"



camera_hack::camera_hack(const char* window_handle)
{
    window_name = FindWindowA(nullptr, window_handle);
    if(!window_name) printf("Error: Window not found");
    //else printf("window found");
    processID = 0;
    l_handle = nullptr;
    modInfo;
}

camera_hack::~camera_hack()
{
    CloseHandle(window_name);
}

bool camera_hack::findProcessID()
{
    GetWindowThreadProcessId(window_name, &processID);
    if(processID == 0)
    {
        printf("\nFailed to get procID from HWND\n");
        return true;
    }

   return processID;
}

bool camera_hack::open_process()
{
    l_handle = OpenProcess(PROCESS_ALL_ACCESS, true, processID);
    if(l_handle == nullptr)
    {
        GetLastError();
        printf("Error: failed to open process\n");
        return false;
    }
    return true;
}

int camera_hack::get_modules() {
    // Get all Modules of a process
    HMODULE hModule[4096];
    DWORD lpcbNeeded;
    EnumProcessModules(l_handle, hModule, 4096, &lpcbNeeded);
    // Total number of modules we got it calculated by
    // Number of bytes returned by EnumProcessModules / size of one HMODULE element
    int modulesCount = lpcbNeeded / sizeof(HMODULE);
    CHAR file_name[2048];
    for (int i = 0; i < modulesCount; i++)
    {
        file_name[2048];
        GetModuleFileNameExA(l_handle, hModule[i], file_name, 2048);
    }
    int id_of_module_in_array = -1;
    for (int i = 0; i < modulesCount; i++)
    {
        file_name[2048];
        GetModuleFileNameExA(l_handle, hModule[i], file_name, 2048);
        if (std::string(file_name).find("WWE2K19_x64.exe") != std::string::npos)
        {
            id_of_module_in_array = i;
        }
    }

    if (id_of_module_in_array == -1)
    {
        return 1;
    }
    if(GetModuleInformation(l_handle, hModule[id_of_module_in_array], &modInfo, sizeof(modInfo)) == 0)
    {
        return 1;
    }
    return -1;
}

//camera angles
int camera_hack::hctpCamera()
{
   camera_struct angle = { 1.75, 0.019, 80, 8, 9, 20, 12.5, 450, 500 };
   return set_angle(angle);
}

int camera_hack::nose_bleeds()
{
    camera_struct angle = { 1.75, 1.200000048, 25, 10, -3, 12, 12.5, 700, 700 };
    return set_angle(angle);
}

int camera_hack::default_cam()
{
    camera_struct angle = { 1.75, 1.57, 25, 10, 3, 6.5, 12.5, 300, 290 };
    return set_angle(angle);
}
int camera_hack::ring_side() {
    camera_struct angle = { 1.75, 1.001000047, 30, 12, 12, 25, 8, 350, 300};
    return set_angle(angle);
}

int camera_hack::set_angle(const camera_struct &angle) {
    uintptr_t xAxis = (uintptr_t) (modInfo.lpBaseOfDll) + 0x252E190;
    uintptr_t xRotate = (uintptr_t) (modInfo.lpBaseOfDll) + 0x252E158;
    uintptr_t yAll = (uintptr_t) (modInfo.lpBaseOfDll) + 0x14252E1C4;
    uintptr_t yOut = (uintptr_t) (modInfo.lpBaseOfDll) + 0x252E1C8;
    uintptr_t yTiltIn = (uintptr_t) (modInfo.lpBaseOfDll) + 0x252E1E4;
    uintptr_t yTiltOut = (uintptr_t) (modInfo.lpBaseOfDll) + 0x252E1E8;
    uintptr_t zAll = (uintptr_t) (modInfo.lpBaseOfDll) + 0x252E1E0;
    uintptr_t zIn = (uintptr_t) (modInfo.lpBaseOfDll) + 0x252E1A0;
    uintptr_t zOut = (uintptr_t) (modInfo.lpBaseOfDll) + 0x252E1AC;

    WriteProcessMemory(l_handle, (LPVOID) xAxis, &angle.x_axis, sizeof(float), nullptr);
    WriteProcessMemory(l_handle, (LPVOID) xRotate, &angle.x_rotation, sizeof(float), nullptr);
    WriteProcessMemory(l_handle, (LPVOID) yAll, &angle.y_all, sizeof(float), nullptr);
    WriteProcessMemory(l_handle, (LPVOID) yOut, &angle.y_out_ring, sizeof(float), nullptr);
    WriteProcessMemory(l_handle, (LPVOID) yTiltIn, &angle.y_tilt_in_ring, sizeof(float), nullptr);
    WriteProcessMemory(l_handle, (LPVOID) yTiltOut, &angle.y_tilt_out_ring, sizeof(float),
                                             nullptr);
    WriteProcessMemory(l_handle, (LPVOID) zAll, &angle.z_all, sizeof(float), nullptr);
    WriteProcessMemory(l_handle, (LPVOID) zIn, &angle.z_in_ring, sizeof(float), nullptr);
    WriteProcessMemory(l_handle, (LPVOID) zOut, &angle.z_out_ring, sizeof(float), nullptr);

    return true;
}


#pragma clang diagnostic pop
#pragma clang diagnostic pop