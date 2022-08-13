#include <iostream>
#include <windows.h>
#include <winuser.h>
#include <psapi.h>
#include <ostream>
#include <vector>

// helper function takes in handle, ptr, and pointer offsets, can be found using cheat engine P->???
// traverse the pointer offsets to "jump" from the offsets and find the dynamic address
uintptr_t findAddress(HANDLE handle, uintptr_t ptr, std::vector<unsigned int>offsets){
    uintptr_t addr = ptr;
    for (unsigned int i = 0; i < offsets.size(); ++i){
        ReadProcessMemory(handle, (BYTE*)addr, &addr, sizeof(addr), nullptr);
        addr += offsets[i];
    }
    return addr;
}

int main() {
     // Finding window handle by using the window name (not process name, so no exe)
    HWND WindowHandle = FindWindowA(NULL, "WWE 2K22");
    if (!WindowHandle) {printf("Failed to get WindowHandle"); return 1;};
    printf("Window handle \n >DEC %d \n >HEX %x \n\n", WindowHandle, WindowHandle);

    // Get Process ID from handle
    DWORD ProcessID = NULL;
    GetWindowThreadProcessId(WindowHandle,&ProcessID);
    if (ProcessID == NULL) {printf("Failed to get ProcessID from HWND"); return 1;};
    printf("Window ID \n >DEC %d \n >HEX %x \n\n", ProcessID, ProcessID);

    // Get Process Handle from Process ID
    HANDLE l_handle = OpenProcess(PROCESS_ALL_ACCESS, true, ProcessID);
    if (l_handle == NULL) {printf("Failed to open process"); return 1;};
    printf("Process handle \n >DEC %d \n >HEX %x \n\n", l_handle, l_handle);

    // get full exe path, no use in hack, no use for hack, just for debug
    // return: returns 0 on fail, len(buffer) on success
    char l_path_to_exe[1024];
    if (GetProcessImageFileNameA(l_handle, l_path_to_exe, 1024) == 0)
    { printf("Failed to get name of a process"); return 1; }
    printf("Process exe path\n >%s\n\n", l_path_to_exe);

    // Get all Modules of a process
    HMODULE hModule[4096];
    DWORD lpcbNeeded;
    EnumProcessModules(l_handle, hModule, 4096, &lpcbNeeded);
    // Total number of modules we got it calculated by
    // Number of bytes returned by EnumProcessModules / size of one HMODULE element
    int modules_count = lpcbNeeded / sizeof(HMODULE);
    printf("Number of modules found\n >%d\n\n", modules_count);

    // printing name of all modules, no use for hack, just for debug
    printf("Names of modules: \n >");
    for (int i = 0; i < modules_count; i++)
    {
        CHAR file_name[2048];
        GetModuleFileNameExA(l_handle, hModule[i], file_name, 2048);
        printf("[%s] ", file_name);
    }
    // going through all module names and looking for one we need
    // which is going to have the same name as our process exe, we need to
    // find that exe so we could have its baseaddress
    int id_of_module_in_array = -1;
    for (int i = 0; i < modules_count; i++)
    {
        CHAR file_name[2048];
        GetModuleFileNameExA(l_handle, hModule[i], file_name, 2048);
        if (std::string(file_name).find(".exe") != std::string::npos)
        {
            printf("\n\nFound EXE \n >%s\n >%x\n",file_name, hModule[i]);
            id_of_module_in_array = i;
        }
    }

    if (id_of_module_in_array == -1)
    { printf("Failed to find EXE in modules"); return 1; }

    MODULEINFO modInfo;
    if(GetModuleInformation(l_handle, hModule[id_of_module_in_array], &modInfo, sizeof(modInfo)) == 0)
    { printf("Failed to get info about module"); return 1; }
    printf("\nInformation about module\n");
    printf(" >EntryPoint\n");
    printf(" >> %x\n", modInfo.EntryPoint);
    printf(" >BaseOfDll\n");
    printf(" >> %x\n", modInfo.lpBaseOfDll);
    printf(" >SizeOfImage\n");
    printf(" >> %d\n", modInfo.SizeOfImage);

    uintptr_t cameraPtr = (uintptr_t)(modInfo.lpBaseOfDll) + 0x036ED358;
    std::vector<unsigned int> offsets = { 0x20, 0x28, 0x28, 0x18, 0x178 };
    uintptr_t pointerAddy = findAddress(l_handle, cameraPtr, offsets);
    std::cout << "zoom address = "<< std::hex << pointerAddy << "\n";
    //14252E158
    return 0;
}