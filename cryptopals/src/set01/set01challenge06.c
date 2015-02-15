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

    // Load the base64 encoded data into memory.
    char *base64DecodedData = decodeBase64(fileMapping);
    if (!base64DecodedData){
        printf("Error: solveSet1Challenge06 failed to decode base64 data.\n");
        munmap(fileMapping, fileSize);
        return result;    	
    }


    /*************************** ACTUAL BREAKING ********************/

 	// Known results
    char *key = "Terminator X: Bring the noise";
    int keySize = strlen(key) * 2;

    int base64DecodedDataSize =  (strlen(fileMapping) / 4) * 3;

    printf("base64DecodedDataSize: %d, keySize: %d\n", base64DecodedDataSize, keySize);

    int numColumns = keySize;
    int numRows = 1 + (base64DecodedDataSize / keySize);
    char **dataInBlocks = divideDataIntoBlocks(base64DecodedData, base64DecodedDataSize, keySize);
    char **transposedData = transposeBlocks(dataInBlocks, numColumns, numRows);

    xorDecryptedMessage **decryptedBlocks = malloc(sizeof(char *) * keySize);
    for(int i=0; i<keySize; i++){
    	decryptedBlocks[i] = xorDecrypt(transposedData[i], numRows, 1);
    }

    for(int i=0; i<numRows; i++){
    	for(int j=0; j<keySize; j++){
			printf("%c", (decryptedBlocks[j]->message)[i]);
    	}
    }


    printf("\n");
    return result;
}