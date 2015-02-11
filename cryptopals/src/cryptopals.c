#include "cryptopals.h"

int main(int argc, char **argv) {

    printf("-----------------------------------------------------\n");
    printf("|########## Matasano's Crypto Challenges! ##########|\n");
    printf("-----------------------------------------------------\n");

    printf("[Set 01 :: Challenge 01]\n");
    char *resultOne = solveSet1Challenge01(NULL);
    if(resultOne){
        printf("Result: %s\n\n", resultOne);
        free(resultOne);
    } else {
        printf("Failed.\n\n");
    }

    printf("[Set 01 :: Challenge 02]\n");
    char *resultTwo = solveSet1Challenge02(NULL, NULL);
    if(resultTwo){
        printf("Result: %s\n\n", resultTwo);
        free(resultTwo);
    } else {
        printf("Failed.\n\n");
    }

    printf("[Set 01 :: Challenge 03]\n");
    xorDecryptedMessage *resultThree = solveSet1Challenge03(NULL);
    if(resultThree){
        printf("Key: %s\n", resultThree->key);
        printf("Score: %d\n", resultThree->numberOfMatches);
        printf("Message: %s\n\n", resultThree->message);
        free(resultThree->key);
        free(resultThree->message);
        free(resultThree);
    } else {
        printf("Failed.\n\n");
    }

    printf("[Set 01 :: Challenge 04]\n");
    // I broke it
    // xorDecryptedMessage *resultFour = solveSet1Challenge04(NULL);
    xorDecryptedMessage *resultFour = NULL;
    if(resultFour){
        printf("Key: %s\n", resultFour->key);
        printf("Score: %d\n", resultFour->numberOfMatches);
        printf("Message: %s\n\n", resultFour->message);
        free(resultFour->key);
        free(resultFour->message);
        free(resultFour);
    } else {
        printf("Failed.\n\n");
    }

    printf("[Set 01 :: Challenge 05]\n");
    char *resultFive = solveSet1Challenge05(NULL, NULL);
    if(resultFive){
        printf("Result: %s\n\n", resultFive);
        free(resultFive);
    } else {
        printf("Failed.\n\n");
    }

    return 0;
}
