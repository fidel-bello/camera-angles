//
// Created by fidel on 8/11/2022.
//
#include "camera_hack.h"
#include "./helpers/helpers.cpp"
#include "./constants/constants.h"


#pragma clang diagnostic push
#pragma ide diagnostic ignored "ConstantParameter"
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

int camera_hack::open_process()
{
    l_handle = OpenProcess(PROCESS_ALL_ACCESS, true, processID);
    if(l_handle == nullptr)
    {
        GetLastError();
        printf("Error: failed to open process\n");
        return false;
    }
    printf("Opened process");
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
        if (std::string(file_name).find("WWE2K19_x64.exe") != std::string::npos  || std::string(file_name).find("WWE2K22_x64.exe") != std::string::npos)
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

/**
 *
 * @param angle takes in address from the camera struct
 * @return r
 */

std::vector<unsigned int> camera_hack::get_offsetsHelper(std::vector<unsigned int>address, uintptr_t ptr, float val, float newVal)
{
    uintptr_t game = (uintptr_t)(modInfo.lpBaseOfDll);
    uintptr_t xRotate_func = game + 0x0793414;
    uintptr_t zAxis_func = game + 0x07964FE;
    uintptr_t yAxis_func = game + 0x0793C7A;
    uintptr_t yAxis1_func = game + 0x7964A0;

    int size_of_z_function = 6;
    int size_of_x_function = 8;


    for(unsigned int i = 0; i < address.size(); ++i)
    {
        ReadProcessMemory(l_handle, (LPVOID) ptr, &ptr, sizeof(ptr), nullptr);
        ptr += address[i];
    }

    char* free_xAxis = dynamic_nop(size_of_x_function, NOP);
    WriteProcessMemory(l_handle, (LPVOID)xRotate_func, free_xAxis, size_of_x_function, nullptr);

    char* free_zAxis = dynamic_nop(size_of_z_function, NOP);
    WriteProcessMemory(l_handle, (LPVOID)zAxis_func, free_zAxis, size_of_z_function, nullptr);

    char* free_yAxis = dynamic_nop(size_of_x_function, NOP);
    WriteProcessMemory(l_handle, (LPVOID)yAxis_func, free_yAxis, size_of_x_function, nullptr);

    char* free_yAxisOne  = dynamic_nop(size_of_x_function, NOP);
    WriteProcessMemory(l_handle, (LPVOID)yAxis1_func, free_yAxisOne, size_of_x_function, nullptr);

    ReadProcessMemory(l_handle, (LPVOID) ptr, &val, sizeof(float), nullptr);

    WriteProcessMemory(l_handle, (LPVOID)ptr, &newVal, sizeof(float), nullptr);

    return address;
}

void camera_hack::nose_bleeds22() {

    uintptr_t game =(uintptr_t) modInfo.lpBaseOfDll;
    uintptr_t xRotate_address = (uintptr_t)game + 0x036ED358;
    uintptr_t zAxis_address = (uintptr_t)game + 0x036ED358;
    uintptr_t yTilt_address = (uintptr_t)game + 0x036ED368;
    uintptr_t y_address = (uintptr_t) game + 0x036ED368;

    camera_addresses_22 address;

    float default_x_rotate;
    float default_y_tilt;
    float default_z;

    float new_x_rotate = 1;
    float new_y_tilt = -0.200000003;
    float new_z = 2500;
    float default_y;
    float new_y = -300;

    get_offsetsHelper(address.xRotate, xRotate_address, default_x_rotate, new_x_rotate);
    get_offsetsHelper(address.zAxis, zAxis_address, default_z, new_z);
    get_offsetsHelper(address.yTilt, yTilt_address,default_y_tilt, new_y_tilt);
    get_offsetsHelper(address.y_axis, y_address, default_y, new_y);

}

void camera_hack::default_cam22()
{
    uintptr_t game = (uintptr_t)(modInfo.lpBaseOfDll);

    uintptr_t xRotate_func = game + 0x0793414;
    uintptr_t zAxis_func = game + 0x07964FE;
    uintptr_t yAxis_func = game + 0x0793C7A;
    uintptr_t yAxis1_func = game + 0x07964A0;

        unsigned char xRotateArray[] =  {X_ROTATE_FUNC };
        unsigned char* newXRotateArr = revert_address(xRotateArray, 8, l_handle, (LPVOID)xRotate_func);
        delete[] newXRotateArr;

        unsigned char zArray[] = { Z_FUNC };
        unsigned char *newZArray = revert_address(zArray, 6, l_handle, (LPVOID)zAxis_func);
        delete[] newZArray;

        unsigned char yArray[] = { Y_Tilt_FUNC };
        unsigned char *newYArray = revert_address(yArray, 8, l_handle, (LPVOID)yAxis_func);
        delete[] newYArray;

        unsigned char yOneArray[] = { Y_FUNC };
        unsigned char* newYOneArray = revert_address(yOneArray, 8, l_handle, (LPVOID)yAxis1_func);
        delete[] newYOneArray;
}

void camera_hack::hctp22() {

    uintptr_t game =(uintptr_t) modInfo.lpBaseOfDll;
    uintptr_t xRotate_address = (uintptr_t)game + 0x036ED358;
    uintptr_t zAxis_address = (uintptr_t)game + 0x036ED358;
    uintptr_t yTilt_address = (uintptr_t)game + 0x036ED368;

    camera_addresses_22 address;

    float default_x_rotate;
    float default_y_tilt;
    float default_z;

    float new_x_rotate = 0;
    float new_y_tilt = -0.1000000015;
    float new_z = 1050;

    get_offsetsHelper(address.xRotate, xRotate_address, default_x_rotate, new_x_rotate);
    get_offsetsHelper(address.zAxis, zAxis_address, default_z, new_z);
    get_offsetsHelper(address.yTilt, yTilt_address,default_y_tilt, new_y_tilt);

}

void camera_hack::ring_side22() {

    uintptr_t game =(uintptr_t) modInfo.lpBaseOfDll;
    uintptr_t xRotate_address = (uintptr_t)game + 0x036ED358;
    uintptr_t zAxis_address = (uintptr_t)game + 0x036ED358;
    uintptr_t yTilt_address = (uintptr_t)game + 0x036ED368;
    uintptr_t y_address = (uintptr_t) game + 0x036ED368;

    camera_addresses_22 address;

    float default_x_rotate;
    float default_y_tilt;
    float default_z;
    float default_y;

    float new_x_rotate = 1.200000048;
    float new_y_tilt = -0.001000000047;
    float new_z = 1300;
    float new_y = -300;

    get_offsetsHelper(address.xRotate, xRotate_address, default_x_rotate, new_x_rotate);
    get_offsetsHelper(address.zAxis, zAxis_address, default_z, new_z);
    get_offsetsHelper(address.yTilt, yTilt_address,default_y_tilt, new_y_tilt);
    get_offsetsHelper(address.y_axis, y_address, default_y, new_y);
}


#pragma clang diagnostic pop
#pragma clang diagnostic pop