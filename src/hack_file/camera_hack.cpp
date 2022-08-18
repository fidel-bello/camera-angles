//
// Created by fidel on 8/11/2022.
//

#include <algorithm>

#include <string>
#include "camera_hack.h"
#include "./helpers/helpers.cpp"
#include "./constants/constants.h"

#pragma clang diagnostic push
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
   // printf("\nWindow ID \n >DEC %lu \n >HEX %lx \n\n", processID, processID);
}

int camera_hack::open_process()
{
    l_handle = OpenProcess(PROCESS_ALL_ACCESS, true, processID);
    if(l_handle == nullptr)
    {
        GetLastError();
        printf("Error: failed to open process\n");
        return -1;
    }
    //printf("Process handle \n >DEC %lu \n >HEX %lx \n\n", l_handle, l_handle);
}

int camera_hack::get_modules() {
    // Get all Modules of a process
    HMODULE hModule[4096];
    DWORD lpcbNeeded;
    EnumProcessModules(l_handle, hModule, 4096, &lpcbNeeded);
    // Total number of modules we got it calculated by
    // Number of bytes returned by EnumProcessModules / size of one HMODULE element
    int modulesCount = lpcbNeeded / sizeof(HMODULE);
    //printf("Number of modules found \n > %d\n\n", modulesCount);
    // printing name of all modules, no use for hack, just for debug
    //printf("Names of modules: \n >");
    //printf("\n");
    CHAR file_name[2048];
    for (int i = 0; i < modulesCount; i++)
    {
        file_name[2048];
        GetModuleFileNameExA(l_handle, hModule[i], file_name, 2048);
        //printf("[%s] ", file_name);
    }
    int id_of_module_in_array = -1;
    for (int i = 0; i < modulesCount; i++)
    {
        file_name[2048];
        GetModuleFileNameExA(l_handle, hModule[i], file_name, 2048);
        if (std::string(file_name).find("WWE2K19_x64.exe") != std::string::npos)
        {
            //printf("\n\nFound EXE \n >%s\n >%x\n",file_name, hModule[i]);
            id_of_module_in_array = i;
        }
    }

    if (id_of_module_in_array == -1)
    {
        //printf("Failed to find EXE in modules\n");
        return 1;
    }
    if(GetModuleInformation(l_handle, hModule[id_of_module_in_array], &modInfo, sizeof(modInfo)) == 0)
    {
        //printf("Failed to get info about module\n");
        return 1;
    }
/*
    printf("\nInformation about module\n");
    printf(" >EntryPoint\n");
    printf(" >> %x\n", modInfo.EntryPoint);
    printf(" >BaseOfDll\n");
    printf(" >> %x\n", modInfo.lpBaseOfDll);
    printf(" >SizeOfImage\n");
    printf(" >> %d\n", modInfo.SizeOfImage);
*/

    return -1;
}

int camera_hack::get_memory()
{
    uintptr_t cameraAdr = (uintptr_t)(modInfo.lpBaseOfDll) + 0x252E190;
    float anglePtr;
    ReadProcessMemory(l_handle, (LPVOID)cameraAdr, &anglePtr, sizeof(float), nullptr);
    std::cout << "value = " << (float)anglePtr << "\n";
    float newValue = 5;
    WriteProcessMemory(l_handle, (LPVOID)cameraAdr, &newValue, sizeof(newValue),nullptr);
    ReadProcessMemory(l_handle, (LPVOID)cameraAdr, &newValue, sizeof(newValue), nullptr);
}

/**
 * test working
 * */
void camera_hack::nop_test() const
{
    int size = 4; // size of array
    unsigned int funcAddress = 0x36513B5; //address of the function im testing
    uintptr_t addressToReplace = (uintptr_t)(modInfo.lpBaseOfDll) + funcAddress; // base address + function address
    char* newArray = dynamic_nop(size, NOP);
    WriteProcessMemory(l_handle, (LPVOID)addressToReplace, newArray, size, nullptr); //pushes newArray to the process
    delete [] newArray;
}

void camera_hack::revert_test()
{
    int size = 4;
    unsigned int funcAddress = 0x36513B5;
    uintptr_t addressToReplace = (uintptr_t)(modInfo.lpBaseOfDll) + funcAddress;
    unsigned char array[] = { DEFAULT_TEST };
    unsigned char* newArr = revert_address(array, size, l_handle, (LPVOID)addressToReplace);
    if(!l_handle || !addressToReplace || newArr == 0)
    {
        printf("Error: not Successful");
        printf("\n");
    }
    delete[] newArr;
}

//camera angles
int camera_hack::hctpCamera()
{
    uintptr_t cameraAdr = (uintptr_t)(modInfo.lpBaseOfDll) + 0x0252E158;
    float newRotation = 0.1;
    WriteProcessMemory(l_handle, (LPVOID)cameraAdr, &newRotation, sizeof(newRotation), nullptr);
    return 0;
}

int camera_hack::nose_bleeds() {

    camera_struct angle = { 500, 500, 20.5, -3, 12, 1.200000048 };
    return set_angle(angle);
}

int camera_hack::default_cam()
{
    camera_struct angle = { 1.75, 1.57, 25, 10, 3, 6.5, 12.5, 300, 290 };

    set_angle(angle);

}


int camera_hack::set_angle(const camera_struct &angle)
{
    uintptr_t xAxis = (uintptr_t)(modInfo.lpBaseOfDll) + 0x252E190;
    uintptr_t xRotate = (uintptr_t)(modInfo.lpBaseOfDll) + 0x252E158;
    uintptr_t yAll = (uintptr_t)(modInfo.lpBaseOfDll) + 0x14252E1C4;
    uintptr_t yOut = (uintptr_t)(modInfo.lpBaseOfDll) + 0x252E1C8;
    uintptr_t yTiltIn = (uintptr_t)(modInfo.lpBaseOfDll) + 0x252E1E4;
    uintptr_t yTiltOut = (uintptr_t)(modInfo.lpBaseOfDll) + 0x252E1E8;
    uintptr_t zAll = (uintptr_t)(modInfo.lpBaseOfDll) + 0x252E1E0;
    uintptr_t zIn = (uintptr_t)(modInfo.lpBaseOfDll) + 0x252E1A0;
    uintptr_t zOut = (uintptr_t)(modInfo.lpBaseOfDll) + 0x252E1AC;



    WriteProcessMemory(l_handle, (LPVOID)xAxis, &angle.x_axis, sizeof(float), nullptr);
    WriteProcessMemory(l_handle, (LPVOID)xRotate, &angle.x_rotation, sizeof(float), nullptr);
    WriteProcessMemory(l_handle, (LPVOID)yAll, &angle.y_all, sizeof(float), nullptr);
    WriteProcessMemory(l_handle, (LPVOID)yOut, &angle.y_out_ring, sizeof(float), nullptr);
    WriteProcessMemory(l_handle, (LPVOID)yTiltIn, &angle.y_tilt_in_ring, sizeof(float), nullptr);
    WriteProcessMemory(l_handle, (LPVOID)yTiltOut, &angle.y_tilt_out_ring, sizeof(float), nullptr);
    WriteProcessMemory(l_handle, (LPVOID)zAll, &angle.z_all, sizeof(float), nullptr);
    WriteProcessMemory(l_handle, (LPVOID)zIn, &angle.z_in_ring, sizeof(float), nullptr);
    WriteProcessMemory(l_handle, (LPVOID)zOut, &angle.z_out_ring, sizeof(float), nullptr);
}


#pragma clang diagnostic pop
#pragma clang diagnostic pop