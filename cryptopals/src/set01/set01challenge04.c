/**
  * Matasano Crypto Challenge Solution
  * Set: 01, Challenge 04: Detect single-character XOR
  *
  * Coded by rot0x1a, 09 Feb 2015
  */
#include "set01challenge04.h"

xorDecryptedMessage *solveSet1Challenge04(char *fileName) {

    xorDecryptedMessage *result = NULL;
    
    // Check for invalid arguments.
    fileName = (!fileName || strlen(fileName) < 1) ? "./resources/s1c04.strings" : fileName;

    // Attempt to open the file provided.
    int stringFileFD = open(fileName, O_RDONLY);
    if(stringFileFD < 0){
        printf("Could not open file [%s]. Quitting.\n", fileName);
        return result;
    }

    // Get the size of the file.
    struct stat sb;
    fstat(stringFileFD, &sb);
    size_t fileSize = (sb.st_size);

    // Map the file into memory.
    char *fileMapping = mmap(NULL, fileSize, PROT_READ | PROT_WRITE, MAP_PRIVATE, stringFileFD, 0);
    if(fileMapping == MAP_FAILED){
        printf("Could not map file to memory. Quitting.\n");
        return result;
    }

    // Keep track of our most confident response, gauged by the highest number of ASCII matches.
    result = malloc(sizeof(xorDecryptedMessage));
    if(!result){
        printf("Could not obtain memory.\n");
        return result;
    }
    result->numberOfMatches = 0;
    result->key = NULL;
    result->message = NULL;

    // We also want to report the line number that contained the encrypted string.
    int currentLineNumber = 0;

    // Split the file using newlines as delimiters and test each string.s
    char *currentEncryptedString = strtok(fileMapping, "\n");
    while (currentEncryptedString){

        xorDecryptedMessage *currentDecryptedMessage = decryptHexStringUsingXOR(currentEncryptedString, 1);
        if(!currentDecryptedMessage){
            printf("Could not decrypt string: %s\n", currentEncryptedString);
            currentEncryptedString = strtok(NULL, "\n");
            continue;
        }

        // If this decrypted string contains more matches than the previous best, save it and the key.
        if(result->numberOfMatches < currentDecryptedMessage->numberOfMatches){

            result->numberOfMatches = currentDecryptedMessage->numberOfMatches;

            // If we had a previous best match for the key, we can free it now.
            if(result->key != NULL){
                free(result->key);
                result->key = NULL;
            }
            result->key = currentDecryptedMessage->key;

            // If we had a previous best match for the message, we can free it now.
            if(result->message != NULL){
                free(result->message);
                result->message = NULL;
            }
            result->message = currentDecryptedMessage->message;

        } else {
            free(currentDecryptedMessage->key);
            free(currentDecryptedMessage->message);
        }

        // Clean up this round and prepare for the next.
        free(currentDecryptedMessage);
        currentEncryptedString = strtok(NULL, "\n");
        currentLineNumber++;
    }

    // End the string at any newlines it may contain.
    char *decryptedMessagePtr = result->message;
    while(*decryptedMessagePtr != '\0'){
        if(*decryptedMessagePtr == '\n'){
            *decryptedMessagePtr = '\0';
        } else {
            decryptedMessagePtr++;
        }
    }

    return result;
}
