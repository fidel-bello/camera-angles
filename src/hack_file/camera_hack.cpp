#pragma clang diagnostic push
#pragma ide diagnostic ignored "ArrayIndexOutOfBounds"
#pragma clang diagnostic ignored "-Wunused-value"
#pragma ide diagnostic ignored "cppcoreguidelines-narrowing-conversions"
//
// Created by fidel on 8/11/2022.
//
#include "camera_hack.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wformat"

camera_hack::camera_hack(const char* window_handle)
{
    window_name = FindWindowA(nullptr, window_handle);
    if(!window_name) printf("Error: Window not found");
    else printf("window found");
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
    printf("\nWindow ID \n >DEC %lu \n >HEX %lx \n\n", processID, processID);
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
    printf("Process handle \n >DEC %lu \n >HEX %lx \n\n", l_handle, l_handle);
}

int camera_hack::get_modules() {
    // Get all Modules of a process
    HMODULE hModule[4096];
    DWORD lpcbNeeded;
    EnumProcessModules(l_handle, hModule, 4096, &lpcbNeeded);
    // Total number of modules we got it calculated by
    // Number of bytes returned by EnumProcessModules / size of one HMODULE element
    int modulesCount = lpcbNeeded / sizeof(HMODULE);
    printf("Number of modules found \n > %d\n\n", modulesCount);
    // printing name of all modules, no use for hack, just for debug
    printf("Names of modules: \n >");
    printf("\n");
    CHAR file_name[2048];
    for (int i = 0; i < modulesCount; i++)
    {
        file_name[2048];
        GetModuleFileNameExA(l_handle, hModule[i], file_name, 2048);
        printf("[%s] ", file_name);
    }
    int id_of_module_in_array = -1;
    for (int i = 0; i < modulesCount; i++)
    {
        file_name[2048];
        GetModuleFileNameExA(l_handle, hModule[i], file_name, 2048);
        if (std::string(file_name).find("WWE2K19_x64.exe") != std::string::npos)
        {
            printf("\n\nFound EXE \n >%s\n >%x\n",file_name, hModule[i]);
            id_of_module_in_array = i;
        }
    }

    if (id_of_module_in_array == -1)
    {
        printf("Failed to find EXE in modules\n"); return 1;
    }
    if(GetModuleInformation(l_handle, hModule[id_of_module_in_array], &modInfo, sizeof(modInfo)) == 0)
    {
        printf("Failed to get info about module\n");
        return 1;
    }

    printf("\nInformation about module\n");
    printf(" >EntryPoint\n");
    printf(" >> %x\n", modInfo.EntryPoint);
    printf(" >BaseOfDll\n");
    printf(" >> %x\n", modInfo.lpBaseOfDll);
    printf(" >SizeOfImage\n");
    printf(" >> %d\n", modInfo.SizeOfImage);

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
    std::cout << "The new value is " << (float)newValue << "\n";
}

int camera_hack::hctpCamera()
{
    uintptr_t cameraAdr = (uintptr_t)(modInfo.lpBaseOfDll) + 0x0252E158;
    float newRotation = 0.1;
    WriteProcessMemory(l_handle, (LPVOID)cameraAdr, &newRotation, sizeof(newRotation), nullptr);
    return 0;
}


#pragma clang diagnostic pop
#pragma clang diagnostic pop