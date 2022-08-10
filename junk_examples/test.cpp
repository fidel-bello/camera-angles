#include <cstdio>
#include <windows.h>
#include <tlhelp32.h>
#include <iostream>
#include <psapi.h>
#include <tchar.h>
#include <memoryapi.h>

void EnableDebugPriv()
{
    HANDLE hToken;
    LUID luid;
    TOKEN_PRIVILEGES tkp;

    OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken);

    LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &luid);

    tkp.PrivilegeCount = 1;
    tkp.Privileges[0].Luid = luid;
    tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    AdjustTokenPrivileges(hToken, false, &tkp, sizeof(tkp), NULL, NULL);

    CloseHandle(hToken);
}



int main(int, char *[])
{
    //EnableDebugPriv();

    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

    if (Process32First(snapshot, &entry) == TRUE)
    {
        while (Process32Next(snapshot, &entry) == TRUE)
        {
            if (_stricmp(entry.szExeFile, "RotMG Exalt.exe") == 0)
            {
                HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, entry.th32ProcessID);

                MODULEINFO modinfo;
                HMODULE hArray[1024];
                DWORD fak;
                EnumProcessModules(hProcess, hArray, sizeof(hArray), &fak);

                GetModuleInformation(hProcess, hArray[39],&modinfo,sizeof(MODULEINFO) );
                TCHAR Buffer[MAX_PATH];

                if (GetModuleFileNameEx(hProcess, hArray[39], Buffer, MAX_PATH))
                {
                    _tprintf(TEXT("\t%s (0x%08X)\n"), Buffer, hArray[39]);
                }

                std::cout << modinfo.EntryPoint << "\n";
                std::cout << modinfo.lpBaseOfDll << "\n";
                std::cout << modinfo.SizeOfImage << "\n";

                while (true) {

                    //get base offset
                    uintptr_t playerPtr = (uintptr_t)(modinfo.lpBaseOfDll) + 0x03B7A318;

                    uintptr_t playerObjectAddr;

                    ReadProcessMemory(hProcess, (LPVOID)playerPtr, &playerObjectAddr, sizeof(playerObjectAddr), NULL);

                    std::cout << "\n dll + offset: " << (uintptr_t *)playerObjectAddr << "\n";

                    uintptr_t jump1 = playerObjectAddr + 0x210;
                    uintptr_t store1;
                    ReadProcessMemory(hProcess, (LPVOID)jump1, &store1, sizeof(store1), NULL);

                    std::cout << "\n + 0x210: " << (uintptr_t *)store1 << "\n";

                    uintptr_t jump2 = store1 + 0x1B8;
                    uintptr_t store2;
                    ReadProcessMemory(hProcess, (LPVOID)jump2, &store2, sizeof(store2), NULL);

                    std::cout << "\n + 0x1B8: " << (uintptr_t *)store2 << "\n";

                    uintptr_t jump3 = store2 + 0x28;
                    uintptr_t store3;
                    ReadProcessMemory(hProcess, (LPVOID)jump3, &store3, sizeof(store3), NULL);

                    std::cout << "\n + 0x28: " << (uintptr_t *)store3 << "\n";

                    uintptr_t jump4 = store3 + 0x1C4;
                    int store4;
                    ReadProcessMemory(hProcess, (LPVOID)jump4, &store4, sizeof(store4), NULL);

                    std::cout << "\n + 0x1C4 (MAX HP): " << (store4) << "\n";

                    uintptr_t jump5 = store3 + 0x1C8;
                    int store5;
                    ReadProcessMemory(hProcess, (LPVOID)jump5, &store5, sizeof(store5), NULL);

                    std::cout << "\n + 0x1C8 (HP): " << (store5) << "\n";

                    Sleep(200);
                }
                CloseHandle(hProcess);
            }
        }
    }

    CloseHandle(snapshot);

    return 0;
}