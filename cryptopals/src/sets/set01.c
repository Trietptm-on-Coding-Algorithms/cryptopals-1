#include "set01.h"

/**
  * Matasano Crypto Challenge Solution
  * Set: 01, Challenge 01: Convert Hex to Base64
  *
  * Coded by rot0x1a, 08 Feb 2015
  */
char *solveSet1Challenge01(char *hexString){
    char *result = NULL;

    // Check for invalid arguments.
    if(!hexString || strlen(hexString) < 1){
        printf("Error: solveSet1Challenge01 input is NULL or empty.\n");
        return result;
    } else if (strlen(hexString) % 2) {
        printf("Error: solveSet1Challenge01 input is not byte aligned.\n");
        return result;
    }

    // The number of bytes represented by the data is half the string length since 2 characters represents one byte.
    int numberOfBytes = strlen(hexString) / 2;

    // Load the hex into memory as data.
    char *dataLocation = decodeHex(hexString);
    if(!dataLocation) {
        printf("Error: hexToBase64 failed to load hex into memory.\n");
        return result;
    }

    // Get the base64 representation of data we stored in memory.
    result = encodeBase64(dataLocation, numberOfBytes);
    if(!result) {
        printf("Error: hexToBase64 failed to get base64 encoding of data.\n");
        free(dataLocation);
        return result;
    }

    // Free memory we no longer need and return the result.
    free(dataLocation);
    return result;
}


/**
  * Matasano Crypto Challenge Solution
  * Set: 01, Challenge 02: Fixed XOR
  *
  * Coded by rot0x1a, 09 Feb 2015
  */
char *solveSet1Challenge02(char *hexStringOne, char *hexStringTwo) {
    char *result = NULL;

    // Check for invalid arguments.
    if(!hexStringOne || strlen(hexStringOne) < 1){
        printf("Error: solveSet1Challenge02 hexStringOne input is NULL or empty.\n");
        return result;
    } else if(!hexStringTwo || strlen(hexStringTwo) < 1){
        printf("Error: solveSet1Challenge02 hexStringTwo input is NULL or empty.\n");
        return result;
    } else if (strlen(hexStringOne) % 2) {
        printf("Error: solveSet1Challenge02 hexStringOne input is not byte aligned.\n");
        return result;
    } else if (strlen(hexStringOne) != strlen(hexStringTwo)){
        printf("Error: solveSet1Challenge02 input lengths do not match.\n");
        return result;
    }

    // Load the first hex string into memory as data.
    char *dataBlockOne = decodeHex(hexStringOne);
    if(!dataBlockOne){
        printf("Error: solveSet1Challenge02 unable to load hexStringOne into memory.\n");
        return result;
    }

    // Load the second hex string into memory as data.
    char *dataBlockTwo = decodeHex(hexStringTwo);
    if(!dataBlockTwo){
        printf("Error: solveSet1Challenge02 unable to load hexStringTwo into memory.\n");
        free(dataBlockOne);
        return result;
    }

    // XOR the data
    char *xorResult = xorDataBlock(dataBlockOne, (strlen(hexStringOne) / 2), dataBlockTwo, (strlen(hexStringTwo) / 2));
    if(!xorResult){
        printf("Error: solveSet1Challenge02 unable to read memory into hex string.\n");
        free(dataBlockTwo);
        free(dataBlockOne);
        return result;
    }

    // Retrieve the result as hex for displaying.
    result = encodeHex(xorResult, strlen(hexStringOne)/2);
    if(!result){
        printf("Error: solveSet1Challenge02 unable to read memory into hex string.\n");
        free(xorResult);
        free(dataBlockTwo);
        free(dataBlockOne);
        return result;
    }

    // Free memory we no longer need and return the result.
    free(xorResult);
    free(dataBlockTwo);
    free(dataBlockOne);
    return result;
}


/**
  * Matasano Crypto Challenge Solution
  * Set: 01, Challenge 03: Single-byte XOR cipher
  *
  * Coded by rot0x1a, 09 Feb 2015
  */
xorDecryptedMessage *solveSet1Challenge03(char *hexString) {
    xorDecryptedMessage *result = NULL;

    // Check for invalid arguments.
    if(!hexString || strlen(hexString) < 1){
        printf("Error: solveSet1Challenge03 input is NULL or empty.\n");
        return result;
    } else if (strlen(hexString) % 2) {
        printf("Error: solveSet1Challenge03 input is not byte aligned.\n");
        return result;
    }

    // Load the hex into memory as data.
    char *dataLocation = decodeHex(hexString);
    if(!dataLocation) {
        printf("Error: hexToBase64 failed to load hex into memory.\n");
        return result;
    }

    // The number of bytes represented by the data is half the string length since 2 characters represents one byte.
    int numberOfBytes = strlen(hexString) / 2;

    // Decrypt.
    result = xorDecrypt(dataLocation, numberOfBytes, 1);
    if(!result){
        printf("Error: Could not decrypt hex string.\n");
        free(dataLocation);
        return result;
    }
    
    // Free memory we no longer need and return the result.
    free(dataLocation);
    return result;
}


/**
  * Matasano Crypto Challenge Solution
  * Set: 01, Challenge 04: Detect single-character XOR
  *
  * Coded by rot0x1a, 09 Feb 2015
  */
xorDecryptedMessage *solveSet1Challenge04(char *fileName) {
    xorDecryptedMessage *result = NULL;
    
    // Check for invalid arguments.
    if(!fileName || strlen(fileName) < 1){
        printf("Error: solveSet1Challenge04 input is NULL or empty.\n");
        return result;
    }

    // Attempt to open the file provided.
    int stringFileFD = open(fileName, O_RDONLY);
    if(stringFileFD < 0){
        printf("Error: solveSet1Challenge04 failed to open file.\n");
        return result;
    }

    // Get the size of the file.
    struct stat sb;
    fstat(stringFileFD, &sb);
    size_t fileSize = sb.st_size;

    // Map the file into memory.
    char *fileMapping = mmap(NULL, fileSize, PROT_READ | PROT_WRITE, MAP_PRIVATE, stringFileFD, 0);
    if(fileMapping == MAP_FAILED){
        printf("Error: solveSet1Challenge04 failed to map file into memory.\n");
        close(stringFileFD);
        return result;
    }

    // Keep track of our most confident response, gauged by the highest number of ASCII matches.
    result = malloc(sizeof(xorDecryptedMessage));
    if(!result){
        printf("Error: solveSet1Challenge04 failed to allocate memory for result.\n");
        munmap(fileMapping, fileSize);
        close(stringFileFD);
        return result;
    }
    result->score = 0;
    result->key = NULL;
    result->message = NULL;

    // Split the file using newlines as delimiters and test each string.s
    char *currentEncryptedString = strtok(fileMapping, "\n");
    while (currentEncryptedString){

        // The number of bytes represented by the data is half the string length since 2 characters represents one byte.
        int numberOfBytes = strlen(currentEncryptedString) / 2;

        char *encryptedData = decodeHex(currentEncryptedString);
        if(!encryptedData){
            printf("Error: solveSet1Challenge04 failed to load hex into memory.\n");
            continue;
        }

        xorDecryptedMessage *currentDecryptedMessage = xorDecrypt(encryptedData, numberOfBytes, 1);
        if(!currentDecryptedMessage){
            printf("Error: solveSet1Challenge04 failed to decrypt string.\n");
            free(encryptedData);
            currentEncryptedString = strtok(NULL, "\n");
            continue;
        }

        // If this decrypted string contains more matches than the previous best, save it and the key.
        if(result->score < currentDecryptedMessage->score){

            result->score = currentDecryptedMessage->score;

            // If we had a previous best match for the key, we can free it now.
            if(result->key != NULL){
                free(result->key);
                result->key = NULL;
            }
            result->key = currentDecryptedMessage->key;

            // If we had a previous best match for the message, we can free it now.
            if(result->message != NULL){
                free(result->message);
                result->message = NULL;
            }
            result->message = currentDecryptedMessage->message;

        } else {
            free(currentDecryptedMessage->key);
            free(currentDecryptedMessage->message);
        }

        // Clean up this round and prepare for the next.
        free(encryptedData);
        free(currentDecryptedMessage);
        currentEncryptedString = strtok(NULL, "\n");
    }

    // Free resources we no longer need and return the result.
    munmap(fileMapping, fileSize);
    close(stringFileFD);
    return result;
}


/**
  * Matasano Crypto Challenge Solution
  * Set: 01, Challenge 05: Implement repeating-key XOR
  *
  * Coded by rot0x1a, 10 Feb 2015
  */
char *solveSet1Challenge05(char *message, char *key){
    char *result = NULL;
    
    // Check for invalid arguments.
    if(!message || strlen(message) < 1){
        printf("Error: solveSet1Challenge04 message input is NULL or empty.\n");
        return result;
    } else if(!key || strlen(key) < 1){
        printf("Error: solveSet1Challenge04 key input is NULL or empty.\n");
        return result;
    }

    // XOR the data.
    char *xorResult = xorDataBlock(message, strlen(message), key, strlen(key));
    if(!xorResult){
        printf("Error: solveSet1Challenge05 could not XOR the message.\n");
        return result;
    }

    // Get the hex representing the data.
    result = encodeHex(xorResult, strlen(message));
    if(!result){
        printf("Error: solveSet1Challenge05 could get memory as hex.\n");
        free(xorResult);
        return result;
    }

    // Free memory we no longer need and return the result.
    free(xorResult);
    return result;
}


/**
  * Matasano Crypto Challenge Solution
  * Set: 01, Challenge 06: Break repeating-key XOR
  *
  * Coded by rot0x1a, 10 Feb 2015
  */
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
            if(bytesWritten < base64DecodedDataSize){
                *(result + bytesWritten) = (decryptedBlocks[j]->message)[i];
                bytesWritten++;
            }
        }
    }

    // TODO: Why is this needed?
    result[bytesWritten - 1] = '\x00';

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


/**
  * Matasano Crypto Challenge Solution
  * Set: 01, Challenge 06: AES in ECB mode
  *
  * Coded by rot0x1a, 16 Feb 2015
  */
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


/**
  * Matasano Crypto Challenge Solution
  * Set: 01, Challenge 08: Detect AES in ECB mode
  *
  * Coded by rot0x1a, 16 Feb 2015
  */
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
