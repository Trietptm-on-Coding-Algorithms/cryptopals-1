/**
  * Matasano Crypto Challenge Solution
  * Set: 01, Challenge 03: Single-byte XOR cipher
  *
  * Coded by rot0x1a, 09 Feb 2015
  */
#include "set01challenge03.h"

xorDecryptedMessage *solveSet1Challenge03(char *hexString) {
    xorDecryptedMessage *result = NULL;

    // Check for invalid arguments.
    if(!hexString || strlen(hexString) < 1){
        printf("Error: solveSet1Challenge03 input is NULL or empty.\n");
        return result;
    } else if (strlen(hexString) % 2) {
        printf("Error: solveSet1Challenge03 input is not byte aligned.\n");
        return result;
    }

    // Load the hex into memory as data.
    char *dataLocation = decodeHex(hexString);
    if(!dataLocation) {
        printf("Error: hexToBase64 failed to load hex into memory.\n");
        return result;
    }

    // The number of bytes represented by the data is half the string length since 2 characters represents one byte.
    int numberOfBytes = strlen(hexString) / 2;

    // Decrypt.
    result = xorDecrypt(dataLocation, numberOfBytes, 1);
    if(!result){
        printf("Error: Could not decrypt hex string.\n");
        free(dataLocation);
        return result;
    }
    
    // Free memory we no longer need and return the result.
    free(dataLocation);
    return result;
}
