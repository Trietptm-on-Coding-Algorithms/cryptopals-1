/**
  * Matasano Crypto Challenge Solution
  * Set: 01, Challenge 05: Implement repeating-key XOR
  *
  * Coded by rot0x1a, 10 Feb 2015
  */
#include "set01challenge05.h"

char *solveSet1Challenge05(char *string, char *xorKey){
    
    char *result = NULL;
    
    string = (!string || strlen(string) < 1) ? "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal" : string;
    xorKey = (!xorKey || strlen(xorKey) < 1) ? "ICE" : xorKey;

	result = xorDataBlock(string, xorKey, strlen(string) * 2);
	if(!result){
		printf("Error: Failed to XOR the data =(\n");
		return result;
	}

    return result;
}
