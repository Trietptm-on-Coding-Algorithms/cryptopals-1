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

    int base64DecodedDataSize = (strlen(fileMapping) / 3) * 4;
    int keySize = -1;
    int bestNormalized = -1;
    int maxKeyLength = ((base64DecodedDataSize / 2) < 40) ? (base64DecodedDataSize/2) : 40; 

    for(int i=2; i<=maxKeyLength; i++){
    	char *blockOne = calloc(sizeof(char) * (i + 1), sizeof(char));
    	strncpy(blockOne, base64DecodedData, i);

    	char *blockTwo = calloc(sizeof(char) * (i + 1), sizeof(char));
    	strncpy(blockTwo, (base64DecodedData + i), i);

    	int hammingDistance = computeHammingDistance(blockOne, blockTwo, i);
    	int normalized = hammingDistance/i;

    	if(keySize < 0 || bestNormalized < -1){
    		keySize = i;
    		bestNormalized = normalized;
    	} else if (normalized < bestNormalized){
    		keySize = i;
    		bestNormalized = normalized;
    	}
    }

 	printf("Winning keySize %d\n", keySize);

    int numTransposedBlocks = keySize;
    int transposedBlockLength = base64DecodedDataSize / keySize;

    char **transposedBlocks = calloc(numTransposedBlocks, sizeof(char*));
    for(int i=0; i<numTransposedBlocks; i++){
    	transposedBlocks[i] = calloc(transposedBlockLength + 1, sizeof(char));
    }

    for(int i=0; i<numTransposedBlocks; i++){
    	for(int j=0; j<transposedBlockLength; j++){
      	    transposedBlocks[i][j] = (base64DecodedData + i)[j];
    	}
    }

    for(int i=0; i<numTransposedBlocks; i++){
	    xorDecryptedMessage *decryptResult = xorDecrypt(transposedBlocks[i], transposedBlockLength, 1);
	    printf("\ndecryptResult:\n");
	    printf("score: %f\n", decryptResult->score);
	    printf("key: %s\n", decryptResult->key);
	    printf("message: %s\n", decryptResult->message);
    }


    char *stringOne = "this is a test";
    char *stringTwo = "wokka wokka!!!";
    printf("Hamming Distance: %d\n", computeHammingDistance(stringOne, stringTwo, strlen(stringOne)));


    free(base64DecodedData);

    return result;
}