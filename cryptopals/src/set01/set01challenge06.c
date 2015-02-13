#include "set01challenge06.h"

xorDecryptedMessage *solveSet1Challenge06(char *fileName){
    xorDecryptedMessage *result = NULL;

    // Check for invalid arguments.
    if(!fileName || strlen(fileName) < 1){
        printf("Error: solveSet1Challenge06 input is NULL or empty.\n");
        return result;
    }

    // Attempt to open the file provided.
    int stringFileFD = open(fileName, O_RDONLY);
    if(stringFileFD < 0){
        printf("Error: solveSet1Challenge06 failed to open file.\n");
        return result;
    }

    // Get the size of the file.
    struct stat sb;
    fstat(stringFileFD, &sb);
    size_t fileSize = sb.st_size;

    // Map the file into memory.
    char *fileMapping = mmap(NULL, fileSize, PROT_READ | PROT_WRITE, MAP_PRIVATE, stringFileFD, 0);
    if(fileMapping == MAP_FAILED){
        printf("Error: solveSet1Challenge06 failed to map file into memory.\n");
        close(stringFileFD);
        return result;
    }

    /*************************** IN DEVELOPMENT ********************/
    char *base64DecodedData = decodeBase64(fileMapping);
    if (!base64DecodedData){
        printf("Error: solveSet1Challenge06 failed to decode base64 data.\n");
        munmap(fileMapping, fileSize);
        return result;    	
    }

    char *stringOne = "this is a test";
    char *stringTwo = "wokka wokka!!!";
    printf("Hamming Distance: %d\n", computeHammingDistance(stringOne, stringTwo, strlen(stringOne)));


    free(base64DecodedData);

    return result;
}