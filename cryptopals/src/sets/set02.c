#include "set02.h"

/**
  * Matasano Crypto Challenge Solution
  * Set: 02, Challenge 01:  Implement PKCS#7 padding
  *
  * Coded by rot0x1a, 17 Feb 2015
  */
char *solveSet2Challenge01(char *data, int desiredLength){
	char *result = NULL;

    // Check for invalid arguments.
    if(!data && strlen(data)){
        printf("Error: solveSet2Challenge01 data input is NULL.\n");
        return result;
    } else if (desiredLength < 1) {
        printf("Error: solveSet2Challenge01 desiredLength input is less than 1.\n");
        return result;
    }

    int numberOfBytes = strlen(data);    
    result = pkcs7(data, numberOfBytes, desiredLength);
    if(!result){
        printf("Error: solveSet2Challenge01 call to pcks7 failed.\n");
        return result;
    }

    return result;
}



/**
  * Matasano Crypto Challenge Solution
  * Set: 02, Challenge 02:  Implement CBC Mode
  *
  * Coded by rot0x1a, 18 Feb 2015
  */
char *solveSet2Challenge02(char *fileName){
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

    int base64DataSize = (strlen(fileMapping) / 4) * 3;

    char *encrypted = decodeBase64(fileMapping);
    if(!encrypted){
        printf("Error: solveSet1Challenge08 to decode base64 data.\n");
        munmap(fileMapping, fileSize);
        close(stringFileFD);
        return result;
    }

    result = aesDecryptCBC(encrypted, base64DataSize, "YELLOW SUBMARINE", 16);
    free(encrypted);
    return result;
}