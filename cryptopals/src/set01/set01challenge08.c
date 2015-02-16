/**
  * Matasano Crypto Challenge Solution
  * Set: 01, Challenge 08: Detect AES in ECB mode
  *
  * Coded by rot0x1a, 16 Feb 2015
  */
#include "set01challenge08.h"

char *solveSet1Challenge08(char *fileName){
    char *result = NULL;
    
    // Check for invalid arguments.
    if(!fileName || strlen(fileName) < 1){
        printf("Error: solveSet1Challenge08 input is NULL or empty.\n");
        return result;
    }

    // Attempt to open the file provided.
    int stringFileFD = open(fileName, O_RDONLY);
    if(stringFileFD < 0){
        printf("Error: solveSet1Challenge08 failed to open file.\n");
        return result;
    }

    // Get the size of the file.
    struct stat sb;
    fstat(stringFileFD, &sb);
    size_t fileSize = sb.st_size;

    // Map the file into memory.
    char *fileMapping = mmap(NULL, fileSize, PROT_READ | PROT_WRITE, MAP_PRIVATE, stringFileFD, 0);
    if(fileMapping == MAP_FAILED){
        printf("Error: solveSet1Challenge08 failed to map file into memory.\n");
        close(stringFileFD);
        return result;
    }
    result = NULL;

    // Split the file using newlines as delimiters and test each string.s
    char *currentLine = strtok(fileMapping, "\n");
    while (currentLine){

        // The number of bytes represented by the data is half the string length since 2 characters represents one byte.
        int numberOfBytes = strlen(currentLine);
        printf("Current line length: %d\n", numberOfBytes);
        currentLine = strtok(NULL, "\n");
    }

    // Free resources we no longer need and return the result.
    munmap(fileMapping, fileSize);
    close(stringFileFD);
    return result;
}
