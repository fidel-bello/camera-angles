//
// Created by fidel on 8/14/2022.
//

/**
 * dynamic_nop(size, val)
 * size == the size of the array, val = NOP or whatever value you want to pass in;
 * will be useful for future functions that have to be nop for the mod to work
 **/
#include "../camera_hack.h"


char *dynamic_nop(int size, char val)
{
    char* array = new char[size];
    for(int i = 0; i < size; i++)
    {
        array[i] = val;
    }
    return array;
}

//create empty arr, insert elements from input array, new-arr = input-arr;
unsigned char* revert_address(unsigned char array[], int size, HANDLE hProc, LPVOID baseAddress)
{
    unsigned char* newArray = new unsigned char[size];
    for(int i = 0; i < size; i++)
    {
        newArray[i] = array[i];
        WriteProcessMemory(hProc, baseAddress, newArray, size, nullptr);
    }
    return newArray;
}







