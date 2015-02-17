#include "set02.h"

/**
  * Matasano Crypto Challenge Solution
  * Set: 02, Challenge 01:  Implement PKCS#7 padding
  *
  * Coded by rot0x1a, 17 Feb 2015
  */
char *solveSet2Challenge01(char *data, int desiredLength){
	char *result = NULL;

    // Check for invalid arguments.
    if(!data && strlen(data)){
        printf("Error: solveSet2Challenge01 data input is NULL.\n");
        return result;
    } else if (desiredLength < 1) {
        printf("Error: solveSet2Challenge01 desiredLength input is less than 1.\n");
        return result;
    }

    int numberOfBytes = strlen(data);    
    result = pkcs7(data, numberOfBytes, desiredLength);
    if(!result){
        printf("Error: solveSet2Challenge01 call to pcks7 failed.\n");
        return result;
    }

    return result;
}