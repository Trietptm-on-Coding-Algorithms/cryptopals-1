#ifndef CRYPTOPALS_H
#define CRYPTOPALS_H

#include <stdio.h>
#include "cryptopals-common.h"
#include "set01.h"
#include "set02.h"

void mainMenu();

void setOneMenu();
void setOneChallengeOne();
void setOneChallengeTwo();
void setOneChallengeThree();
void setOneChallengeFour();
void setOneChallengeFive();
void setOneChallengeSix();
void setOneChallengeSeven();
void setOneChallengeEight();

void printSetOneMenu();
void printSetOneChallengeOneMenu();
void printSetOneChallengeTwoMenu();
void printSetOneChallengeThreeMenu();
void printSetOneChallengeFourMenu();
void printSetOneChallengeFiveMenu();
void printSetOneChallengeSixMenu();
void printSetOneChallengeSevenMenu();
void printSetOneChallengeEightMenu();

void setTwoMenu();
void setTwoChallengeOne();
void setTwoChallengeTwo();

#define SET_1_CHALLENGE_1_INPUT_1 "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d"

#define SET_1_CHALLENGE_2_INPUT_1 "1c0111001f010100061a024b53535009181c"
#define SET_1_CHALLENGE_2_INPUT_2 "686974207468652062756c6c277320657965"

#define SET_1_CHALLENGE_3_INPUT_1 "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736"

#define SET_1_CHALLENGE_4_INPUT_1 "data/4.txt"

#define SET_1_CHALLENGE_5_INPUT_1 "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal"
#define SET_1_CHALLENGE_5_INPUT_2 "ICE"

#define SET_1_CHALLENGE_6_INPUT_1 "data/6.txt"

#define SET_1_CHALLENGE_7_INPUT_1 "data/7.txt"
#define SET_1_CHALLENGE_7_INPUT_2 "YELLOW SUBMARINE"

#define SET_1_CHALLENGE_8_INPUT_1 "data/8.txt"

#define SET_2_CHALLENGE_1_INPUT_1 "YELLOW SUBMARINE"
#define SET_2_CHALLENGE_1_INPUT_2 20

#define SET_2_CHALLENGE_1_EXPECTED_OUTPUT "YELLOW SUBMARINE\\x04\\x04\\x04\\x04"
#define SET_2_CHALLENGE_2_INPUT_1 "data/10.txt"

#endif