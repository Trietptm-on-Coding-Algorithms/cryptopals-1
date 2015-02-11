/**
  * Matasano Crypto Challenge Solution
  * Set: 01, Challenge 02: Fixed XOR
  *
  * Coded by rot0x1a, 09 Feb 2015
  */
#include "set01challenge02.h"

char *solveSet1Challenge02(char *hexStringOne, char *hexStringTwo) {
    char *result = NULL;

    hexStringOne = (!hexStringOne || strlen(hexStringOne) < 1) ? "1c0111001f010100061a024b53535009181c" : hexStringOne;
    hexStringTwo = (!hexStringTwo || strlen(hexStringTwo) < 1) ? "686974207468652062756c6c277320657965" : hexStringTwo;

    if (strlen(hexStringOne) % 2) {
        printf("Error: Cannot load hex data of odd length into memory.\n");
        return result;
    }

    char *dataBlockOne = loadHexStringToMemory(hexStringOne);
    if(!dataBlockOne){
        printf("Error: Unable to load string [%s] into memory.\n", hexStringOne);
        return result;
    }

    char *dataBlockTwo = loadHexStringToMemory(hexStringTwo);
    if(!dataBlockTwo){
        printf("Error: Unable to load string [%s] into memory.\n", hexStringTwo);
        return result;
    }

    result = xorDataBlock(dataBlockOne, dataBlockTwo, strlen(hexStringOne));
    free(dataBlockOne);
    free(dataBlockTwo);

    return result;
}


