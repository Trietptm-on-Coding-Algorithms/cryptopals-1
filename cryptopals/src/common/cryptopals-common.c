#include "cryptopals-common.h"

char *loadHexStringToMemory(char *hexString){
    char *result = NULL;

    // Check for invalid arguments.
    if(!hexString || !strlen(hexString)){
        printf("Error: loadHexStringToMemory returning NULL due to bad arguments.\n");
        return result;
    }

    // If the hex string is of odd length, prepend a zero.
    int hexStringLength = strlen(hexString);
    if(hexStringLength % 2) {
        printf("Error: loadHexStringToMemory passed hex string of odd length.\n");
        return result;
    }

    char *validHexString = calloc(hexStringLength, sizeof(char));
    if(!validHexString){
        printf("Error: loadHexStringToMemory could not allocate memory.\n");
        return result;
    }

    strncpy(validHexString, hexString, hexStringLength);
    char *validHexStringPtr = validHexString;
    hexStringLength = strlen(validHexString);

    // Obtain memory for storing the result.
    result = calloc(hexStringLength + 1, sizeof(char));  
    if(!result){
        printf("Error: loadHexStringToMemory could not allocate memory.\n");
        return result;
    }    

    // Copy the hex string characters into memory as raw data.
    for(int i = 0; i < hexStringLength/2; i++) {
        sscanf(validHexStringPtr, "%2hhx", &result[i]);
        validHexStringPtr += 2;
    }

    // Clean up the mess we made and return.
    free(validHexString);
    return result;
}


char *base64Encode(char *data, int dataLength){
    char *result = NULL;

    // Check for invalid arguments.
    if(!data || dataLength < 1){
        printf("Error: base64Encode returning NULL due to bad arguments.\n");
        return result;
    }

    // Determine the size of memory needed to store the result and allocate it.
    int resultSize = dataLength * 2;
    result = calloc(resultSize + 1, sizeof(char));
    if(!result){
        printf("Error: base64Encode Could not allocate memory.\n");
        return result;
    }    

    // Base64 encode the data, 24 bytes at a time.
    int numWrote = 0;
    for(int i=0; i<dataLength; i+=3){

        // Load the next 24 bit chunk of data to encode into currentChunk.
        unsigned int currentChunk = 0;
        currentChunk = currentChunk | (data[i + 0]  << 16); // Load bits [23, 22, 21, 20, 19, 18, 17, 16]
        currentChunk = currentChunk | (data[i + 1]  <<  8); // Load bits [15, 14, 13, 12, 11, 10,  9,  8]
        currentChunk = currentChunk | (data[i + 2]  <<  0); // Load bits [ 7,  6,  5,  4,  3,  2,  1,  0]

        // Divide the 24 bits we loaded in currentChunk into 4 6-bit blocks.
        unsigned int block1 = (currentChunk & 0xFC0000) >> 18;  // block1 consists of bits: [23, 22, 21, 20, 19, 18]
        unsigned int block2 = (currentChunk & 0x03F000) >> 12;  // block2 consists of bits: [17, 16, 15, 14, 13, 12]
        unsigned int block3 = (currentChunk & 0x000FC0) >>  6;  // block3 consists of bits: [11, 10,  9,  8,  7,  6]
        unsigned int block4 = (currentChunk & 0x00003F) >>  0;  // block4 consists of bits: [ 5,  4,  3,  2,  1,  0]

        // Append the base64 character representing each block onto the result.
        strncpy(result + numWrote++, &BASE64_ENCODING_VALUES[block1], sizeof(char)); // Copy base64 encoding of block 1
        strncpy(result + numWrote++, &BASE64_ENCODING_VALUES[block2], sizeof(char)); // Copy base64 encoding of block 2
        strncpy(result + numWrote++, &BASE64_ENCODING_VALUES[block3], sizeof(char)); // Copy base64 encoding of block 3
        strncpy(result + numWrote++, &BASE64_ENCODING_VALUES[block4], sizeof(char)); // Copy base64 encoding of block 4
    }

    // If the original data was not a multiple of 3 bytes, we will pad the rest with the "=" character
    int remainingBytes = dataLength % 3;
    if (remainingBytes == 1) {
        strncpy(result + numWrote - 2, "==", sizeof(char) * 3);
    } else if (remainingBytes == 2) {
        strncpy(result + numWrote - 1, "=", sizeof(char) * 2);
    }

    return result;
}


char *xorDataBlock(char *dataBlock, char *xorKey, int dataBlockLength) {
    char *result = NULL;

    // Check for invalid arguments.
    if(!dataBlock || !xorKey){
        printf("Error: xorDataBlocks returning NULL due to bad arguments.\n");
        return result;
    }

    int xorKeyLength = strlen((char *)xorKey);
    result = calloc(dataBlockLength + 1, sizeof(char));
    if(!result){
        printf("Error: xorDataBlocks Could not allocate memory.\n");
        return result;
    }    

    for(int i=0; i<dataBlockLength/2; i++){
        char smallBlockOne = dataBlock[i];
        char smallBlockTwo = xorKey[i % xorKeyLength];
        sprintf(result + (2 * i), "%02x", smallBlockOne ^ smallBlockTwo);
    }
    return result;
}


xorDecryptedMessage *decryptHexStringUsingXOR(char *cipherText, int keyLength){
    xorDecryptedMessage *result = NULL;

    // Check for invalid arguments.
    if(!cipherText || strlen(cipherText) < 1 || keyLength < 1){
        printf("Error: decryptHexStringUsingXOR returning NULL due to bad arguments.\n");
        return result;
    } else if (strlen(cipherText) % 2){
        printf("Error: decryptHexStringUsingXOR received odd ciphertext string. Must be even number of hex characters.\n");
        return result;
    }

    // Get the number of characters in the hex string and the decoded message.
    int numberOfHexCharacters = strlen(cipherText);
    int messageLength = numberOfHexCharacters / 2;

    // Allocate memory for the result struct, the key, and the decoded message.
    result = calloc(sizeof(xorDecryptedMessage), sizeof(char));
    if(!result){
        printf("Error: decryptHexStringUsingXOR Could not obtain memory for result struct.\n");        
        return result;
    }

    result->key = calloc(sizeof(char) * (keyLength + 1), sizeof(char));
    if(!result->key){
        printf("Error: decryptHexStringUsingXOR Could not obtain memory for result key.\n");
        free(result);
        result = NULL;
        return result;
    }

    result->message = calloc(sizeof(char) * (messageLength + 1), sizeof(char));
    if(!result->message){
        printf("Error: decryptHexStringUsingXOR Could not obtain memory for result message.\n");
        free(result->key);
        free(result);
        result = NULL;
        return result;
    }

    // Load the hex string into memory so we can work with it as raw data.
    char *cipheredString = loadHexStringToMemory(cipherText);
    if(!cipheredString){
        printf("Error: decryptHexStringUsingXOR Could not load hex string into memory.\n");
        free(result->message);
        free(result->key);
        free(result);
        result = NULL;
        return result;
    }

    // Check all common ASCII characters as the key.
    char *keyBuffer = calloc(sizeof(char) * (keyLength + 1), sizeof(char));
    if(!keyBuffer){
        printf("Error: decryptHexStringUsingXOR Could not obtain memory for key buffer.\n");
        free(cipheredString);
        free(result->message);
        free(result->key);
        free(result);
        result = NULL;
        return result;
    }

    checkAllKeyCombinations(result, cipheredString, messageLength, keyBuffer, 0, keyLength);

    // Clean up and return.
    free(keyBuffer);
    free(cipheredString);
    return result;
}


void checkAllKeyCombinations(xorDecryptedMessage* result, char *cipherText, int messageLength, char *keyBuffer, int index, int keyLength) {
    
    // If the key is the desired length, print it and return.
    if (index >= keyLength) {
        keyBuffer[keyLength] = '\0';

        // XOR the cipher string and our key string together and free the keyString.
        char *xorResult = xorDataBlock(cipherText, keyBuffer, (messageLength * 2));
        if(!xorResult){
            printf("Error: checkAllKeyCombinations Could not XOR datablocks.\n");
        }

        // Load the XOR'ed data into memory so we can treat it like a string.
        char *xorResultInMemory = loadHexStringToMemory(xorResult);
        if(!xorResultInMemory){
            printf("Error: checkAllKeyCombinations Could not load XOR result into memory.\n");
            free(xorResult);
            return;
        }
        free(xorResult);

        // Count how many spaces and English alphabet ASCII characters are in the decoded string.
        int thisMatchCount = 0;
        for(int j=0; j<(messageLength * 2); j++){
            if(('A' <= xorResultInMemory[j] && xorResultInMemory[j] <= 'z') || xorResultInMemory[j] == ' '){
                thisMatchCount++;
            }
        }

        // If this decrypted string contains more matches than the previous best, save it and the key.
        if(thisMatchCount > result->numberOfMatches){
            result->numberOfMatches = thisMatchCount;
            strncpy(result->key, keyBuffer, keyLength);
            strncpy(result->message, (const char *)xorResultInMemory, messageLength);
        }
        free(xorResultInMemory);

        return;

    // If the key is not long enough, add the character loop.
    } else {
        for (char i=' '; i<='}'; i++) {
            keyBuffer[index] = i;
            checkAllKeyCombinations(result, cipherText, messageLength, keyBuffer, index + 1, keyLength);
        }
    }
}