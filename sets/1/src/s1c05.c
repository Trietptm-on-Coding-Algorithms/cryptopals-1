/**
  * Matasano Crypto Challenge Solution
  * Set: 01, Challenge 05: Implement repeating-key XOR
  *
  * Coded by rot0x1a, 10 Feb 2015
  */
#include "include/s1c05.h"

int main(int argc, char **argv) {

	char *string = "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal";
	char *xorKey = "ICE";

	char *result = xorDataBlock(string, xorKey, strlen(string) * 2);
	if(!result){
		printf("Error: Failed to XOR the data =(\n");
		return -1;
	}

	printf("%s\n", result);
    free(result);
}
