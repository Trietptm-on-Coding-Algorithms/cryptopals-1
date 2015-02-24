#include "cryptopals.h"


int main(int argc, char **argv) {
    mainMenu();
    return 0;
}


void printMainMenu(){
    printf("                                                                                        \n");
    printf("                                                                                        \n");
    printf("╔══════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║  ██████╗██████╗ ██╗   ██╗██████╗ ████████╗ ██████╗ ██████╗  █████╗ ██╗     ███████╗  ║\n");
    printf("║ ██╔════╝██╔══██╗╚██╗ ██╔╝██╔══██╗╚══██╔══╝██╔═══██╗██╔══██╗██╔══██╗██║     ██╔════╝  ║\n");
    printf("║ ██║     ██████╔╝ ╚████╔╝ ██████╔╝   ██║   ██║   ██║██████╔╝███████║██║     ███████╗  ║\n");
    printf("║ ██║     ██╔══██╗  ╚██╔╝  ██╔═══╝    ██║   ██║   ██║██╔═══╝ ██╔══██║██║     ╚════██║  ║\n");
    printf("║ ╚██████╗██║  ██║   ██║   ██║        ██║   ╚██████╔╝██║     ██║  ██║███████╗███████║  ║\n");
    printf("║  ╚═════╝╚═╝  ╚═╝   ╚═╝   ╚═╝        ╚═╝    ╚═════╝ ╚═╝     ╚═╝  ╚═╝╚══════╝╚══════╝  ║\n");
    printf("╠══════════════════════════════════════════════════════════════════════════════════════╣\n");
    printf("║ http://cryptopals.com                                                      -rot0x1a  ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("[1] Basics                                                                              \n");
    printf("[2] Block Crypto                                                                        \n");
    printf("[3] Block & Stream Crypto                                         (Not yet implemented) \n");
    printf("[4] Stream crypto and randomness                                  (Not yet implemented) \n");
    printf("[5] Diffie-Hellman and friends                                    (Not yet implemented) \n");
    printf("[6] RSA and DSA                                                   (Not yet implemented) \n");
    printf("[7] Hashes                                                        (Not yet implemented) \n");
    printf("[8] Unknown                                                       (Not yet implemented) \n");
    printf("[0] Quit                                                                                \n");
    printf("                                                                                        \n");
}


void mainMenu(){
    printMainMenu();
    char input = 0;
    while (input != '0'){
        while (input < '0' || input > '8'){
            printf("Enter Selection: ");
            scanf("%c", &input);
            while(input != '\n' && getchar() != '\n');
        }

        switch(input){
            case '1':   setOneMenu();
                        printMainMenu();
                        input = 0;
                        break;
                        
            case '2':   setTwoMenu();
                        printMainMenu();
                        input = 0;
                        break;
                        
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':   printf("Sorry, this set is not yet completed.\n");
                        input = 0;
                        break;

            case '0':   return;

            default:    printf("Unknown option: %c\n", input);
                        input = 0;
                        break;
        }
    }
}


void printSetOneMenu(){
    printf("                                                                                        \n");
    printf("                                                                                        \n");
    printf("╔══════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║ Set One: Basics                                                                      ║\n");
    printf("╠══════════════════════════════════════════════════════════════════════════════════════╣\n");
    printf("║ This is the qualifying set. We picked the exercises in it to ramp developers up      ║\n");
    printf("║ gradually into coding cryptography, but also to verify that we were working with     ║\n");
    printf("║ people who were ready to write code.                                                 ║\n");
    printf("║                                                                                      ║\n");
    printf("║ This set is relatively easy. With one exception, most of these exercises should      ║\n");
    printf("║ take only a couple minutes. But don't beat yourself up if it takes longer than       ║\n");
    printf("║ that. It took Alex two weeks to get through the set!                                 ║\n");
    printf("║                                                                                      ║\n");
    printf("║ If you've written any crypto code in the past, you're going to feel like skipping    ║\n");
    printf("║ a lot of this. Don't skip them. At least two of them (we won't say which) are        ║\n");
    printf("║ important stepping stones to later attacks.                                          ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("[1] Convert hex to base64                                                               \n");
    printf("[2] Fixed XOR                                                                           \n");
    printf("[3] Single-byte XOR cipher                                                              \n");
    printf("[4] Detect single-character XOR                                                         \n");
    printf("[5] Implement repeating-key XOR                                                         \n");
    printf("[6] Break repeating-key XOR                                                             \n");
    printf("[7] AES in ECB mode                                                                     \n");
    printf("[8] Detect AES in ECB mode                                                              \n");
    printf("[0] Main Menu                                                                           \n");
    printf("                                                                                        \n");    
}


void printSetOneChallengeOneMenu(){
    printf("                                                                                                    \n");
    printf("                                                                                                    \n");
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║ Set One: Basics                                             Challenge One: Convert hex to base64 ║\n");
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════╣\n");
    printf("║ The string:                                                                                      ║\n");
    printf("║ 49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d ║\n");
    printf("║                                                                                                  ║\n");
    printf("║ Should produce:                                                                                  ║\n");
    printf("║ SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t                                 ║\n");
    printf("║                                                                                                  ║\n");
    printf("║ So go ahead and make that happen. You'll need to use this code for the rest of the exercises.    ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("[1] Convert hex to base64.                                                                          \n");
    printf("[2] Change input.                                                                                   \n");
    printf("[0] Main Menu                                                                                       \n");
    printf("                                                                                                    \n");    
}


void printSetOneChallengeTwoMenu(){
    printf("                                                                                                    \n");
    printf("                                                                                                    \n");
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║ Set One: Basics                                                         Challenge Two: Fixed XOR ║\n");
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════╣\n");
    printf("║ Write a function that takes two equal-length buffers and produces their XOR combination.         ║\n");
    printf("║                                                                                                  ║\n");
    printf("║ If your function works properly, then when you feed it the string:                               ║\n");
    printf("║ 1c0111001f010100061a024b53535009181c                                                             ║\n");
    printf("║                                                                                                  ║\n");
    printf("║ ... after hex decoding, and when XOR'd against:                                                  ║\n");
    printf("║ 686974207468652062756c6c277320657965                                                             ║\n");
    printf("║                                                                                                  ║\n");
    printf("║ ... should produce:                                                                              ║\n");
    printf("║ 746865206b696420646f6e277420706c6179                                                             ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("[1] XOR inputs.                                                                                     \n");
    printf("[2] Change XOR input.                                                                               \n");
    printf("[3] Change XOR key.                                                                                 \n");
    printf("[0] Main Menu                                                                                       \n");
    printf("                                                                                                    \n");    
}


void printSetOneChallengeThreeMenu(){
    printf("                                                                                                    \n");
    printf("                                                                                                    \n");
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║ Set One: Basics                                          Challenge Three: Single-byte XOR cipher ║\n");
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════╣\n");
    printf("║ The hex encoded string:                                                                          ║\n");
    printf("║ 1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736                             ║\n");
    printf("║                                                                                                  ║\n");
    printf("║ ... has been XOR'd against a single character. Find the key, decrypt the message.                ║\n");
    printf("║                                                                                                  ║\n");
    printf("║ You can do this by hand. But don't: write code to do it for you.                                 ║\n");
    printf("║                                                                                                  ║\n");
    printf("║ How? Devise some method for \"scoring\" a piece of English plaintext.                              ║\n");
    printf("║ Character frequency is a good metric.                                                            ║\n");
    printf("║ Evaluate each output and choose the one with the best score.                                     ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("[1] Crack XOR cipher.                                                                               \n");
    printf("[2] Change XOR ciphertext.                                                                          \n");
    printf("[0] Main Menu                                                                                       \n");
    printf("                                                                                                    \n");    
}


void printSetTwoMenu(){
    printf("                                                                                        \n");
    printf("                                                                                        \n");
    printf("╔══════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║ Set Two: Block Crypto                                                                ║\n");
    printf("╠══════════════════════════════════════════════════════════════════════════════════════╣\n");
    printf("║ This is the first of several sets on block cipher cryptography. This is              ║\n");
    printf("║ bread-and-butter crypto, the kind you'll see implemented in most web software        ║\n");
    printf("║ that does crypto. This set is relatively easy.                                       ║\n");
    printf("║                                                                                      ║\n");
    printf("║ People that clear set 1 tend to clear set 2 somewhat quickly.                        ║\n");
    printf("║                                                                                      ║\n");
    printf("║ Three of the challenges in this set are extremely valuable in breaking real-world    ║\n");
    printf("║ crypto; one allows you to decrypt messages encrypted in the default mode of AES,     ║\n");
    printf("║ and the other two allow you to rewrite messages encrypted in the most popular modes  ║\n");
    printf("║ of AES.                                                                              ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("[1] Implement PKCS#7 padding                                                            \n");
    printf("[2] Implement CBC mode                                                                  \n");
    printf("[3] An ECB/CBC detection oracle                                   (Not yet implemented) \n");
    printf("[4] Byte-at-a-time ECB decryption (Simple)                        (Not yet implemented) \n");
    printf("[5] ECB cut-and-paste                                             (Not yet implemented) \n");
    printf("[6] Byte-at-a-time ECB decryption (Harder)                        (Not yet implemented) \n");
    printf("[7] PKCS#7 padding validation                                     (Not yet implemented) \n");
    printf("[0] Main Menu                                                                           \n");
    printf("                                                                                        \n");    
}


void setOneMenu(){
    printSetOneMenu(); 
    char input = 0;
    while (input != '0'){
        while (input < '0' || input > '8'){
            printf("Enter Selection: ");
            scanf("%c", &input);
            while(input != '\n' && getchar() != '\n');
        }

        switch(input){
            case '1':   setOneChallengeOne();
                        printSetOneMenu();
                        input = 0;
                        break;

            case '2':   setOneChallengeTwo();
                        printSetOneMenu();
                        input = 0;
                        break;

            case '3':   setOneChallengeThree();
                        printSetOneMenu();
                        input = 0;
                        break;

            case '4':   setOneChallengeFour();
                        printSetOneMenu();
                        input = 0;
                        break;

            case '5':   setOneChallengeFive();
                        printSetOneMenu();
                        input = 0;
                        break;

            case '6':   setOneChallengeSix();
                        printSetOneMenu();
                        input = 0;
                        break;

            case '7':   setOneChallengeSeven();
                        printSetOneMenu();
                        input = 0;
                        break;

            case '8':   setOneChallengeEight();
                        printSetOneMenu();
                        input = 0;
                        break;                    
                        
            case '0':   return;

            default:    printf("Unknown option: %c\n", input);
                        input = 0;
                        break;
        }        
    }
}


void setOneChallengeOne(){
    char *result;
    int maxInputLength = 256;

    char *challengeOneInput = calloc(maxInputLength + 1, sizeof(char));
    if(!challengeOneInput){
        printf("Failed to allocate memory for Set 1, Challenge 1.\n");
        return;
    }
    strncpy(challengeOneInput, SET_1_CHALLENGE_1_INPUT_1, strlen(SET_1_CHALLENGE_1_INPUT_1));

    printSetOneChallengeOneMenu();
    char input = 0;
    while (input != '0'){
        while (input < '0' || input > '2'){
            printf("Current Input: %s\n", challengeOneInput);
            printf("Enter Selection: ");
            scanf("%c", &input);
            while(input != '\n' && getchar() != '\n');
        }

        switch(input){
            case '1':   result = solveSet1Challenge01(challengeOneInput);
                        if(result != NULL){
                            printf("----------------------------------------------------\n");
                            printf("Result: %s\n", result);
                            free(result);
                        }
                        printf("\n");
                        input = 0;
                        break;

            case '2':   printf("Enter new input: ");
                        fgets(challengeOneInput, maxInputLength, stdin);
                        char *ptr = challengeOneInput;
                        while(*ptr != '\0'){
                            if(*ptr == '\n'){
                                *ptr = '\0';
                            } else {
                                ptr++;
                            }
                        }
                        printSetOneChallengeOneMenu();
                        input = 0;
                        break;

            case '0':   return;

            default:    printf("Unknown option: %c\n", input);
                        input = 0;
                        break;
        }        
    }
}


void setOneChallengeTwo(){
    char *result;
    int maxInputLength = 256;

    char *challengeTwoInputOne = calloc(maxInputLength + 1, sizeof(char));
    char *challengeTwoInputTwo = calloc(maxInputLength + 1, sizeof(char));
    if(!challengeTwoInputOne || !challengeTwoInputTwo){
        printf("Failed to allocate memory for Set 1, Challenge 2.\n");
        return;
    }

    strncpy(challengeTwoInputOne, SET_1_CHALLENGE_2_INPUT_1, strlen(SET_1_CHALLENGE_2_INPUT_1));
    strncpy(challengeTwoInputTwo, SET_1_CHALLENGE_2_INPUT_2, strlen(SET_1_CHALLENGE_2_INPUT_2));

    printSetOneChallengeTwoMenu();
    char input = 0;
    while (input != '0'){
        while (input < '0' || input > '3'){
            printf("Current Input: %s\n", challengeTwoInputOne);
            printf("Current Key:   %s\n", challengeTwoInputTwo);
            printf("Enter Selection: ");
            scanf("%c", &input);
            while(input != '\n' && getchar() != '\n');
        }

        switch(input){
            case '1':   result = solveSet1Challenge02(challengeTwoInputOne, challengeTwoInputTwo);
                        if(result != NULL){
                            printf("----------------------------------------------------\n");
                            printf("Result: %s\n", result);
                            free(result);
                        }
                        printf("\n");
                        input = 0;
                        break;

            case '2':   printf("Enter new input: ");
                        fgets(challengeTwoInputOne, maxInputLength, stdin);
                        char *ptrOne = challengeTwoInputOne;
                        while(*ptrOne != '\0'){
                            if(*ptrOne == '\n'){
                                *ptrOne = '\0';
                            } else {
                                ptrOne++;
                            }
                        }
                        printSetOneChallengeTwoMenu();
                        input = 0;
                        break;

            case '3':   printf("Enter new input: ");
                        fgets(challengeTwoInputTwo, maxInputLength, stdin);
                        char *ptrTwo = challengeTwoInputTwo;
                        while(*ptrTwo != '\0'){
                            if(*ptrTwo == '\n'){
                                *ptrTwo = '\0';
                            } else {
                                ptrTwo++;
                            }
                        }
                        printSetOneChallengeTwoMenu();
                        input = 0;
                        break;

            case '0':   return;

            default:    printf("Unknown option: %c\n", input);
                        input = 0;
                        break;
        }        
    }
}


void setOneChallengeThree(){
    xorDecryptedMessage *result;
    int maxInputLength = 256;

    char *challengeThreeInput = calloc(maxInputLength + 1, sizeof(char));
    if(!challengeThreeInput){
        printf("Failed to allocate memory for Set 1, Challenge 1.\n");
        return;
    }
    strncpy(challengeThreeInput, SET_1_CHALLENGE_3_INPUT_1, strlen(SET_1_CHALLENGE_3_INPUT_1));

    printSetOneChallengeThreeMenu();
    char input = 0;
    while (input != '0'){
        while (input < '0' || input > '2'){
            printf("Current Input: %s\n", challengeThreeInput);
            printf("Enter Selection: ");
            scanf("%c", &input);
            while(input != '\n' && getchar() != '\n');
        }

        switch(input){
            case '1':   result = solveSet1Challenge03(challengeThreeInput);
                        if(result != NULL){
                            printf("----------------------------------------------------\n");
                            printf("Score:    %f\n", result->score);
                            printf("Key:      %s\n", result->key);
                            printf("Message:  %s\n\n", result->message);
                            free(result->key);
                            free(result->message);
                            free(result);
                        }
                        printf("\n");
                        input = 0;
                        break;

            case '2':   printf("Enter new input: ");
                        fgets(challengeThreeInput, maxInputLength, stdin);
                        char *ptr = challengeThreeInput;
                        while(*ptr != '\0'){
                            if(*ptr == '\n'){
                                *ptr = '\0';
                            } else {
                                ptr++;
                            }
                        }
                        printSetOneChallengeThreeMenu();
                        input = 0;
                        break;

            case '0':   return;

            default:    printf("Unknown option: %c\n", input);
                        input = 0;
                        break;
        }        
    }
}


void setOneChallengeFour(){

}


void setOneChallengeFive(){

}


void setOneChallengeSix(){

}


void setOneChallengeSeven(){

}


void setOneChallengeEight(){

}


void setTwoMenu(){
    printSetTwoMenu(); 
    char input = 0;
    while (input != '0'){
        while (input < '0' || input > '7'){
            printf("Enter Selection: ");
            scanf("%c", &input);
            while(input != '\n' && getchar() != '\n');
        }

        switch(input){
            case '1':   printf("Implement PKCS#7 padding\n");
                        printSetTwoMenu();
                        input = 0;
                        break;

            case '2':   printf("Implement CBC mode\n");
                        printSetTwoMenu();
                        input = 0;
                        break;

            case '3':   printf("An ECB/CBC detection oracle\n");
                        printSetTwoMenu();
                        input = 0;
                        break;

            case '4':   printf("Byte-at-a-time ECB decryption (Simple)\n");
                        printSetTwoMenu();
                        input = 0;
                        break;

            case '5':   printf("ECB cut-and-paste\n");
                        printSetTwoMenu();
                        input = 0;
                        break;

            case '6':   printf("Byte-at-a-time ECB decryption (Harder)\n");
                        printSetTwoMenu();
                        input = 0;
                        break;

            case '7':   printf("PKCS#7 padding validation\n");
                        printSetTwoMenu();
                        input = 0;
                        break;

            case '0':   return;

            default:    printf("Unknown option: %c\n", input);
                        input = 0;
                        break;
        }        
    }
}



int oldMain(){


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
    char *setTwoChallengeTwoResult = solveSet2Challenge02(SET_2_CHALLENGE_2_INPUT_1);
    if(setTwoChallengeTwoResult){
        printf("setTwoChallengeTwoResult:\n%s\n", setTwoChallengeTwoResult);
        free(setTwoChallengeTwoResult);
    } else {
        printf("Failed.\n\n");
    }

    mainMenu();

    return 0;
}




