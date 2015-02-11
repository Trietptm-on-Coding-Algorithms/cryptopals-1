/**
  * Matasano Crypto Challenge Solution
  * Set: 01, Challenge 01: Convert Hex to Base64
  *
  * Coded by rot0x1a, 08 Feb 2015
  */
#include "set01challenge01.h"

char *solveSet1Challenge01(char *hexString){
    char *result = NULL;

    // If no string provided, use the default string.
    hexString = (hexString) ? hexString : "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";

    int hexStringLength = strlen(hexString);
    hexStringLength = (hexStringLength % 2) ? hexStringLength + 1 : hexStringLength;

    // Attempt to load the hex characters into memory as raw data.
    char *dataLocation = loadHexStringToMemory(hexString);
    if(!dataLocation) {
        printf("Error: hexToBase64 failed to load hex data into memory.\n");
        return result;
    }

    // Get the base64 representation of data we stored in memory.
    result = base64Encode(dataLocation, hexStringLength/2);
    if(!result) {
        printf("Error: hexToBase64 failed to get base64 encoding of data.\n");
        return result;
    }

    // Clean up the mess we made and return.
    free(dataLocation);
    return result;
}
