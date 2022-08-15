//
// Created by fidel on 8/14/2022.
//
#include "../hack_file/camera_hack.h"


void print_cameraStructs(const std::vector<unsigned int>& cameraStruct)
{
    for(unsigned int i : cameraStruct)
        std::cout <<  std::hex << i << " ";
    std::cout << "\n";
}

/**
 *  takes in the pointer address and size of bytes of the address
 *  suppose to replace address with 0x90 as the bytes of the address but not working
 * */
void no_op(uintptr_t baseAddressToReplace, int bytes)
{
    DWORD d, ds;
    VirtualProtect((void*)baseAddressToReplace, bytes, PAGE_EXECUTE_READWRITE, &d);
    memset((void*)baseAddressToReplace, NOP, bytes);
    std::cout << baseAddressToReplace << "\n";
    VirtualProtect((void*)baseAddressToReplace, bytes, d, &ds);

    //loop through function

}


