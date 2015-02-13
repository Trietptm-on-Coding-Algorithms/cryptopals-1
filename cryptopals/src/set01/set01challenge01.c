/**
  * Matasano Crypto Challenge Solution
  * Set: 01, Challenge 01: Convert Hex to Base64
  *
  * Coded by rot0x1a, 08 Feb 2015
  */
#include "set01challenge01.h"

char *solveSet1Challenge01(char *hexString){
    char *result = NULL;

    // Check for invalid arguments.
    if(!hexString || strlen(hexString) < 1){
        printf("Error: solveSet1Challenge01 input is NULL or empty.\n");
        return result;
    } else if (strlen(hexString) % 2) {
        printf("Error: solveSet1Challenge01 input is not byte aligned.\n");
        return result;
    }

    // The number of bytes represented by the data is half the string length since 2 characters represents one byte.
    int numberOfBytes = strlen(hexString) / 2;

    // Load the hex into memory as data.
    char *dataLocation = decodeHex(hexString);
    if(!dataLocation) {
        printf("Error: hexToBase64 failed to load hex into memory.\n");
        return result;
    }

    // Get the base64 representation of data we stored in memory.
    result = encodeBase64(dataLocation, numberOfBytes);
    if(!result) {
        printf("Error: hexToBase64 failed to get base64 encoding of data.\n");
        free(dataLocation);
        return result;
    }

    // Free memory we no longer need and return the result.
    free(dataLocation);
    return result;
}
