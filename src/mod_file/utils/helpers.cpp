//
// Created by fidel on 8/14/2022.
//

/**
 * @param size takes in size of bytes of array
 * @param val takes in the val of the NOP from constants directory. or 0x90
 * @returns return an array of NOP in n bytes
 */
char *dynamic_nop(int size, char val)
{
    char* array = new char[size];
    for(int i = 0; i < size; i++)
    {
        array[i] = val;
    }
    return array;
}

/**
 *
 * @param array takes an array of values from the address
 * @param size  takes the size of bytes in the array
 * @return returns the original values from the array before being no-oped
 */
unsigned char* revert_address(unsigned char array[], int size)
{
     unsigned char *newArray = new unsigned char[size];
    for(int i = 0; i < size; i++)
    {
        newArray[i] = array[i];
    }
    return newArray;
}







