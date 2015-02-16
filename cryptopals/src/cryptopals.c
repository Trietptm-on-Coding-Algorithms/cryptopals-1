#include "cryptopals.h"


int main(int argc, char **argv) {

    printf("\n====================================================================================\n");
    printf("                           Matasano's Crypto Challenges Set 1                           ");
    printf("\n====================================================================================\n");

    printf(" ------------------------ \n");
    printf("| Set 01 ::Challenge 01] |\n");
    printf(" ------------------------ \n");
    char *resultOne = solveSet1Challenge01(SET_1_CHALLENGE_1_INPUT_1);
    if(resultOne){
        printf("Expected: %s\n", SET_1_CHALLENGE_1_EXPECTED_OUTPUT);
        printf("Result:   %s\n\n", resultOne);
        free(resultOne);
    } else {
        printf("Failed.\n\n");
    }

    printf(" ------------------------ \n");
    printf("| Set 01 :: Challenge 02 |\n");
    printf(" ------------------------ \n");
    char *resultTwo = solveSet1Challenge02(SET_1_CHALLENGE_2_INPUT_1, SET_1_CHALLENGE_2_INPUT_2);
    if(resultTwo){
        printf("Expected: %s\n", SET_1_CHALLENGE_2_EXPECTED_OUTPUT);
        printf("Result:   %s\n\n", resultTwo);
        free(resultTwo);
    } else {
        printf("Failed.\n\n");
    }

    printf(" ------------------------ \n");
    printf("| Set 01 :: Challenge 03 |\n");
    printf(" ------------------------ \n");
    xorDecryptedMessage *resultThree = solveSet1Challenge03(SET_1_CHALLENGE_3_INPUT_1);
    if(resultThree){
        printf("Result Score: %f\n", resultThree->score);
        printf("Expected Key: %s\n", SET_1_CHALLENGE_3_EXPECTED_KEY);
        printf("Result Key:   %s\n", resultThree->key);
        printf("Expected Message: %s\n", SET_1_CHALLENGE_3_EXPECTED_MESSAGE);
        printf("Result Message:   %s\n\n", resultThree->message);
        free(resultThree->key);
        free(resultThree->message);
        free(resultThree);
    } else {
        printf("Failed.\n\n");
    }

    printf(" ------------------------ \n");
    printf("| Set 01 :: Challenge 04 |\n");
    printf(" ------------------------ \n");
    xorDecryptedMessage *resultFour = solveSet1Challenge04(SET_1_CHALLENGE_4_INPUT_1);
    if(resultFour){
        printf("Result Score: %f\n", resultFour->score);
        printf("Expected Key: %s\n", SET_1_CHALLENGE_4_EXPECTED_KEY);
        printf("Result Key:   %s\n", resultFour->key);
        printf("Expected Message: %s\n", SET_1_CHALLENGE_4_EXPECTED_MESSAGE);
        printf("Result Message:   %s\n\n", resultFour->message);
        free(resultFour->key);
        free(resultFour->message);
        free(resultFour);
    } else {
        printf("Failed.\n\n");
    }

    printf(" ------------------------ \n");
    printf("| Set 01 :: Challenge 05 |\n");
    printf(" ------------------------ \n");
    char *resultFive = solveSet1Challenge05(SET_1_CHALLENGE_5_INPUT_1, SET_1_CHALLENGE_5_INPUT_2);
    if(resultFive){
        printf("Expected: %s\n", SET_1_CHALLENGE_5_EXPECTED_OUTPUT);
        printf("Result:   %s\n\n", resultFive);
        free(resultFive);
    } else {
        printf("Failed.\n\n");
    }

    printf(" ------------------------ \n");
    printf("| Set 01 :: Challenge 06 |\n");
    printf(" ------------------------ \n");
    char *resultSix = solveSet1Challenge06(SET_1_CHALLENGE_6_INPUT_1);
    if(resultSix){
        printf("Result Message:\n%s\n\n", resultSix);
        free(resultSix);
    } else {
        printf("Failed.\n\n");
    }

    printf(" ------------------------ \n");
    printf("| Set 01 :: Challenge 07 |\n");
    printf(" ------------------------ \n");
    char *resultSeven = solveSet1Challenge07(SET_1_CHALLENGE_7_INPUT_1, SET_1_CHALLENGE_7_INPUT_2);
    if(resultSeven){
        printf("Result Message:\n%s\n\n", resultSeven);
        free(resultSeven);
    } else {
        printf("Failed.\n\n");
    }

    return 0;
}
