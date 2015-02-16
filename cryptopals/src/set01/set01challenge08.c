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
    int highestNumberOfMatchingBlocks = 0;

    // Split the file using newlines as delimiters and test each string.s
    char *currentLine = strtok(fileMapping, "\n");
    int lineNumber = 0;
    while (currentLine){
    	int lineLength = strlen(currentLine);
    	char **currentLineBlocks = divideDataIntoBlocks(currentLine, lineLength, 16);

    	int currentLineMatchingBlocks = 0;
    	int numberOfBlocks = lineLength / 16;
    	for(int i=0; i<numberOfBlocks; i++){			
	    	for(int j=(i+1); j<numberOfBlocks; j++){
	    		if(!(strcmp(currentLineBlocks[i], currentLineBlocks[j]))){
		    		currentLineMatchingBlocks++;
	    		}
	    	}
    	}

    	if(currentLineMatchingBlocks > highestNumberOfMatchingBlocks){
    		highestNumberOfMatchingBlocks = currentLineMatchingBlocks;
    		result = calloc(lineLength + 1, sizeof(char));
    		strncpy(result, currentLine, lineLength);
    	}

    	for(int i=0; i<numberOfBlocks; i++){
    		free(currentLineBlocks[i]);
    	}
		free(currentLineBlocks);

        currentLine = strtok(NULL, "\n");
        lineNumber++;
    }

    // Free resources we no longer need and return the result.
    munmap(fileMapping, fileSize);
    close(stringFileFD);
    return result;
}
