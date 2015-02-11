/**
  * Matasano Crypto Challenge Solution
  * Set: 01, Challenge 02: Fixed XOR
  *
  * Coded by rot0x1a, 09 Feb 2015
  */
#include "include/s1c02.h"

int main(int argc, char **argv) {
    if( (argc != 3) || (strlen(argv[1]) != strlen(argv[2])) ){
        printf("Error: Please provide 2 equal-length hex strings.\n");
        return -1;
    }

    char *dataBlockOne = loadHexStringToMemory(argv[1]);
    char *dataBlockTwo = loadHexStringToMemory(argv[2]);
    if(!dataBlockOne || !dataBlockTwo){
        printf("Error: Unable to load data blocks into memory.\n");
        return -1;
    }

    int numBytes = (strlen(argv[1]) % 2) ? (strlen(argv[1]) + 1) : strlen(argv[1]);
    char *result = xorDataBlock(dataBlockOne, dataBlockTwo, numBytes);

    printf("Result: %s\n", result);

    free(dataBlockOne);
    free(dataBlockTwo);
    free(result);
}


