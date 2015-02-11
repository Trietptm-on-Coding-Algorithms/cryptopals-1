#ifndef CRYPTOPALS_H
#define CRYPTOPALS_H

#include "cryptopals-common.h"
#include "set01challenge01.h"
#include "set01challenge02.h"
#include "set01challenge03.h"
#include "set01challenge04.h"
#include "set01challenge05.h"

#define SET_1_CHALLENGE_1_INPUT_1 "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d"
#define SET_1_CHALLENGE_1_EXPECTED_OUTPUT "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t"

#define SET_1_CHALLENGE_2_INPUT_1 "1c0111001f010100061a024b53535009181c"
#define SET_1_CHALLENGE_2_INPUT_2 "686974207468652062756c6c277320657965"
#define SET_1_CHALLENGE_2_EXPECTED_OUTPUT "746865206b696420646f6e277420706c6179"

#define SET_1_CHALLENGE_3_INPUT_1 "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736"
#define SET_1_CHALLENGE_3_EXPECTED_KEY "X"
#define SET_1_CHALLENGE_3_EXPECTED_MESSAGE "Cooking MC's like a pound of bacon"

#define SET_1_CHALLENGE_4_INPUT_1 "resources/s1c04.strings"
#define SET_1_CHALLENGE_4_EXPECTED_KEY "5"
#define SET_1_CHALLENGE_4_EXPECTED_MESSAGE "Now that the party is jumping"

#define SET_1_CHALLENGE_5_INPUT_1 "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal"
#define SET_1_CHALLENGE_5_INPUT_2 "ICE"
#define SET_1_CHALLENGE_5_EXPECTED_OUTPUT "0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272a282b2f20430a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f"

#endif