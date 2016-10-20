#ifndef SET01_H
#define SET01_H

#include "cryptopals-common.h"
#include <fcntl.h>
#include <openssl/aes.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#ifdef __clang__
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#endif 

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


/**
  * Provided a hexadecimal string that represents a block of data XOR'ed with a single
  * character, determine the original message and key used in the XOR operation.
  *
  * @param hexString The XOR'ed data string we will attempt to decrypt.
  *
  * @return The xorDecryptedMessage containing the original key, message, and score indicating the confidence.
  */
xorDecryptedMessage *solveSet1Challenge03(char *hexString);


/**
  * Provided a file containing a list of hexadecimal strings that represents blocks of data XOR'ed with a single
  * character, determine which string originally contained a secret message.
  *
  * @param fileName The location of the file storing the list of hexadecimal strings.
  *
  * @return The xorDecryptedMessage containing the original key, message, and score indicating the confidence.
  */
  xorDecryptedMessage *solveSet1Challenge04(char *fileName);


/**
  * Return the result of XOR'ing a string with a repeating xorKey.
  *
  * @param string The hexadecimal string to be used in the XOR operation.
  * @param xorKey The key to use in the XOR operation.
  *
  * @return The hexadecimal representation of the string when XOR'ed with the xorKey.
  */
char *solveSet1Challenge05(char *string, char *xorKey);


/**
  * Provided a file containing an AES-128 ECB encrypted message, decrypt it using the provided key.
  *
  * @param fileName The location of the file containing the encrypted message.
  * @param key The key to use for decryption.
  *
  * @return The decrypted message.
  */
char *solveSet1Challenge06(char *fileName);


/**
  * Provided a file containing an AES-128 ECB encrypted message, decrypt it using the provided key.
  *
  * @param fileName The location of the file containing the encrypted message.
  * @param key The key to use for decryption.
  *
  * @return The decrypted message.
  */
char *solveSet1Challenge07(char *fileName, char *key);


/**
  * Provided a file containing multiple strings, determine which is an AES-ECB encrypted message.
  *
  * @param fileName The location of the file containing the strings.
  *
  * @return The AES-ECB encrypted message.
  */
char *solveSet1Challenge08(char *fileName);

#endif
