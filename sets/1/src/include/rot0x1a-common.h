#ifndef ROT0X1A_COMMON_H
#define ROT0X1A_COMMON_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static const char BASE64_ENCODING_VALUES[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

/**
  * Provided a string of hex characters, allocate a chunk of memory and load
  * the hex characters into the chunk as raw data.
  *
  * @param hexString The hexadecimal characters load into memory.
  *
  * @return The memory address we loaded the hex data into.
  */
unsigned char *loadHexStringToMemory(char *hexString);


/**
  * Given a pointer to memory, encode the specified amount of data as base64 
  * and return the result as a string.
  *
  * @param data The location of the data to be encoded.
  * @param dataLength The number of bytes to encode.
  *
  * @return The base64 string representation of the data.
  */
char *base64Encode(unsigned char *data, int dataLength);


/**
  * Given a pointer to two blocks of memory, return a string representation
  * of the two values XOR'ed together.
  *
  * @param dataBlockOne The location of the first block of data to be XOR'ed.
  * @param dataBlockTwo The location of the second block of data to be XOR'ed.
  * @param dataBlockLength The number of bytes to XOR together.
  *
  * @return The string representation of the XOR results.
  */
char *xorDataBlocks(unsigned char *dataBlockOne, unsigned char *dataBlockTwo, int dataBlockLength);

#endif
