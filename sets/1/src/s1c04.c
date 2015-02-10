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

    // Keep track of our most confident response, gauged by the highest number of ASCII matches.
    xorDecryptedMessage *bestDecryptedMessage = malloc(sizeof(xorDecryptedMessage));
    bestDecryptedMessage->numberOfMatches = 0;
    bestDecryptedMessage->key = NULL;
    bestDecryptedMessage->message = NULL;

    // We also want to report the line number that contained the encrypted string.
    int winningLineNumber = 0;
    int currentLineNumber = 0;

    // Split the file using newlines as delimiters and test each string.s
    char *currentEncryptedString = strtok(fileMapping, "\n");
    while (currentEncryptedString){

        xorDecryptedMessage *currentDecryptedMessage = decryptHexStringUsingXOR(currentEncryptedString, 1);

        // If this decrypted string contains more matches than the previous best, save it and the key.
        if(bestDecryptedMessage->numberOfMatches < currentDecryptedMessage->numberOfMatches){

            winningLineNumber = currentLineNumber;
            bestDecryptedMessage->numberOfMatches = currentDecryptedMessage->numberOfMatches;

            // If we had a previous best match for the key, we can free it now.
            if(bestDecryptedMessage->key != NULL){
                free(bestDecryptedMessage->key);
                bestDecryptedMessage->key = NULL;
            }
            bestDecryptedMessage->key = currentDecryptedMessage->key;

            // If we had a previous best match for the message, we can free it now.
            if(bestDecryptedMessage->message != NULL){
                free(bestDecryptedMessage->message);
                bestDecryptedMessage->message = NULL;
            }
            bestDecryptedMessage->message = currentDecryptedMessage->message;

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
    char *decryptedMessagePtr = bestDecryptedMessage->message;
    while(*decryptedMessagePtr != '\0'){
        if(*decryptedMessagePtr == '\n'){
            *decryptedMessagePtr = '\0';
        } else {
            decryptedMessagePtr++;
        }
    }

    // Display the result.
    printf("Line Number: %d\nKey: %s\nMatches: %d\nMessage: %s\n", winningLineNumber, bestDecryptedMessage->key, bestDecryptedMessage->numberOfMatches, bestDecryptedMessage->message);

    // Clean up after ourselves and exit.
    free(bestDecryptedMessage->key);
    free(bestDecryptedMessage->message);
    free(bestDecryptedMessage);
    return 0;
}
