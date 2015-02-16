#include "set01challenge06.h"

char *solveSet1Challenge06(char *fileName){
    char *result = NULL;

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


    // Load the base64 encoded data into memory.
    char *base64DecodedData = decodeBase64(fileMapping);
    if (!base64DecodedData){
        printf("Error: solveSet1Challenge06 failed to decode base64 data.\n");
        close(stringFileFD);
        munmap(fileMapping, fileSize);
        return result;      
    }

    // Determine the key size for decrypting the data.
    int base64DecodedDataSize = (strlen(fileMapping) / 4) * 3;
    int maxKeySize = 40;
    int keySize = determineKeySize(base64DecodedData, base64DecodedDataSize, maxKeySize);
    if(keySize < 1){
        printf("Error: solveSet1Challenge06 failed to determineKeySize.\n");
        free(base64DecodedData);
        close(stringFileFD);
        munmap(fileMapping, fileSize);
        return result;      
    }

    // Divide the data into blocks
    char **dataInBlocks = divideDataIntoBlocks(base64DecodedData, base64DecodedDataSize, keySize);
    if(!dataInBlocks){
        printf("Error: solveSet1Challenge06 failed to divideDataIntoBlocks.\n");
        free(base64DecodedData);
        close(stringFileFD);
        munmap(fileMapping, fileSize);
        return result;      
    }

    // Transpose the blocks
    int numColumns = keySize;
    int numRows = 1 + (base64DecodedDataSize / keySize);
    char **transposedData = transposeBlocks(dataInBlocks, numColumns, numRows);
    if(!transposedData){
        printf("Error: solveSet1Challenge06 failed to transposeBlocks.\n");
        free(dataInBlocks);
        free(base64DecodedData);
        close(stringFileFD);
        munmap(fileMapping, fileSize);
        return result;      
    }

    // Allocate memory for the decrypted blocks.
    xorDecryptedMessage **decryptedBlocks = calloc(sizeof(char *) * keySize, sizeof(char));
    if(!decryptedBlocks){
        printf("Error: solveSet1Challenge06 failed to allocate memory for decryptedBlocks.\n");
        free(transposedData);
        free(dataInBlocks);
        free(base64DecodedData);
        close(stringFileFD);
        munmap(fileMapping, fileSize);
        return result;      
    }

    // Decrypt the transposed blocks.
    for(int i=0; i<keySize; i++){
        decryptedBlocks[i] = xorDecrypt(transposedData[i], numRows, 1);
        if(!decryptedBlocks[i]){
            printf("Error: solveSet1Challenge06 failed to xorDecrypt.\n");
            while(--i >= 0){
                free(decryptedBlocks[i]);
            }
            free(decryptedBlocks);
            free(transposedData);
            free(dataInBlocks);
            free(base64DecodedData);
            close(stringFileFD);
            munmap(fileMapping, fileSize);
            return result;      
        }
    }

    // Allocate memory for the result string.
    result = calloc(base64DecodedDataSize + 1, sizeof(char));
    if(!result){
        printf("Error: solveSet1Challenge06 failed to allocate memory for result.\n");
        for(int i=0; i<keySize; i++){
            free(decryptedBlocks[i]);
        }
        free(decryptedBlocks);
        free(transposedData);
        free(dataInBlocks);
        free(base64DecodedData);
        close(stringFileFD);
        munmap(fileMapping, fileSize);
        return result;      
    }

    // Copy the decryption results into this function's result.
    int bytesWritten = 0;
    for(int i=0; i<numRows; i++){
        for(int j=0; j<numColumns; j++){

            // Do not write more bytes than the original data represented
            if(bytesWritten < base64DecodedDataSize){
                *(result + bytesWritten) = (bytesWritten < base64DecodedDataSize) ? (decryptedBlocks[j]->message)[i] : '\0';
            } else if (bytesWritten == base64DecodedDataSize) {
                *(result + bytesWritten) = '\0';
            }
            bytesWritten++;
        }
    }

    /* Free allocated memory */
    for(int i=0; i<numRows; i++){
        free(dataInBlocks[i]);
    }

    for(int i=0; i<numColumns; i++){
        free(decryptedBlocks[i]->key);
        free(decryptedBlocks[i]->message);
        free(decryptedBlocks[i]);
        free(transposedData[i]);
    }    

    free(dataInBlocks);
    free(transposedData);
    free(base64DecodedData);
    free(decryptedBlocks);
    close(stringFileFD);
    munmap(fileMapping, fileSize);

    // Return the result.
    return result;
}
