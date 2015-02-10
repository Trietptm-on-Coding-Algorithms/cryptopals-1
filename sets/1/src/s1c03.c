/**
  * Matasano Crypto Challenge Solution
  * Set: 01, Challenge 03: Single-byte XOR cipher
  *
  * Coded by rot0x1a, 09 Feb 2015
  */
#include "include/s1c03.h"

int main(int argc, char **argv) {

    // Check for invalid arguments.
    if(argc != 2){
        printf("Error: Please provide a single strings.\n");
        return -1;
    }

    // Get the number of characters in the string.
    int numCharacters = strlen(argv[1]);

    // Load the hex string into memory.
    unsigned char *cipheredString = loadHexStringToMemory(argv[1]);

    // Keep track of our highest number of matches.
    int highestMatchCount = 0;
    char highestMatchKey = ' ';
    unsigned char *highestMatchMessage = NULL;

    // Check all common ASCII characters as the key.
    for(char xorValue=' '; xorValue<='}'; xorValue++){

        // Create a string the same length as the ciphertext containing only the current ASCII value.
        unsigned char *keyString = malloc(numCharacters);
        memset(keyString, xorValue, numCharacters);

        // XOR the cipher string and our key string together and free the keyString.
        char *xorResult = xorDataBlocks(cipheredString, keyString, numCharacters);
        free(keyString);

        // Load the XOR'ed data into memory so we can treat it like a string.
        unsigned char *xorResultInMemory = loadHexStringToMemory(xorResult);
        
        // TODO: Why can't I free you!
        free(xorResult);

        // Count how many spaces and English alphabet ASCII characters are in the decoded string.
        int thisMatchCount = 0;
        for(int j=0; j<numCharacters; j++){
            if(('A' <= xorResultInMemory[j] && xorResultInMemory[j] <= 'z') || xorResultInMemory[j] == ' '){
                thisMatchCount++;
            }
        }

        // If this decrypted string contains more matches than the previous best, save it and the key.
        if(thisMatchCount > highestMatchCount){
            highestMatchCount = thisMatchCount;
            highestMatchKey = xorValue;

            // If we had a previous best match, we can free it now.
            if(highestMatchMessage != NULL){
                free(highestMatchMessage);
                highestMatchMessage = NULL;
            }
            highestMatchMessage = xorResultInMemory;
        } else {
            free(xorResultInMemory);
        }
    }

    printf("Key: [%c], Message: [%s]\n", highestMatchKey, highestMatchMessage);
    
    // Clean up.
    free(cipheredString);
    free(highestMatchMessage);

    return 0;
}
