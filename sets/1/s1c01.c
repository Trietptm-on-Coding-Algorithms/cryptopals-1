/**
  * Matasano Crypto Challenge Solution
  * Set: 01, Challenge 01: Convert Hex to Base64
  *
  * Coded by rot0x1a, 08 Feb 2015
  */
#import "s1c01.h"

int main(int argc, char **argv) {
    if(argc != 2){
        printf("Error: Please input hex-string.\n");
        return -1;
    }

    printf("%s\n", hexToBase64(argv[1]));
}


char *hexToBase64(char *hexString){

    // Check for invalid arguments.
    if(!hexString || !strlen(hexString)){        
        return NULL;
    }

    // If the hex string is of odd length, prepend a zero.
    int hexStringLength = strlen(hexString);
    int isOddLength = (hexStringLength % 2) ? 1 : 0;
    char *validHexString = calloc(hexStringLength + isOddLength + 1, sizeof(char));
    if(!validHexString){
        printf("Error: Could not allocate memory.\n");
        exit(-1);
    } else if(isOddLength) {
        printf("WARNING: Odd number of characters in hex string. Padding front with a zero.\n");
        strncpy(validHexString, "0", sizeof(char));
    }

    // Copy the rest of the hex string.
    strncpy(validHexString + isOddLength, hexString, hexStringLength);
    char *validHexStringPtr = validHexString;
    hexStringLength = strlen(validHexString);

    // Copy the hex string characters into memory as raw data.
    unsigned char *dataLocation = calloc(hexStringLength, sizeof(char));  
    if(!dataLocation){
        printf("Error: Could not allocate memory.\n");
        exit(-1);
    }    
    for(int i = 0; i < hexStringLength/2; i++) {
        sscanf(validHexStringPtr, "%2hhx", &dataLocation[i]);
        validHexStringPtr += 2;
    }

    // Now that we have the data represented by the hex string stored in memory, we can start converting it to base64.
    int base64Size = hexStringLength * 2;
    char *result = calloc(base64Size + 1, sizeof(char));
    if(!result){
        printf("Error: Could not allocate memory.\n");
        exit(-1);
    }    

    // Base64 encode the data, 24 bytes at a time.
    int numWrote = 0;
    for(int i=0; i<(hexStringLength/2); i+=3){

        // Grab the next 24 bit chunk of data to encode.
        unsigned int currentChunk = 0;
        currentChunk = currentChunk | (dataLocation[i + 0]  << 16); // Grab bits [23, 22, 21, 20, 19, 18, 17, 16]
        currentChunk = currentChunk | (dataLocation[i + 1]  <<  8); // Grab bits [15, 14, 13, 12, 11, 10,  9,  8]
        currentChunk = currentChunk | (dataLocation[i + 2]  <<  0); // Grab bits [ 7,  6,  5,  4,  3,  2,  1,  0]

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
    int remainingBytes = (hexStringLength * 2) % 3;
    if (remainingBytes == 1) {
        strncpy(result + numWrote - 2, "==", sizeof(char) * 3);
    } else if (remainingBytes == 2) {
        strncpy(result + numWrote - 1, "=", sizeof(char) * 2);        
    }

    // Clean up the mess we made and return.
    free(validHexString);
    free(dataLocation);
    return result;
}
