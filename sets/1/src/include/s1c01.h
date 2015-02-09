#ifndef S1C01_H
#define S1C01_H

#include "rot0x1a-common.h"

/**
  * Convert a string of hex bytes into equivalent base64 string.
  * This is done by copying the hex bytes into memory as raw data and then
  * reading them back out as a base64 string.
  *
  * @param hexString The hexadecimal characters to convert to base64.
  *
  * @return The base64 string which is equivalent to the hexString parameter.
  */
char *hexToBase64(char *hexString);

#endif