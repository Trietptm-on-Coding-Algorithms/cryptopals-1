#include "include/rot0x1a-common.h"

unsigned char *loadHexStringToMemory(char *hexString){
    unsigned char *result = NULL;

    // Check for invalid arguments.
    if(!hexString || !strlen(hexString)){        
        return result;
    }

    // If the hex string is of odd length, prepend a zero.
    int hexStringLength = strlen(hexString);
    int isOddLength = (hexStringLength % 2) ? 1 : 0;
    char *validHexString = calloc(hexStringLength + isOddLength + 1, sizeof(char));
    if(!validHexString){
        printf("Error: loadHexStringToMemory could not allocate memory.\n");
        return result;
    } else if(isOddLength) {
        printf("WARNING: Odd number of characters in hex string. Padding front with a zero.\n");
        strncpy(validHexString, "0", sizeof(char));
    }
    strncpy(validHexString + isOddLength, hexString, hexStringLength);
    char *validHexStringPtr = validHexString;
    hexStringLength = strlen(validHexString);

    // Obtain memory for storing the result.
    result = calloc(hexStringLength, sizeof(char));  
    if(!result){
        printf("Error: loadHexStringToMemory could not allocate memory.\n");
        return result;
    }    

    // Copy the hex string characters into memory as raw data.
    for(int i = 0; i < hexStringLength/2; i++) {
        sscanf(validHexStringPtr, "%2hhx", &result[i]);
        validHexStringPtr += 2;
    }

    // Clean up the mess we made and return.
    free(validHexString);
    return result;
}


char *base64Encode(unsigned char *data, int dataLength){
    char *result = NULL;

    // Check for invalid arguments.
    if(!data || dataLength < 1){        
        return result;
    }

    // Determine the size of memory needed to store the result and allocate it.
    int resultSize = dataLength * 2;
    result = calloc(resultSize + 1, sizeof(char));
    if(!result){
        printf("Error: Could not allocate memory.\n");
        exit(-1);
    }    

    // Base64 encode the data, 24 bytes at a time.
    int numWrote = 0;
    for(int i=0; i<dataLength; i+=3){

        // Grab the next 24 bit chunk of data to encode.
        unsigned int currentChunk = 0;
        currentChunk = currentChunk | (data[i + 0]  << 16); // Grab bits [23, 22, 21, 20, 19, 18, 17, 16]
        currentChunk = currentChunk | (data[i + 1]  <<  8); // Grab bits [15, 14, 13, 12, 11, 10,  9,  8]
        currentChunk = currentChunk | (data[i + 2]  <<  0); // Grab bits [ 7,  6,  5,  4,  3,  2,  1,  0]

        // Divide the currentChunk into 4 6-bit blocks.
        unsigned int block1 = (currentChunk & 0xFC0000) >> 18;  // block1 consists of bits: [23, 22, 21, 20, 19, 18]
        unsigned int block2 = (currentChunk & 0x03F000) >> 12;  // block2 consists of bits: [17, 16, 15, 14, 13, 12]
        unsigned int block3 = (currentChunk & 0x000FC0) >>  6;  // block3 consists of bits: [11, 10,  9,  8,  7,  6]
        unsigned int block4 = (currentChunk & 0x00003F) >>  0;  // block4 consists of bits: [ 5,  4,  3,  2,  1,  0]

        // Append the base64 character for each block onto the result.
        strncpy(result + numWrote++, &BASE64_ENCODING_VALUES[block1], sizeof(char)); // Copy base64 encoding of block 1
        strncpy(result + numWrote++, &BASE64_ENCODING_VALUES[block2], sizeof(char)); // Copy base64 encoding of block 2
        strncpy(result + numWrote++, &BASE64_ENCODING_VALUES[block3], sizeof(char)); // Copy base64 encoding of block 3
        strncpy(result + numWrote++, &BASE64_ENCODING_VALUES[block4], sizeof(char)); // Copy base64 encoding of block 4
    }

    // If the original data was not a multiple of 3 bytes, we will pad the rest with the "=" character
    int remainingBytes = dataLength % 3;
    if (remainingBytes == 1) {
        strncpy(result + numWrote - 2, "==", sizeof(char) * 3);
    } else if (remainingBytes == 2) {
        strncpy(result + numWrote - 1, "=", sizeof(char) * 2);
    }

    return result;
}