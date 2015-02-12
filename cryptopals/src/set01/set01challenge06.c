#include "set01challenge06.h"

xorDecryptedMessage *solveSet1Challenge06(char *fileName){
    xorDecryptedMessage *result = NULL;

    char *stringOne = "this is a test";
    char *stringTwo = "wokka wokka!!!";

    printf("Hamming Distance: %d\n", computeHammingDistance(stringOne, stringTwo));
    return result;
}