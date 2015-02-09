/**
  * Matasano Crypto Challenge Solution
  * Set: 01, Challenge 01: Convert Hex to Base64
  *
  * Coded by rot0x1a, 08 Feb 2015
  */
#import "include/s1c01.h"

int main(int argc, char **argv) {
    if(argc != 2){
        printf("Error: Please input hex-string.\n");
        return -1;
    }

    printf("%s\n", hexToBase64(argv[1]));
}


char *hexToBase64(char *hexString){
    char *result = NULL;

    // Check for invalid arguments.
    if(!hexString){
        return result;
    }

    int hexStringLength = strlen(hexString);
    hexStringLength = (hexStringLength % 2) ? hexStringLength + 1 : hexStringLength;

    // Attempt to load the hex characters into memory as raw data.
    unsigned char *dataLocation = loadHexStringToMemory(hexString);
    if(!dataLocation) {
        printf("Error: hexToBase64 failed to load hex data into memory.\n");
        exit(-1);
    }

    // Get the base64 representation of data we stored in memory.
    result = base64Encode(dataLocation, hexStringLength/2);
    if(!result) {
        printf("Error: hexToBase64 failed to get base64 encoding of data.\n");
        exit(-1);
    }

    // Clean up the mess we made and return.
    free(dataLocation);
    return result;
}
