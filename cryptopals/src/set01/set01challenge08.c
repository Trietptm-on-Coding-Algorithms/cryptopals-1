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

    // Keep track of the number of matching blocks in the winning line.
    int highestNumberOfMatchingBlocks = 0;

    // Split the file using newlines as delimiters and test each string.
    char *currentLine = strtok(fileMapping, "\n");
    while (currentLine){
    	int lineLength = strlen(currentLine);
    	char **currentLineBlocks = divideDataIntoBlocks(currentLine, lineLength, 16);
    	if(!currentLineBlocks){
	        printf("Error: solveSet1Challenge08 failed to divideDataIntoBlocks.\n");
	        munmap(fileMapping, fileSize);
	        close(stringFileFD);
	        return result;
    	}

    	// Determine how many matching blocks are in this line.
    	int currentLineMatchingBlocks = 0;
    	int numberOfBlocks = lineLength / 16;
    	for(int i=0; i<numberOfBlocks; i++){			
	    	for(int j=(i+1); j<numberOfBlocks; j++){
	    		if(!(strcmp(currentLineBlocks[i], currentLineBlocks[j]))){
		    		currentLineMatchingBlocks++;
	    		}
	    	}
    	}

    	// If this line has more matching blocks than the previous best.
    	if(currentLineMatchingBlocks > highestNumberOfMatchingBlocks){
    		highestNumberOfMatchingBlocks = currentLineMatchingBlocks;

    		// If a less-qualified result was found, free it.
    		if(result != NULL){
    			free(result);
    			result = NULL;
    		}

    		// Copy the winning line into the result.
    		result = calloc(lineLength + 1, sizeof(char));
    		if(!result){
		        printf("Error: solveSet1Challenge08 failed to allocate memory for the result.\n");
		    	for(int i=0; i<numberOfBlocks; i++){
		    		free(currentLineBlocks[i]);
		    	}
				free(currentLineBlocks);
		        munmap(fileMapping, fileSize);
		        close(stringFileFD);
		        return result;
    		}
    		strncpy(result, currentLine, lineLength);
    	}

    	// Free all resources we no longer need in this iteration.
    	for(int i=0; i<numberOfBlocks; i++){
    		free(currentLineBlocks[i]);
    	}
		free(currentLineBlocks);

		// Continue to the next line.
        currentLine = strtok(NULL, "\n");
    }

    // Free resources we no longer need and return the result.
    munmap(fileMapping, fileSize);
    close(stringFileFD);
    return result;
}
