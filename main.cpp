#include <iostream>
#include <windows.h>
#include <winuser.h>
#include <psapi.h>
#include <ostream>

int main() {

    HWND WindowHandle = FindWindowA(NULL, "WWE 2K22");
    if(!WindowHandle) std::cout << "not successful\n";
    DWORD PID;
    GetWindowThreadProcessId(WindowHandle, &PID);
    std::cout << PID << "\n";
    PVOID hProcess = OpenProcess(PROCESS_VM_READ | PROCESS_QUERY_INFORMATION | PROCESS_VM_WRITE, 0, PID);
    HMODULE hMods[1024];
    DWORD cbNeeded;
    int numOfModules  = 0;

    if (EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbNeeded))
    {
        numOfModules = cbNeeded / sizeof(HMODULE);
        //return number of modules by dividing size of array by element size
        std::cout  << cbNeeded / sizeof(HMODULE) << "\n";
    }
    for(int i = 0; i < numOfModules; i++){
        CHAR lpFileName[1024];
        GetModuleFileNameA(hMods[i], (lpFileName), (DWORD) 1024);
        std::cout << lpFileName << "\n";
    }
    std::cout << hMods[1] << "\n";
    // Release the handle to the process.

    CloseHandle(hProcess);

}
