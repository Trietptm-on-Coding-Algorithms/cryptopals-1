#include "cryptopals-common.h"

char *loadHexStringToMemory(char *hexString){
    char *result = NULL;

    // Check that input is valid hex.
    if (!isValidHexadecimalString(hexString)){
        printf("Error: loadHexStringToMemory input is not valid hexadecimal.\n");
        return result;
    }

    // Number of bytes needed is half the string length since 2 characters is one byte.
    int numberOfBytes = strlen(hexString) / 2;

    // TODO: Figure out why we cannot allocate half the length without breaking challenge 4. Allocate full string length for now.
    // result = calloc(numberOfBytes + 1, sizeof(char));
    result = calloc(strlen(hexString) + 1, sizeof(char));
    if (!result){
        printf("Error: loadHexStringToMemory could not allocate memory for the result.\n");
        return result;
    }    

    // Copy the hex string characters into memory as raw data.
    for(int i = 0; i < numberOfBytes; i++){
        sscanf(hexString + (2 * i), "%2hhx", &result[i]);
    }

    // Return the memory address where we loaded the hex data.
    return result;
}


char *loadMemoryToHexString(char *data, int numberOfBytes){
    char *result = NULL;

    // Check for invalid arguments.
    if (!data){
        printf("Error: loadMemoryToHexString data input is null.\n");
        return result;
    } else if (numberOfBytes < 1){
        printf("Error: loadMemoryToHexString numberOfBytes input is less than one.");
        return result;
    }

    // The result string will be numberOfBytes * 2 since it takes two hex characters to represent a byte.
    result = calloc((numberOfBytes * 2) + 1, sizeof(char));
    if (!result){
        printf("Error: loadMemoryToHexString could not allocate memory for the result.\n");
        return result;
    }

    // Copy the contents of memory into the result as hex characters.
    for(int i = 0; i < numberOfBytes; i++){
        sprintf(result + (2 * i), "%02x", (unsigned char)data[i]);
    }

    // Return the contents of the memory address as a hexadecimal string.
    return result;
}


char *base64Encode(char *data, int dataLength){
    char *result = NULL;

    // Check for invalid arguments.
    if (!data){
        printf("Error: base64Encode data input is NULL.\n");
        return result;
    } else if (dataLength < 1){
        printf("Error: base64Encode dataLength input is less than one.\n");
        return result;
    }

    // For every 3 bytes of data, we need 4 characters to represent it.
    int numberOfBytes = ((dataLength * 3) / 4) * 2;

    // If the number of bytes is not a multiple of three, obtain memory for padding characters.
    numberOfBytes += (dataLength % 3) * 2;

    // Allocate the memory to store the result and the null terminator. 
    result = calloc(numberOfBytes + 1, sizeof(char));
    if (!result){
        printf("Error: base64Encode Could not allocate memory for the result.\n");
        return result;
    }    

    // Base64 encode the data, 24 bytes at a time.
    int numWrote = 0;
    for(int i=0; i<dataLength; i+=3){

        // Load the next 24 bit chunk of data to encode.
        unsigned int currentChunk = 0;
        currentChunk = currentChunk | (data[i + 0]  << 16); // Load bits [23, 22, 21, 20, 19, 18, 17, 16]
        currentChunk = currentChunk | (data[i + 1]  <<  8); // Load bits [15, 14, 13, 12, 11, 10,  9,  8]
        currentChunk = currentChunk | (data[i + 2]  <<  0); // Load bits [ 7,  6,  5,  4,  3,  2,  1,  0]

        // Divide the 24 bits we loaded in currentChunk into 4 6-bit blocks.
        unsigned int block1 = (currentChunk & 0xFC0000) >> 18;  // block1 consists of bits: [23, 22, 21, 20, 19, 18]
        unsigned int block2 = (currentChunk & 0x03F000) >> 12;  // block2 consists of bits: [17, 16, 15, 14, 13, 12]
        unsigned int block3 = (currentChunk & 0x000FC0) >>  6;  // block3 consists of bits: [11, 10,  9,  8,  7,  6]
        unsigned int block4 = (currentChunk & 0x00003F) >>  0;  // block4 consists of bits: [ 5,  4,  3,  2,  1,  0]

        // Append the base64 character representing each block to the end of the result.
        strncpy(result + numWrote++, &BASE64_ENCODING_VALUES[block1], sizeof(char)); // Copy base64 encoding of block 1
        strncpy(result + numWrote++, &BASE64_ENCODING_VALUES[block2], sizeof(char)); // Copy base64 encoding of block 2
        strncpy(result + numWrote++, &BASE64_ENCODING_VALUES[block3], sizeof(char)); // Copy base64 encoding of block 3
        strncpy(result + numWrote++, &BASE64_ENCODING_VALUES[block4], sizeof(char)); // Copy base64 encoding of block 4
    }

    // If the original data was not a multiple of 3 bytes, we will pad the rest with the "=" character
    int remainingBytes = dataLength % 3;
    if (remainingBytes == 1){
        strncpy(result + numWrote - 2, "==", sizeof(char) * 3);
    } else if (remainingBytes == 2){
        strncpy(result + numWrote - 1, "=", sizeof(char) * 2);
    }

    // Return the contents of the memory address as a hexadecimal string.
    return result;
}


char *base64Decode(char *base64String){
    char *result = NULL;

    // Check that we received valid base64 data.
    if (isValidBase64String(base64String)){
        printf("Error: base64Decode input is not valid base64.\n");
        return result;
    }

    // TODO: Implement me!
    printf("NOT YET IMPLEMENTED\n");

    return result;
}


int isValidHexadecimalString(char *hexString){
    int result = 0;

    // Check for NULL or empty String
    if (!hexString || strlen(hexString) < 1){
        printf("Error: isValidHexadecimalString input is NULL or empty.\n");
        return result;
    }

    // Check byte-alignment.
    int hexStringLength = strlen(hexString);
    if (hexStringLength % 2){
        printf("Error: isValidHexadecimalString input length is not a multiple of 2.\n");
        return result;
    }

    // Check for non-hexadecimal characters.
    for(int i=0; i<hexStringLength; i++){
        int isNumber = (hexString[i] >= '0') && ('9' >= hexString[i]);
        int isLowerCase = (hexString[i] >= 'a') && ('f' >= hexString[i]);
        int isUpperCase = (hexString[i] >= 'A') && ('F' >= hexString[i]);
        if (!isNumber && !isLowerCase && !isUpperCase){
            printf("Error: isValidHexadecimalString input contains non-hexadecimal character [%c].\n", hexString[i]);
            return result;
        }
    }

    // We passed all tests.
    result = 1;
    return result;
}


int isValidBase64String(char *base64String){
    int result = 0;

    // Check for invalid arguments.
    if (!base64String || strlen(base64String) < 1){
        printf("Error: base64Decode input is NULL or empty.\n");
        return result;
    }

    // Check byte-alignment.
    int base64StringLength = strlen(base64String);
    if (base64StringLength % 3){
        printf("Error: base64Decode input length is not a multiple of 3.\n");
        return result;
    }

    // Check for non-base64 characters.
    for(int i=0; i<base64StringLength; i++){
        int isNumber        = (base64String[i] >= '0') && ('9' >= base64String[i]);
        int isLowerCase     = (base64String[i] >= 'a') && ('z' >= base64String[i]);
        int isUpperCase     = (base64String[i] >= 'A') && ('Z' >= base64String[i]);
        int isSpecialChar   = (base64String[i] >= '+') && ('/' >= base64String[i]);
        int isbadEquals     = (base64String[i] == '=') && (('\0' != base64String[i+1] || base64String[i+2] != '\0'));

        if (!isNumber && !isLowerCase && !isUpperCase && !isSpecialChar && !isbadEquals){
            printf("Error: isValidBase64String input contains non-base64 character [%c].\n", base64String[i]);
            return result;
        }
    }

    // We passed all tests.
    result = 1;
    return result;
}


/************* Needs to be revisited and updated ***************/


char *xorDataBlock(char *dataBlock, char *xorKey, int dataBlockLength){
    char *result = NULL;

    // Check for invalid arguments.
    if (!dataBlock){
        printf("Error: xorDataBlock dataBlock input is NULL.\n");
        return result;        
    } else if (!xorKey || strlen(xorKey) < 1){
        printf("Error: xorDataBlock xorKey input is NULL or empty.\n");
        return result;
    } else if (dataBlockLength < 1){
        printf("Error: xorDataBlock dataBlockLength input is less than one.\n");
        return result;
    }

    // TODO: Do we need this?
    // Verify the data block length is an even length.
    dataBlockLength += (dataBlockLength % 2);
    
    result = calloc(dataBlockLength + 1, sizeof(char));
    if (!result){
        printf("Error: xorDataBlocks Could not allocate memory.\n");
        return result;
    }    

    int xorKeyLength = strlen(xorKey);

    // For each byte of the data, XOR it with the repeating key's next byte and append it to the result.
    for(int i=0; i<dataBlockLength/2; i++){
        unsigned char dataBlockByte = dataBlock[i];
        unsigned char xorKeyByte = xorKey[i % xorKeyLength];
        unsigned char xorResult = dataBlockByte ^ xorKeyByte;
        sprintf(result + (2 * i), "%02x", xorResult);
    }
    return result;
}


xorDecryptedMessage *decryptHexStringUsingXOR(char *cipherText, int keyLength){
    xorDecryptedMessage *result = NULL;

    // Check for invalid arguments.
    if (!cipherText || strlen(cipherText) < 1 || keyLength < 1){
        printf("Error: decryptHexStringUsingXOR returning NULL due to bad arguments.\n");
        return result;
    } else if (strlen(cipherText) % 2){
        printf("Error: decryptHexStringUsingXOR received odd ciphertext string. Must be even number of hex characters.\n");
        return result;
    }

    // Get the number of characters in the hex string and the decoded message.
    int numberOfHexCharacters = strlen(cipherText);
    int messageLength = (numberOfHexCharacters / 2);

    // Allocate memory for the result struct, the key, and the decoded message.
    result = calloc(sizeof(xorDecryptedMessage), sizeof(char));
    if (!result){
        printf("Error: decryptHexStringUsingXOR Could not obtain memory for result struct.\n");        
        return result;
    }

    result->key = calloc(sizeof(char) * (keyLength + 1), sizeof(char));
    if (!result->key){
        printf("Error: decryptHexStringUsingXOR Could not obtain memory for result key.\n");
        free(result);
        result = NULL;
        return result;
    }

    result->message = calloc(sizeof(char) * (messageLength + 1), sizeof(char));
    if (!result->message){
        printf("Error: decryptHexStringUsingXOR Could not obtain memory for result message.\n");
        free(result->key);
        free(result);
        result = NULL;
        return result;
    }

    // Load the hex string into memory so we can work with it as raw data.
    char *cipheredString = loadHexStringToMemory(cipherText);
    if (!cipheredString){
        printf("Error: decryptHexStringUsingXOR Could not load hex string into memory.\n");
        free(result->message);
        free(result->key);
        free(result);
        result = NULL;
        return result;
    }

    // Check all common ASCII characters as the key.
    char *keyBuffer = calloc(sizeof(char) * (keyLength + 1), sizeof(char));
    if (!keyBuffer){
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


void checkAllKeyCombinations(xorDecryptedMessage* result, char *cipherText, int messageLength, char *keyBuffer, int index, int keyLength){
    
    // If the key is the desired length, print it and return.
    if (index >= keyLength){
        keyBuffer[keyLength] = '\0';

        // XOR the cipher string and our key string together and free the keyString.
        char *xorResult = xorDataBlock(cipherText, keyBuffer, ((messageLength * 2) + 1));
        if (!xorResult){
            printf("Error: checkAllKeyCombinations Could not XOR datablocks.\n");
            return;
        }

        // Load the XOR'ed data into memory so we can treat it like a string.
        char *xorResultInMemory = loadHexStringToMemory(xorResult);
        if (!xorResultInMemory){
            printf("Error: checkAllKeyCombinations Could not load XOR result into memory.\n");
            free(xorResult);
            return;
        }
        free(xorResult);

        // Count how many spaces and English alphabet ASCII characters are in the decoded string.
        int thisScore = 0;
        for(int j=0; j<(messageLength * 2); j++){
            if (('A' <= xorResultInMemory[j] && xorResultInMemory[j] <= 'z') || xorResultInMemory[j] == ' '){
                thisScore++;
            }
        }

        // If this decrypted string scores higher than the previous best, save it and the key.
        if (thisScore > result->score){
            result->score = thisScore;
            strncpy(result->key, keyBuffer, keyLength);
            strncpy(result->message, (const char *)xorResultInMemory, messageLength);
        }
        free(xorResultInMemory);
        return;

    // If the key is not long enough, add the character loop.
    } else {
        for (char i=' '; i<='}'; i++){
            keyBuffer[index] = i;
            checkAllKeyCombinations(result, cipherText, messageLength, keyBuffer, index + 1, keyLength);
        }
    }
}


int computeHammingDistance(char *stringOne, char *stringTwo){
    int result = -1;

    if (!stringOne || !stringTwo || strlen(stringOne) < 1 || strlen(stringTwo) < 1){
        printf("Error: computeHammingDistance received null or empty arguments.\n");
        return result;
    }

    int stringLength = strlen(stringOne);
    if (stringLength != strlen(stringTwo)){
        printf("Error: computeHammingDistance arguments must be same length.\n");
        return result;
    }

    result = 0;
    for(int i=0; i<stringLength; i++){
        char *xorResult = xorDataBlock(stringOne + i, stringTwo + i, sizeof(char)); 
        char *xorResultInMemory = loadHexStringToMemory(xorResult);

        for(int j=0; j<8; j++){
            int isBitSet = ((xorResultInMemory[0] >> j) % 2) ? 1 : 0;
            result += isBitSet;
        }

        free(xorResultInMemory);
        free(xorResult);
    }
    return result;
}


