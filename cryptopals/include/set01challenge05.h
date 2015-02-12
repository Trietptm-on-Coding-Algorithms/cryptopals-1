#ifndef S1C05_H
#define S1C05_H

#include "cryptopals-common.h"

/**
  * Return the result of XOR'ing a string with a repeating xorKey.
  *
  * @param string The hexadecimal string to be used in the XOR operation.
  * @param xorKey The key to use in the XOR operation.
  *
  * @return The hexadecimal representation of the string when XOR'ed with the xorKey.
  */
char *solveSet1Challenge05(char *string, char *xorKey);

#endif
