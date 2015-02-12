#ifndef S1C03_H
#define S1C03_H

#include "cryptopals-common.h"

/**
  * Provided a hexadecimal string that represents a block of data XOR'ed with a single
  * character, determine the original message and key used in the XOR operation.
  *
  * @param hexString The XOR'ed data string we will attempt to decrypt.
  *
  * @return The xorDecryptedMessage containing the original key, message, and score indicating the confidence.
  */
xorDecryptedMessage *solveSet1Challenge03(char *hexString);

#endif
