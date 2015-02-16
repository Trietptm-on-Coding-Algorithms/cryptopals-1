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

    int base64DecodedDataSize =  (strlen(fileMapping) / 4) * 3;

    // Load the base64 encoded data into memory.
    char *base64DecodedData = decodeBase64(fileMapping);
    if (!base64DecodedData){
        printf("Error: solveSet1Challenge06 failed to decode base64 data.\n");
        munmap(fileMapping, fileSize);
        return result;    	
    }


    /*************************** ACTUAL BREAKING ********************/

    char *stringOne = "this is a test";
	char *stringTwo = "wokka wokka!!!";
	int stringLength = strlen(stringOne);
	int sanityCheck = (computeHammingDistance(stringOne, stringTwo, stringLength) == 37);
	if(!sanityCheck){
		printf("Failed computeHammingDistance sanityCheck. Quitting.\n\n");
		exit(-1);
	}


	int maxKeySize = 40;
	float hammingAverages[maxKeySize];
	for(int i=0; i<maxKeySize; i++){
		hammingAverages[i] = 0.0;
	}

	// Take as many samples as we can
	int numSamples = (base64DecodedDataSize - maxKeySize) / 2;
	for(int i=0; i<numSamples; i++){

		// Add the normalized samples together:
		for(int j=2; j<maxKeySize; j++){
			char *dataStart = base64DecodedData + i;
			int hammingDistance = computeHammingDistance(dataStart, dataStart + j, j);
			float normalized = (float)hammingDistance / (float)j;
			hammingAverages[j] += normalized;
		}

	}

	int keySize = -1;
	int lowestNormalized = -1;
	for(int i =2; i<maxKeySize; i++){
		hammingAverages[i] /= numSamples;
		if(lowestNormalized < 0 || hammingAverages[i] < lowestNormalized){
			keySize = i;
			lowestNormalized = hammingAverages[i];
		}
	}
 	printf("numSamples: %d\n", numSamples);
	printf("keySize: %d\n", keySize);
	printf("normalized=%f\n", hammingAverages[keySize]);
 	printf("\n");


    // Divide the data into blocks and transpose them.
    int numColumns = keySize;
    int numRows = 1 + (base64DecodedDataSize / keySize);
    char **dataInBlocks = divideDataIntoBlocks(base64DecodedData, base64DecodedDataSize, keySize);
    char **transposedData = transposeBlocks(dataInBlocks, numColumns, numRows);

    xorDecryptedMessage **decryptedBlocks = calloc(sizeof(char *) * keySize, sizeof(char));
    for(int i=0; i<keySize; i++){
    	decryptedBlocks[i] = xorDecrypt(transposedData[i], numRows, 1);
    }

    for(int i=0; i<numRows; i++){
    	for(int j=0; j<numColumns; j++){
			printf("%c", (decryptedBlocks[j]->message)[i]);
    	}
    }
 	printf("\n");

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
    return result;
}