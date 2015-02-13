/**
  * Matasano Crypto Challenge Solution
  * Set: 01, Challenge 05: Implement repeating-key XOR
  *
  * Coded by rot0x1a, 10 Feb 2015
  */
#include "set01challenge05.h"

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
    char *xorResult = xorDataBlock(message, key, strlen(message) * 2, strlen(key) * 2);
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
