/**
  * Matasano Crypto Challenge Solution
  * Set: 01, Challenge 04: Detect single-character XOR
  *
  * Coded by rot0x1a, 09 Feb 2015
  */
#include "include/s1c04.h"

int main(int argc, char **argv) {

    // Check for invalid arguments.
    const char *fileName = NULL;
    if(argc != 2){
        fileName = "./resources/s1c04.strings";
        printf("No filename provided. ");
    } else {
        fileName = argv[1];
    }
    printf("Using file [%s]\n", fileName);

    // Attempt to open the file provided.
    int stringFileFD = open(fileName, O_RDONLY);
    if(stringFileFD < 0){
        printf("Could not open file [%s]. Quitting.\n", fileName);
        return -1;
    }

    // Get the size of the file.
    struct stat sb;
    fstat(stringFileFD, &sb);
    size_t fileSize = (sb.st_size);

    // Map the file into memory.
    char *fileMapping = mmap(NULL, fileSize, PROT_READ | PROT_WRITE, MAP_PRIVATE, stringFileFD, 0);
    if(fileMapping == MAP_FAILED){
        printf("Could not map file to memory. Quitting.\n");
        return -1;
    }
    char *fileMappingPtr = fileMapping;

    // Keep track of our most confident response, gauged by the highest number of ASCII matches.
    int highestConfidenceCount = 0;
    char highestConfidenceKey = ' ';
    unsigned char *highestConfidenceMessage = NULL;
    int currentLineNumber = 0;
    int winningLineNumber = 0;

    // Split the file using newlines as delimiters and test each string.s
    fileMappingPtr = strtok(fileMappingPtr, "\n");
    while (fileMappingPtr){

        // Get the number of characters in the string.
        int numCharacters = strlen(fileMappingPtr);

        // Load the hex string into memory.
        unsigned char *cipheredString = loadHexStringToMemory(fileMappingPtr);

        // Keep track of our highest number of ASCII matches.
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

        // If this decrypted string contains more matches than the previous best, save it and the key.
        if(highestConfidenceCount < highestMatchCount){
            highestConfidenceCount = highestMatchCount;
            highestConfidenceKey = highestMatchKey;
            winningLineNumber = currentLineNumber;

            // If we had a previous best match, we can free it now.
            if(highestConfidenceMessage != NULL){
                free(highestConfidenceMessage);
                highestConfidenceMessage = NULL;
            }
            highestConfidenceMessage = highestMatchMessage;
        } else {
            free(highestMatchMessage);
        }

        // Clean up this round and start the next round.
        free(cipheredString);
        fileMappingPtr = strtok(NULL, "\n");
        currentLineNumber++;
    }

    // End the string at any newlines it may contain.
    unsigned char *highestConfidenceMessagePtr = highestConfidenceMessage;
    while(*highestConfidenceMessagePtr != '\0'){
        if(*highestConfidenceMessagePtr == '\n'){
            *highestConfidenceMessagePtr = '\0';
        } else {
            highestConfidenceMessagePtr++;
        }
    }

    // Display the result.
    printf("Line Number: [%d], Key: [%c], Message: [%s]\n", winningLineNumber, highestConfidenceKey, highestConfidenceMessage);

    free(highestConfidenceMessage);
    return 0;
}
