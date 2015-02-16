/**
  * Matasano Crypto Challenge Solution
  * Set: 01, Challenge 02: Fixed XOR
  *
  * Coded by rot0x1a, 09 Feb 2015
  */
#include "set01challenge02.h"

char *solveSet1Challenge02(char *hexStringOne, char *hexStringTwo) {
    char *result = NULL;

    // Check for invalid arguments.
    if(!hexStringOne || strlen(hexStringOne) < 1){
        printf("Error: solveSet1Challenge02 hexStringOne input is NULL or empty.\n");
        return result;
    } else if(!hexStringTwo || strlen(hexStringTwo) < 1){
        printf("Error: solveSet1Challenge02 hexStringTwo input is NULL or empty.\n");
        return result;
    } else if (strlen(hexStringOne) % 2) {
        printf("Error: solveSet1Challenge02 hexStringOne input is not byte aligned.\n");
        return result;
    } else if (strlen(hexStringOne) != strlen(hexStringTwo)){
        printf("Error: solveSet1Challenge02 input lengths do not match.\n");
        return result;
    }

    // Load the first hex string into memory as data.
    char *dataBlockOne = decodeHex(hexStringOne);
    if(!dataBlockOne){
        printf("Error: solveSet1Challenge02 unable to load hexStringOne into memory.\n");
        return result;
    }

    // Load the second hex string into memory as data.
    char *dataBlockTwo = decodeHex(hexStringTwo);
    if(!dataBlockTwo){
        printf("Error: solveSet1Challenge02 unable to load hexStringTwo into memory.\n");
        free(dataBlockOne);
        return result;
    }

    // XOR the data
    char *xorResult = xorDataBlock(dataBlockOne, (strlen(hexStringOne) / 2), dataBlockTwo, (strlen(hexStringTwo) / 2));
    if(!xorResult){
        printf("Error: solveSet1Challenge02 unable to read memory into hex string.\n");
        free(dataBlockTwo);
        free(dataBlockOne);
        return result;
    }

    // Retrieve the result as hex for displaying.
    result = encodeHex(xorResult, strlen(hexStringOne)/2);
    if(!result){
        printf("Error: solveSet1Challenge02 unable to read memory into hex string.\n");
        free(xorResult);
        free(dataBlockTwo);
        free(dataBlockOne);
        return result;
    }

    // Free memory we no longer need and return the result.
    free(xorResult);
    free(dataBlockTwo);
    free(dataBlockOne);
    return result;
}
