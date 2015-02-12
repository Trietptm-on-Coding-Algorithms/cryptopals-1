#ifndef S1C02_H
#define S1C02_H

#include "cryptopals-common.h"

/**
  * Provided two equal-length, null-terminated hexadecimal strings which will be loaded
  * into memory as raw data, return the result of XOR'ing the data together.
  *
  * @param hexStringOne The first hexadecimal string to be used in the XOR operation.
  * @param hexStringTwo The second hexadecimal string to be used in the XOR operation.
  *
  * @return The hexadecimal representation of the data when XOR'ed
  */
char *solveSet1Challenge02(char *hexStringOne, char *hexStringTwo);

#endif