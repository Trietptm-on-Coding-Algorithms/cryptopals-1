#ifndef S1C01_H
#define S1C01_H

#include "cryptopals-common.h"

#define S1C01_DEFAULT_INPUT_01 "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d"

/**
  * Convert a string of hex bytes into equivalent base64 string.
  * This is done by copying the hex bytes into memory as raw data and then
  * reading them back out as a base64 string.
  *
  * @param hexString The hexadecimal characters to convert to base64.
  *
  * @return The base64 string which is equivalent to the hexString parameter.
  */
char *solveSet1Challenge01(char *hexString);

#endif
