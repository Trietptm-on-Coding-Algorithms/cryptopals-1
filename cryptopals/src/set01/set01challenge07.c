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
    if (!fileName || strlen(fileName) < 1){
        printf("Error: solveSet1Challenge06 fileName input is NULL or empty.\n");
        return result;
    } else if (!key || strlen(key) < 1){
        printf("Error: solveSet1Challenge06 key input is NULL or empty.\n");
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

    // Load the base64 encoded data into memory.
    char *base64DecodedData = decodeBase64(fileMapping);
    if (!base64DecodedData){
        printf("Error: solveSet1Challenge06 failed to decode base64 data.\n");
        close(stringFileFD);
        munmap(fileMapping, fileSize);
        return result;      
    }
    int base64DecodedDataSize = (strlen(fileMapping) / 4) * 3;

    // Prepare for decryption.
    unsigned char *aesOut = calloc(base64DecodedDataSize, sizeof(char));
    const unsigned char *aesIn = (const unsigned char *)base64DecodedData;
	AES_KEY aesKey;
	AES_set_decrypt_key((const unsigned char *)key, strlen(key) * 8, &aesKey);

	// Decrypt the 16 bit blocks.
	int count = 0;
	while (count < base64DecodedDataSize){
		AES_ecb_encrypt(aesIn + count, aesOut + count, (const AES_KEY *)&aesKey, AES_DECRYPT);
	  	count += strlen(key);
	}

	// Strip PKCS7 padding.
	int paddingLength = aesOut[count - 1];
	for(int i=1; i<=paddingLength; i++){
		aesOut[count-i] = '\0';
	}

	// Copy the output to our result.
	result = calloc(base64DecodedDataSize + 1, sizeof(char));
	strncpy(result, (char *)aesOut, base64DecodedDataSize);

    // Free resources we no longer need and return the result.
	free(aesOut);
    free(base64DecodedData);
    close(stringFileFD);
    munmap(fileMapping, fileSize);
    return result;
}
