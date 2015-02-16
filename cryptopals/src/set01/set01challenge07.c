/**
  * Matasano Crypto Challenge Solution
  * Set: 01, Challenge 06: AES in ECB mode
  *
  * Coded by rot0x1a, 16 Feb 2015
  */
#include "set01challenge07.h"

char *solveSet1Challenge07(char *fileName, char *key){
    char *result = NULL;

    // Check for invalid arguments.
    if(!fileName || strlen(fileName) < 1){
        printf("Error: solveSet1Challenge07 input is NULL or empty.\n");
        return result;
    }

    // Attempt to open the file provided.
    int stringFileFD = open(fileName, O_RDONLY);
    if(stringFileFD < 0){
        printf("Error: solveSet1Challenge07 failed to open file.\n");
        return result;
    }

    // Get the size of the file.
    struct stat sb;
    fstat(stringFileFD, &sb);
    size_t fileSize = sb.st_size;

    // Map the file into memory.
    char *fileMapping = mmap(NULL, fileSize, PROT_READ | PROT_WRITE, MAP_PRIVATE, stringFileFD, 0);
    if(fileMapping == MAP_FAILED){
        printf("Error: solveSet1Challenge07 failed to map file into memory.\n");
        close(stringFileFD);
        return result;
    }

    /*
     * Work on data here
     */


    // Free resources we no longer need and return the result.
    close(stringFileFD);
    munmap(fileMapping, fileSize);
    return result;
}
