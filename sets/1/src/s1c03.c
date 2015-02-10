/**
  * Matasano Crypto Challenge Solution
  * Set: 01, Challenge 03: Single-byte XOR cipher
  *
  * Coded by rot0x1a, 09 Feb 2015
  */
#include "include/s1c03.h"

int main(int argc, char **argv) {

    // Check for invalid arguments.
    if(argc != 2){
        printf("Error: Please provide a single strings.\n");
        return -1;
    }

    xorDecryptedMessage *result = decryptHexStringUsingXOR(argv[1], 1);

    printf("Key: %s\nMatches: %d\nMessage: %s\n", result->key, result->numberOfMatches, result->message);

    free(result->message);
    free(result);
    return 0;
}
