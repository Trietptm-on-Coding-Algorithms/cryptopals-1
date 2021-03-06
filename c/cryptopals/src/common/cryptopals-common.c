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


char *xorDataBlock(char *data, int numberOfBytes, char *xorKey, int keyLength){
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
    for(int i=0; i<numberOfBytes; i++){
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
    checkAllKeyCombinations(result, data, numberOfBytes, keyLength, keyBuffer, 0);

    // Clean up and return.
    free(keyBuffer);
    return result;
}


void checkAllKeyCombinations(xorDecryptedMessage* result, char *data, int numberOfBytes, int keyLength, char *keyBuffer, int index){
    // If the key is the desired length, try to decrypt and return.
    if (index >= keyLength){
        keyBuffer[keyLength] = '\0';

        // XOR the cipher string and our key string together and free the keyString.
        char *xorResult = xorDataBlock(data, numberOfBytes, keyBuffer, keyLength);
        if (!xorResult){
            printf("Error: checkAllKeyCombinations could not XOR datablocks.\n");
            return;
        }

        // Count how many spaces and English alphabet ASCII characters are in the decoded string.
        int thisScore = 0;
        for(int j=0; j<numberOfBytes; j++){
            thisScore += getLetterScore(xorResult[j]);
        }

        // If this decrypted string scores higher than the previous best, save it and the key.
        if (thisScore > result->score){
            result->score = thisScore;
            strncpy(result->key, keyBuffer, keyLength);
            strncpy(result->message, (const char *)xorResult, numberOfBytes);
        }
        free(xorResult);
        return;

    // If the key is less than keyLength, loop this index through all characters and recurse.
    } else {
        for (int i=0x00; i<=0xFF; i++){
            keyBuffer[index] = i;
            checkAllKeyCombinations(result, data, numberOfBytes, keyLength, keyBuffer, index + 1);
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

        // XOR the bytes together which will return the bits that are unique to each byte.
        char *xorResult = xorDataBlock(dataOne + i, 1, dataTwo + i, 1); 
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


double getLetterScore(char letter){
    double result = 0;

    switch(letter){
        case 'A':
        case 'a':
            result = 8.167;
            break;

        case 'B':
        case 'b':
            result += 1.492;
            break;

        case 'C':
        case 'c':
            result += 2.782;
            break;

        case 'D':
        case 'd':
            result += 4.253;
            break;

        case 'E':
        case 'e':
            result += 12.702;
            break;

        case 'F':
        case 'f':
            result += 2.228;
            break;

        case 'G':
        case 'g':
            result += 2.015;
            break;

        case 'H':
        case 'h':
            result += 6.094;
            break;

        case 'I':
        case 'i':
            result += 6.966;
            break;

        case 'J':
        case 'j':
            result += 0.153;
            break;

        case 'K':
        case 'k':
            result += 0.772;
            break;

        case 'L':
        case 'l':
            result += 4.025;
            break;

        case 'M':
        case 'm':
            result += 2.406;
            break;

        case 'N':
        case 'n':
            result += 6.749;
            break;

        case 'O':
        case 'o':
            result += 7.507;
            break;

        case 'P':
        case 'p':
            result += 1.929;
            break;

        case 'Q':
        case 'q':
            result += 0.095;
            break;

        case 'R':
        case 'r':
            result += 5.987;
            break;

        case 'S':
        case 's':
            result += 6.327;
            break;

        case 'T':
        case 't':
            result += 9.056;
            break;

        case 'U':
        case 'u':
            result += 2.758;
            break;

        case 'V':
        case 'v':
            result += 0.978;
            break;

        case 'W':
        case 'w':
            result += 2.360;
            break;

        case 'X':
        case 'x':
            result += 0.150;
            break;

        case 'Y':
        case 'y':
            result += 1.974;
            break;

        case 'Z':
        case 'z':
            result += 0.074;
            break;

        case '\0':
        case ' ':
        case '\n':
        case ')':
        case '(':
        case ',':
        case ':':
        case ';':
        case '.':
        case '!':
        case '?':
        case '\'':
        case '"':
            result += 0.0;
            break;

        default:
            result -= 50.0;
            break;
    }

    return result;
}


char **divideDataIntoBlocks(char *data, int numberOfBytes, int blockSize){
    char **result = NULL;

    // Determine the number of blocks required
    int numberOfBlocks = numberOfBytes / blockSize;
    while(numberOfBytes > (numberOfBlocks * blockSize)){
        numberOfBlocks++;
    }

    // Allocate memory for the result.
    result = malloc(sizeof(char *) * numberOfBlocks);
    for(int i=0; i<numberOfBlocks; i++){
        result[i] = calloc(blockSize + 1, sizeof(char *));
    }

    // Copy the data into the blocks.
    for(int i=0; i<numberOfBlocks; i++){
        for(int j=0; j<blockSize; j++){
            result[i][j] = (data + (blockSize * i))[j];
        }
    }

    return result;
}


char **transposeBlocks(char **dataBlocks, int numColumns, int numRows){
    char **result = NULL;

    // Allocate memory for the result.
    result = malloc(sizeof(char *) * numColumns);
    for(int i=0; i<numColumns; i++){
        result[i] = calloc(numRows + 1, sizeof(char *));
    }

    // Transpose.
    for(int i=0; i<numColumns; i++){
        for(int j=0; j<numRows; j++){
            result[i][j] = dataBlocks[j][i];
        }
    }

    return result;
}


int determineKeySize(char *data, int numberOfBytes, int maxKeySize){
    int result = -1;

    // Create a space for our hamming distance averages and zero them all out.
    float hammingAverages[maxKeySize];
    for(int i=0; i<maxKeySize; i++){
        hammingAverages[i] = 0.0;
    }

    // Take as many samples as we can given the data size and maximum key size.
    int numSamples = (numberOfBytes - maxKeySize) / 2;
    for(int i=0; i<numSamples; i++){

        // Add the normalized samples together:
        for(int j=2; j<maxKeySize; j++){
            char *dataStart = data + i;
            int hammingDistance = computeHammingDistance(dataStart, dataStart + j, j);
            float normalized = (float)hammingDistance / (float)j;
            hammingAverages[j] += normalized;
        }
    }

    // Find the lowest normalize hamming distance. This is probably the key.
    int lowestNormalized = -1;
    for(int i =2; i<maxKeySize; i++){
        hammingAverages[i] /= numSamples;
        if(lowestNormalized < 0 || hammingAverages[i] < lowestNormalized){
            result = i;
            lowestNormalized = hammingAverages[i];
        }
    }
    
    return result;
}


char *pkcs7(char *data, int numberOfBytes, int desiredLength){
    char *result = NULL;

    // Check for invalid arguments.
    if(numberOfBytes < 1) {
        printf("Error: pkcs7 numberOfBytes less than one.\n");
        return result;
    } else if (desiredLength < 1){
        printf("Error: pkcs7 desiredLength less than one.\n");
        return result;
    } 

    result = calloc(desiredLength, sizeof(char));
    if(!result){
        printf("Error: pkcs7 could not allocate memory for result message.\n");
        return result;
    }

    char paddingByte = desiredLength - numberOfBytes;
    strncpy(result, data, numberOfBytes);
    for(int i=numberOfBytes; i<desiredLength; i++){
        result[i] = paddingByte;
    }

    return result;      
}


void *stripPKCS7(void *data, int dataLength){
    void *result;

    //Allocate memory
    result = calloc(dataLength + 1, sizeof(char));

    // Strip PKCS7 padding.
    int paddingLength = ((unsigned char *)data)[dataLength - 1];
    strncpy(result, data, dataLength - paddingLength);

    // Return the result.
    return result;    
}


void *aesEncryptECB(void *data, int dataLength, void *key, int keyLength){
    void *result = NULL;

    // Check for invalid arguments.
    if (!data){
        printf("Error: aesEncryptECB data input is NULL.\n");
        return result;        
    } else if (!key){
        printf("Error: aesEncryptECB key input is NULL.\n");
        return result;
    } else if (dataLength < 1){
        printf("Error: aesEncryptECB dataLength input is less than one.\n");
        return result;
    } else if (keyLength < 1){
        printf("Error: aesEncryptECB keyLength input is less than one.\n");
        return result;
    }

    // Allocate memory for the result.
    result = calloc(dataLength, sizeof(char));
    if (!result){
        printf("Error: aesEncryptBlock could not allocate memory for result message.\n");
        return result;
    }

    // Prepare for decryption.
    AES_KEY aesKey;
    AES_set_encrypt_key((const unsigned char *)key, keyLength * 8, &aesKey);
    unsigned int paddingLength = 16 - (dataLength % 16);
    void *paddedPlaintext = pkcs7(data, dataLength, dataLength + paddingLength);
    const unsigned char *aesIn = (const unsigned char *)paddedPlaintext;

    // Encrypt the 16 bit blocks.
    int count = 0;
    while (count < dataLength){
        AES_ecb_encrypt(aesIn + count, (unsigned char *)result + count, (const AES_KEY *)&aesKey, AES_ENCRYPT);
        count += AES_BLOCK_SIZE;
    }

    // Clean up and return.
    free(paddedPlaintext);
    return result;
}


void *aesDecryptECB(void *data, int dataLength, void *key, int keyLength){
    void *result = NULL;

    // Check for invalid arguments.
    if (!data){
        printf("Error: aesDecryptECB data input is NULL.\n");
        return result;        
    } else if (!key){
        printf("Error: aesDecryptECB key input is NULL.\n");
        return result;
    } else if (dataLength < 1){
        printf("Error: aesDecryptECB dataLength input is less than one.\n");
        return result;
    } else if (keyLength < 1){
        printf("Error: aesDecryptECB keyLength input is less than one.\n");
        return result;
    }

    // Allocate memory for the result.
    void *decrypted = calloc(dataLength + 1, sizeof(char));
    if (!decrypted){
        printf("Error: aesDecryptECB could not allocate memory for decrypted message.\n");
        return result;
    }

    // Prepare for decryption.
    AES_KEY aesKey;
    AES_set_decrypt_key((const unsigned char *)key, keyLength * 8, &aesKey);
    const unsigned char *aesIn = data;

    // Decrypt the 16 bit blocks.
    int count = 0;
    while (count < dataLength){
        AES_ecb_encrypt(aesIn + count, (unsigned char *)decrypted + count, (const AES_KEY *)&aesKey, AES_DECRYPT);
        count += AES_BLOCK_SIZE;
    }

    result = stripPKCS7(decrypted, dataLength);

    free(decrypted);
    return result;
}


void *aesDecryptCBC(void *data, int dataLength, void *key, int keyLength){
    void *result = NULL;

    // Check for invalid arguments.
    if (!data){
        printf("Error: aesDecryptCBC data input is NULL.\n");
        return result;        
    } else if (!key){
        printf("Error: aesDecryptCBC key input is NULL.\n");
        return result;
    } else if (dataLength < 1){
        printf("Error: aesDecryptCBC dataLength input is less than one.\n");
        return result;
    } else if (keyLength < 1){
        printf("Error: aesDecryptCBC keyLength input is less than one.\n");
        return result;
    }

    // Allocate memory for the result.
    void *decrypted = calloc(dataLength + 1, sizeof(char));
    if (!decrypted){
        printf("Error: aesDecryptCBC could not allocate memory for decrypted message.\n");
        return result;
    }

    // Allocate memory for the result.
    char *xorDecrypted = calloc(dataLength + 1, sizeof(char));
    if (!xorDecrypted){
        printf("Error: aesDecryptCBC could not allocate memory for xorDecrypted.\n");
        return result;
    }

    // Prepare for decryption.
    AES_KEY aesKey;
    AES_set_decrypt_key((const unsigned char *)key, keyLength * 8, &aesKey);

    int numBlocks = dataLength / 16;
    for(int i=0; i<numBlocks; i++){

        int offset = 16 * i;
        char *iv = (i == 0) ? "\0\0\0\0\0\0\0\0" : data + (offset - 16);
        const unsigned char *aesIn = (const unsigned char *)data + offset;
        AES_ecb_encrypt(aesIn, (unsigned char *)(decrypted + offset), (const AES_KEY *)&aesKey, AES_DECRYPT);
        char *cbcBlock = (i == 0) ? (char *)decrypted : (char *)xorDataBlock((char *)decrypted + offset, 16, iv, 16);
        strncpy(xorDecrypted + offset, cbcBlock, strlen(cbcBlock));
        
        if(i != 0){            
            free(cbcBlock);
        }
    }

    result = stripPKCS7(xorDecrypted, dataLength);
    free(decrypted);
    free(xorDecrypted);
    return result;
}


void *aesEncryptCBC(void *data, int dataLength, void *key, int keyLength) {
    printf("aesEncryptCBC not yet implemented......\n");
    return NULL;
}


void aesCheck(char *data, char *key, char *answer){
  int plaintextLength = strlen(data);
  int paddingLength = 16 - (plaintextLength % 16);
  int encryptedLength = plaintextLength + paddingLength;

  void *aesIn = data;
  int dataLength = plaintextLength;
  void *aesKey = key;
  int keyLength = strlen(key);

  void *encrypted = aesEncryptECB(aesIn, dataLength, aesKey, keyLength);
  void *decrypted = aesDecryptECB(encrypted, encryptedLength, aesKey, keyLength);

  printf("Original : %s\n", data);

  printf("Hex      : ");
  for(int i=0; i<plaintextLength; i++){
    printf("%02x", ((unsigned char *)data)[i]);
  }
  printf("\n");

  printf("Encrypted: ");
  for(int i=0; i<encryptedLength; i++){
    printf("%02x", ((unsigned char *)encrypted)[i]);
  }
  printf("\n");

  printf("Expected : %s\n", answer);

  printf("Decrypted: ");
  for(int i=0; i<encryptedLength; i++){
    printf("%02x", ((unsigned char *)decrypted)[i]);
  }
  printf("\n");

  printf("Plaintext: %s", (char *)decrypted);
  printf("\n\n");
}




