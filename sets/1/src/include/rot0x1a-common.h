#ifndef ROT0X1A_COMMON_H
#define ROT0X1A_COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char BASE64_ENCODING_VALUES[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

unsigned char *loadHexStringToMemory(char *hexString);
char *base64Encode(unsigned char *data, int dataLength);

#endif
