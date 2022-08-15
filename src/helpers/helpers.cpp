//
// Created by fidel on 8/14/2022.
//

/**
 * dynamic_nop(size, val)
 * size == the size of the array, val = NOP or whatever value you want to pass in;
 * will be useful for future functions that have to be nop for the mod to work
 **/
char* dynamic_nop(int size, char val)
{
    char* array = new char[size];
    for(int i = 0; i < size; i++)
    {
        array[i] = val;
    }
    return array;
}
