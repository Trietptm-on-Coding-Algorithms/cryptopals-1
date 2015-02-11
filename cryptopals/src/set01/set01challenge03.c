/**
  * Matasano Crypto Challenge Solution
  * Set: 01, Challenge 03: Single-byte XOR cipher
  *
  * Coded by rot0x1a, 09 Feb 2015
  */
#include "set01challenge03.h"

xorDecryptedMessage *solveSet1Challenge03(char *hexString) {
    xorDecryptedMessage *result = NULL;

    hexString = (!hexString || strlen(hexString) < 1) ? "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736" : hexString;

    result = decryptHexStringUsingXOR(hexString, 1);
    if(!result){
        printf("Error: Could not decrypt hex string.\n");
        return result;
    }

    return result;
}
