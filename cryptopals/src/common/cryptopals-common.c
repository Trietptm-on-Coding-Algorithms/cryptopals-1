#include "cryptopals-common.h"

int isHex(char *hexString){
    int result = 0;

    // Check for NULL or empty String
    if (!hexString || strlen(hexString) < 1){
        printf("Error: isHex input is NULL or empty.\n");
        return result;
    }

    // Check byte-alignment.
    int hexStringLength = strlen(hexString);
    if (hexStringLength % 2){
        printf("Error: isHex input length is not a multiple of 2.\n");
        return result;
    }

    // Check for non-hexadecimal characters.
    for(int i=0; i<hexStringLength; i++){
        int isNumber = (hexString[i] >= '0') && ('9' >= hexString[i]);
        int isLowerCase = (hexString[i] >= 'a') && ('f' >= hexString[i]);
        int isUpperCase = (hexString[i] >= 'A') && ('F' >= hexString[i]);
        if (!isNumber && !isLowerCase && !isUpperCase){
            printf("Error: isHex input contains non-hexadecimal character [%c].\n", hexString[i]);
            return result;
        }
    }

    // We passed all tests.
    result = 1;
    return result;
}


char *encodeHex(char *data, int numberOfBytes){
    char *result = NULL;

    // Check for invalid arguments.
    if (!data){
        printf("Error: encodeHex data input is null.\n");
        return result;
    } else if (numberOfBytes < 1){
        printf("Error: encodeHex numberOfBytes input is less than one.");
        return result;
    }

    // The result string will be numberOfBytes * 2 since it takes two hex characters to represent a byte.
    result = calloc((numberOfBytes * 2) + 1, sizeof(char));
    if (!result){
        printf("Error: encodeHex could not allocate memory for the result.\n");
        return result;
    }

    // Copy the contents of memory into the result as hex characters.
    for(int i = 0; i < numberOfBytes; i++){
        sprintf(result + (2 * i), "%02x", (unsigned char)data[i]);
    }

    // Return the contents of the memory address as a hexadecimal string.
    return result;
}


char *decodeHex(char *hexString){
    char *result = NULL;

    // Check that input is valid hex.
    if (!isHex(hexString)){
        printf("Error: decodeHex input is not valid hexadecimal.\n");
        return result;
    }

    // Number of bytes needed is half the string length since 2 characters is one byte.
    int numberOfBytes = strlen(hexString) / 2;
    result = calloc(numberOfBytes + 1, sizeof(char));
    if (!result){
        printf("Error: decodeHex could not allocate memory for the result.\n");
        return result;
    }    

    // Copy the hex string characters into memory as raw data.
    for(int i = 0; i < numberOfBytes; i++){
        sscanf(hexString + (2 * i), "%2hhx", &result[i]);
    }

    // Return the memory address where we loaded the hex data.
    return result;
}


int isBase64(char *base64String){
    int result = 0;

    // Check for invalid arguments.
    if (!base64String || strlen(base64String) < 1){
        printf("Error: isBase64 input is NULL or empty.\n");
        return result;
    }

    // Check byte-alignment.
    int base64StringLength = strlen(base64String);
    if (base64StringLength % 4){
        printf("Error: isBase64 input length is not a multiple of 4.\n");
        return result;
    }

    // Check for non-base64 characters.
    for(int i=0; i<base64StringLength; i++){
        int isNumber        = (base64String[i] >= '0') && ('9' >= base64String[i]);
        int isLowerCase     = (base64String[i] >= 'a') && ('z' >= base64String[i]);
        int isUpperCase     = (base64String[i] >= 'A') && ('Z' >= base64String[i]);
        int isSpecialChar   = (base64String[i] >= '+') && ('/' >= base64String[i]);
        
        int isEquals        = 0;
        if(base64String[i] == '='){
            char nextChar = base64String[i+1];
            if(nextChar == '='){
                nextChar = base64String[i+2];
                isEquals = (nextChar == '\0');
            } else {
                isEquals = (nextChar == '\0');
            }
        }

        if (!isNumber && !isLowerCase && !isUpperCase && !isSpecialChar && !isEquals){
            printf("Error: isBase64 input contains non-base64 character [%c].\n", base64String[i]);
            return result;
        }
    }

    // We passed all tests.
    result = 1;
    return result;
}


char *encodeBase64(char *data, int numberOfBytes){
    char *result = NULL;

    // Check for invalid arguments.
    if (!data){
        printf("Error: encodeBase64 data input is NULL.\n");
        return result;
    } else if (numberOfBytes < 1){
        printf("Error: encodeBase64 numberOfBytes input is less than one.\n");
        return result;
    }

    // For every 3 bytes of data, we need 4 characters (8 bytes) to represent it.
    int resultSize = ((numberOfBytes * 3) / 4) * 2;
    
    // If the number of bytes is not a multiple of three, obtain memory for padding characters.
    resultSize += (numberOfBytes % 3) * 2;

    // Allocate the memory to store the result and the null terminator. 
    result = calloc(resultSize + 1, sizeof(char));
    if (!result){
        printf("Error: encodeBase64 Could not allocate memory for the result.\n");
        return result;
    }    

    // Base64 encode the data, 24 bytes at a time.
    int numWrote = 0;
    for(int i=0; i<numberOfBytes; i+=3){

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
    int remainingBytes = numberOfBytes % 3;    
    if (remainingBytes == 1){
        strncpy(result + numWrote - 2, "==", sizeof(char) * 3);
    } else if (remainingBytes == 2){
        strncpy(result + numWrote - 1, "=", sizeof(char) * 2);
    }

    // Return the contents of the memory address as a hexadecimal string.
    return result;
}


char *decodeBase64(char *base64String){
    char *result = NULL;

    // Check that we received valid base64 data.
    if (!isBase64(base64String)){
        printf("Error: decodeBase64 input is not valid base64.\n");
        return result;
    }

    // For every 4 base64 characters, we need 3 bytes to store it.
    int base64Characters = strlen(base64String) ;

    int numberOfBytes = (base64Characters / 3) * 4;
    result = calloc(numberOfBytes + 1, sizeof(char));
    if (!result){
        printf("Error: decodeBase64 could not allocate memory for the result.\n");
        return result;
    }    

    unsigned int numWrote = 0;
    for(int i=0; i<base64Characters; i+=4){

        // Divide the chunk into 4 6 bit blocks based on the encoding values.
        const char *currentChunk = base64String + i;
        unsigned int block1 = (int)(strchr(BASE64_ENCODING_VALUES, currentChunk[0]) - BASE64_ENCODING_VALUES);
        unsigned int block2 = (int)(strchr(BASE64_ENCODING_VALUES, currentChunk[1]) - BASE64_ENCODING_VALUES);
        unsigned int block3 = 0;
        unsigned int block4 = 0;
        if(currentChunk[2] == '='){
            block2 = block2 & 0xFC;
            block3 = 0x00;
            block4 = 0x00;
        } else if(currentChunk[2] == '='){
            block3 = block3 & 0xF3;
            block4 = 0x00;
        } else {
            block3 = (int)(strchr(BASE64_ENCODING_VALUES, currentChunk[2]) - BASE64_ENCODING_VALUES);
            block4 = (int)(strchr(BASE64_ENCODING_VALUES, currentChunk[3]) - BASE64_ENCODING_VALUES);
        }

        unsigned char byte1 = (block1 << 2) | (block2 >> 4);  // byte1 consists of block1 [5, 4, 3, 2, 1, 0] and block2 [5, 4]
        unsigned char byte2 = (block2 << 4) | (block3 >> 2);  // byte2 consists of block2 [3, 2, 1, 0] and block3 [5, 4, 3, 2]
        unsigned char byte3 = (block3 << 6) | (block4 >> 0);  // byte3 consists of block3 [1, 0] and block4 [5, 4, 3, 2, 1, 0]

        // Write the bytes to the result.
        result[numWrote++] = byte1;
        result[numWrote++] = byte2;
        result[numWrote++] = byte3;
    }
    result[numWrote++] = '\0';

    return result;
}


char *xorDataBlock(char *data, char *xorKey, int numberOfBytes, int keyLength){
    char *result = NULL;

    // Check for invalid arguments.
    if (!data){
        printf("Error: xorDataBlock data input is NULL.\n");
        return result;        
    } else if (!xorKey){
        printf("Error: xorDataBlock xorKey input is NULL.\n");
        return result;
    } else if (numberOfBytes < 1){
        printf("Error: xorDataBlock numberOfBytes input is less than one.\n");
        return result;
    } else if (keyLength < 1){
        printf("Error: xorDataBlock keyLength input is less than one.\n");
        return result;
    }

    // Obtain memory to store the result.
    result = calloc(numberOfBytes + 1, sizeof(char));
    if (!result){
        printf("Error: xorDataBlocks Could not allocate memory.\n");
        return result;
    }    

    // For each byte of the data, XOR it with the repeating key's next byte and append it to the result.
    for(int i=0; i<numberOfBytes/2; i++){
        unsigned char dataByte = data[i];
        unsigned char xorKeyByte = xorKey[i % keyLength];
        result[i] = dataByte ^ xorKeyByte;
    }

    return result;
}


xorDecryptedMessage *xorDecrypt(char *data, int numberOfBytes, int keyLength){
    xorDecryptedMessage *result = NULL;

    // Check for invalid arguments.
    if (!data){
        printf("Error: xorDecrypt data input is NULL or empty.\n");
        return result;      
    } else if (numberOfBytes < 1){
        printf("Error: xorDecrypt numberOfBytes input is less than one.\n");
        return result;
    } else if (keyLength < 1){
        printf("Error: xorDecrypt keyLength input is less than one.\n");
        return result;
    }

    // Allocate memory for the result struct.
    result = calloc(sizeof(xorDecryptedMessage), sizeof(char));
    if (!result){
        printf("Error: xorDecrypt could not allocate memory for result struct.\n");        
        return result;
    }

    // Allocate memory for the result key.
    result->key = calloc(sizeof(char) * (keyLength + 1), sizeof(char));
    if (!result->key){
        printf("Error: xorDecrypt could not allocate memory for result key.\n");
        free(result);
        result = NULL;
        return result;
    }

    // Allocate memory for the result message.
    result->message = calloc(sizeof(char) * (numberOfBytes + 1), sizeof(char));
    if (!result->message){
        printf("Error: xorDecrypt could not allocate memory for result message.\n");
        free(result->key);
        free(result);
        result = NULL;
        return result;
    }

    // Allocate temporary memory for use in finding the key.
    char *keyBuffer = calloc(sizeof(char) * (keyLength + 1), sizeof(char));
    if (!keyBuffer){
        printf("Error: xorDecrypt could not obtain memory for key buffer.\n");
        free(result->message);
        free(result->key);
        free(result);
        result = NULL;
        return result;
    }

    // Check all combinations of common ASCII s the key.
    checkAllKeyCombinations(result, data, numberOfBytes, keyBuffer, 0, keyLength);

    // Clean up and return.
    free(keyBuffer);
    return result;
}


void checkAllKeyCombinations(xorDecryptedMessage* result, char *data, int messageLength, char *keyBuffer, int index, int keyLength){
    // If the key is the desired length, try to decrypt and return.
    if (index >= keyLength){
        keyBuffer[keyLength] = '\0';

        // XOR the cipher string and our key string together and free the keyString.
        char *xorResult = xorDataBlock(data, keyBuffer, ((messageLength * 2) + 1), keyLength);
        if (!xorResult){
            printf("Error: checkAllKeyCombinations could not XOR datablocks.\n");
            return;
        }

        // Count how many spaces and English alphabet ASCII characters are in the decoded string.
        int thisScore = 0;
        for(int j=0; j<(messageLength * 2); j++){
            if (('A' <= xorResult[j] && xorResult[j] <= 'z') || xorResult[j] == ' '){
                thisScore++;
            }
        }

        // If this decrypted string scores higher than the previous best, save it and the key.
        if (thisScore > result->score){
            result->score = thisScore;
            strncpy(result->key, keyBuffer, keyLength);
            strncpy(result->message, (const char *)xorResult, messageLength);
        }
        free(xorResult);
        return;

    // If the key is less than keyLength, loop this index through all characters and recurse.
    } else {
        for (char i=' '; i<='}'; i++){
            keyBuffer[index] = i;
            checkAllKeyCombinations(result, data, messageLength, keyBuffer, index + 1, keyLength);
        }
    }
}


int computeHammingDistance(char *dataOne, char *dataTwo, int numberOfBytes){
    int result = 0;

    // Check for invalid arguments.
    if (!dataOne || !dataTwo){
        printf("Error: computeHammingDistance received null arguments.\n");
        return result;
    } else if (numberOfBytes < 1){
        printf("Error: computeHammingDistance number of bytes less than one.\n");
        return result;
    } 

    // A byte at a time to simplify the hamming weight calculation.
    for(int i=0; i<numberOfBytes; i++){

        // XOR the byte which will return the bits that are unique to each data.
        char *xorResult = xorDataBlock(dataOne + i, dataTwo + i, sizeof(char) * 2, (numberOfBytes * 2)); 
        if(!xorResult){
            printf("Error: computeHammingDistance call to xorDataBlock failed.\n");
            return result;
        }

        // Calculate the hamming weight for this byte.
        for(int j=0; j<8; j++){
            int isBitSet = ((xorResult[0] >> j) % 2) ? 1 : 0;
            result += isBitSet;
        }

        // Free the xor result before moving on to the next byte.
        free(xorResult);
    }

    return result;
}


