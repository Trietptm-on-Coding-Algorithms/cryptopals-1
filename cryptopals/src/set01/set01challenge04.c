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
    if(!fileName || strlen(fileName) < 1){
        printf("Error: solveSet1Challenge04 input is NULL or empty.\n");
        return result;
    }

    // Attempt to open the file provided.
    int stringFileFD = open(fileName, O_RDONLY);
    if(stringFileFD < 0){
        printf("Error: solveSet1Challenge04 failed to open file.\n");
        return result;
    }

    // Get the size of the file.
    struct stat sb;
    fstat(stringFileFD, &sb);
    size_t fileSize = sb.st_size;

    // Map the file into memory.
    char *fileMapping = mmap(NULL, fileSize, PROT_READ | PROT_WRITE, MAP_PRIVATE, stringFileFD, 0);
    if(fileMapping == MAP_FAILED){
        printf("Error: solveSet1Challenge04 failed to map file into memory.\n");
        close(stringFileFD);
        return result;
    }

    // Keep track of our most confident response, gauged by the highest number of ASCII matches.
    result = malloc(sizeof(xorDecryptedMessage));
    if(!result){
        printf("Error: solveSet1Challenge04 failed to allocate memory for result.\n");
        close(stringFileFD);
        return result;
    }
    result->score = 0;
    result->key = NULL;
    result->message = NULL;

    // Split the file using newlines as delimiters and test each string.s
    char *currentEncryptedString = strtok(fileMapping, "\n");
    while (currentEncryptedString){

        // The number of bytes represented by the data is half the string length since 2 characters represents one byte.
        int numberOfBytes = strlen(currentEncryptedString) / 2;

        char *encryptedData = decodeHex(currentEncryptedString);
        if(!encryptedData){
            printf("Error: solveSet1Challenge04 failed to load hex into memory.\n");
            continue;
        }

        xorDecryptedMessage *currentDecryptedMessage = xorDecrypt(encryptedData, numberOfBytes, 1);
        if(!currentDecryptedMessage){
            printf("Error: solveSet1Challenge04 failed to decrypt string.\n");
            free(encryptedData);
            currentEncryptedString = strtok(NULL, "\n");
            continue;
        }

        // If this decrypted string contains more matches than the previous best, save it and the key.
        if(result->score < currentDecryptedMessage->score){

            result->score = currentDecryptedMessage->score;

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
        free(encryptedData);
        free(currentDecryptedMessage);
        currentEncryptedString = strtok(NULL, "\n");
    }

    close(stringFileFD);
    return result;
}
