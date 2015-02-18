#include "cryptopals.h"


int main(int argc, char **argv) {

    printf("\n====================================================================================\n");
    printf("                           Matasano's Crypto Challenges Set 1                           ");
    printf("\n====================================================================================\n");

    printf(" ------------------------ \n");
    printf("| Set 01 ::Challenge 01] |\n");
    printf(" ------------------------ \n");
    char *setOneChallengeOneResult = solveSet1Challenge01(SET_1_CHALLENGE_1_INPUT_1);
    if(setOneChallengeOneResult){
        printf("Expected:                %s\n", SET_1_CHALLENGE_1_EXPECTED_OUTPUT);
        printf("setOneChallengeResult:   %s\n\n", setOneChallengeOneResult);
        free(setOneChallengeOneResult);
    } else {
        printf("Failed.\n\n");
    }

    printf(" ------------------------ \n");
    printf("| Set 01 :: Challenge 02 |\n");
    printf(" ------------------------ \n");
    char *setOneChallengeTwoResult = solveSet1Challenge02(SET_1_CHALLENGE_2_INPUT_1, SET_1_CHALLENGE_2_INPUT_2);
    if(setOneChallengeTwoResult){
        printf("Expected:                %s\n", SET_1_CHALLENGE_2_EXPECTED_OUTPUT);
        printf("setOneChallengeResult:   %s\n\n", setOneChallengeTwoResult);
        free(setOneChallengeTwoResult);
    } else {
        printf("Failed.\n\n");
    }

    printf(" ------------------------ \n");
    printf("| Set 01 :: Challenge 03 |\n");
    printf(" ------------------------ \n");
    xorDecryptedMessage *setOneChallengeThreeResult = solveSet1Challenge03(SET_1_CHALLENGE_3_INPUT_1);
    if(setOneChallengeThreeResult){
        printf("setOneChallengeResult Score:     %f\n", setOneChallengeThreeResult->score);
        printf("Expected Key:                    %s\n", SET_1_CHALLENGE_3_EXPECTED_KEY);
        printf("setOneChallengeResult Key:       %s\n", setOneChallengeThreeResult->key);
        printf("Expected Message:                %s\n", SET_1_CHALLENGE_3_EXPECTED_MESSAGE);
        printf("setOneChallengeResult Message:   %s\n\n", setOneChallengeThreeResult->message);
        free(setOneChallengeThreeResult->key);
        free(setOneChallengeThreeResult->message);
        free(setOneChallengeThreeResult);
    } else {
        printf("Failed.\n\n");
    }

    printf(" ------------------------ \n");
    printf("| Set 01 :: Challenge 04 |\n");
    printf(" ------------------------ \n");
    xorDecryptedMessage *setOneChallengeFourResult = solveSet1Challenge04(SET_1_CHALLENGE_4_INPUT_1);
    if(setOneChallengeFourResult){
        printf("setOneChallengeResult Score:     %f\n", setOneChallengeFourResult->score);
        printf("Expected Key:                    %s\n", SET_1_CHALLENGE_4_EXPECTED_KEY);
        printf("setOneChallengeResult Key:       %s\n", setOneChallengeFourResult->key);
        printf("Expected Message:                %s\n", SET_1_CHALLENGE_4_EXPECTED_MESSAGE);
        printf("setOneChallengeResult Message:   %s\n\n", setOneChallengeFourResult->message);
        free(setOneChallengeFourResult->key);
        free(setOneChallengeFourResult->message);
        free(setOneChallengeFourResult);
    } else {
        printf("Failed.\n\n");
    }

    printf(" ------------------------ \n");
    printf("| Set 01 :: Challenge 05 |\n");
    printf(" ------------------------ \n");
    char *setOneChallengeFiveResult = solveSet1Challenge05(SET_1_CHALLENGE_5_INPUT_1, SET_1_CHALLENGE_5_INPUT_2);
    if(setOneChallengeFiveResult){
        printf("Expected:                %s\n", SET_1_CHALLENGE_5_EXPECTED_OUTPUT);
        printf("setOneChallengeResult:   %s\n\n", setOneChallengeFiveResult);
        free(setOneChallengeFiveResult);
    } else {
        printf("Failed.\n\n");
    }

    printf(" ------------------------ \n");
    printf("| Set 01 :: Challenge 06 |\n");
    printf(" ------------------------ \n");
    char *setOneChallengeSixResult = solveSet1Challenge06(SET_1_CHALLENGE_6_INPUT_1);
    if(setOneChallengeSixResult){
        printf("setOneChallengeResult Message:\n%s\n\n", setOneChallengeSixResult);
        free(setOneChallengeSixResult);
    } else {
        printf("Failed.\n\n");
    }

    printf(" ------------------------ \n");
    printf("| Set 01 :: Challenge 07 |\n");
    printf(" ------------------------ \n");
    char *setOneChallengeSevenResult = solveSet1Challenge07(SET_1_CHALLENGE_7_INPUT_1, SET_1_CHALLENGE_7_INPUT_2);
    if(setOneChallengeSevenResult){
        printf("setOneChallengeResult Message:\n%s\n\n", setOneChallengeSevenResult);
        free(setOneChallengeSevenResult);
    } else {
        printf("Failed.\n\n");
    }

    printf(" ------------------------ \n");
    printf("| Set 01 :: Challenge 08 |\n");
    printf(" ------------------------ \n");
    char *setOneChallengeEightResult = solveSet1Challenge08(SET_1_CHALLENGE_8_INPUT_1);
    if(setOneChallengeEightResult){
        printf("Encrypted Line:\n%s\n\n", setOneChallengeEightResult);
        free(setOneChallengeEightResult);
    } else {
        printf("Failed.\n\n");
    }


    printf("\n====================================================================================\n");
    printf("                           Matasano's Crypto Challenges Set 2                           ");
    printf("\n====================================================================================\n");

    printf(" ------------------------ \n");
    printf("| Set 02 ::Challenge 01] |\n");
    printf(" ------------------------ \n");
    char *setTwoChallengeOneResult = solveSet2Challenge01(SET_2_CHALLENGE_1_INPUT_1, SET_2_CHALLENGE_1_INPUT_2);
    if(setTwoChallengeOneResult){
        printf("Expected:              %s\n", SET_2_CHALLENGE_1_EXPECTED_OUTPUT);

        printf("setOneChallengeResult: ");
        for(int i=0; i<SET_2_CHALLENGE_1_INPUT_2; i++){
            if(i < strlen(SET_2_CHALLENGE_1_INPUT_1)){
                printf("%c", setTwoChallengeOneResult[i]);
            } else {
                printf("\\x%02x", setTwoChallengeOneResult[i]);
            }
        }
        printf("\n\n");

        free(setTwoChallengeOneResult);
    } else {
        printf("Failed.\n\n");
    }

    printf(" ------------------------ \n");
    printf("| Set 02 ::Challenge 02] |\n");
    printf(" ------------------------ \n");
    char *setTwoChallengeTwoResult = solveSet2Challenge02(SET_2_CHALLENGE_1_INPUT_1, SET_2_CHALLENGE_1_INPUT_2);
    if(setTwoChallengeTwoResult){
        printf("Expected:              %s\n", SET_2_CHALLENGE_1_EXPECTED_OUTPUT);
        printf("setOneChallengeResult: ");
        printf("\n");

        free(setTwoChallengeTwoResult);
    } else {
        printf("Failed.\n\n");
    }


    return 0;
}
