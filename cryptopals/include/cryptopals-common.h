#ifndef CRYPTOPALS_COMMON_H
#define CRYPTOPALS_COMMON_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static const char BASE64_ENCODING_VALUES[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

/**
  * A struct representing the result of an XOR decryption attempt.
  *
  * @param score The score indicating the confidence of success. Based on English ASCII characters found.
  * @param key The string XOR'ed with the cipher text to arrive at this result.
  * @param message The deciphered text found by XOR'ing the ciphertext with the key.
  */
typedef struct {
    double score;
    char *key;
    char *message;
} xorDecryptedMessage;


/**
  * Validate that a string is valid hex data.
  *
  * @param hexString The hex string to validate.
  * 
  * @return 1 if valid hex, 0 if not valid hex.
  */
int isHex(char *hexString);


/**
  * Returns the specified number of bytes at the provided location encoded as a hex string.
  *
  * @param data The location of the data to be encoded.
  * @param numberOfBytes The number of bytes to encode.
  *
  * @return The hex string representation of the data.
  */
char *encodeHex(char *data, int numberOfBytes);


/**
  * Provided a string of hex characters, load the data into memory and return a pointer to it.
  * 
  * Hex String Requirements:
  *   1) The hex string must be of even length in order to align the bytes in memory correctly.
  *   2) The string must be null terminated.
  *   2) The string greater than one character.
  *
  * @param hexString The hex string to load into memory.
  *
  * @return The memory address containing the loaded data.
  */
char *decodeHex(char *hexString);


/**
  * Validate that a string is valid base64 data.
  *
  * @param base64String The base64 string to validate.
  * 
  * @return 1 if valid base64, 0 if not valid base64.
  */
int isBase64(char *base64String);


/**
  * Returns the specified number of bytes at the provided location encoded as a base64 string.
  *
  * @param data The location of the data to be encoded.
  * @param dataLength The number of bytes to encode.
  *
  * @return The numberOfBytes string representation of the data.
  */
char *encodeBase64(char *data, int numberOfBytes);


/**
  * Provided a string of base64 characters, load the data into memory and return a pointer to it.
  * 
  * Hex String Requirements:
  *   1) The base64 string must be evenly divisible by 4.
  *   2) The string must be null terminated.
  *   2) The string greater than one character.
  *
  * @param base64String The base64 string to load into memory.
  *
  * @return The memory address containing the loaded data.
  */
char *decodeBase64(char *base64String);


/**
  * Returns the XOR result of the data and repeating key for the specified number of bytes.
  *
  * @param data The block of data to XOR using the key.
  * @param xorKey The key to use when XOR'ing the dataBlock.
  * @param numberOfBytes The number of bytes to XOR.
  * @param keyLength The number of bytes to use as the key.
  *
  * @return The data resulting from the XOR operation.
  */
char *xorDataBlock(char *data, char *xorKey, int numberOfBytes, int keyLength);


/**
  * Decrypt data by finding the key of a specified length that results in the highest number of common ASCII characters.
  *
  * NOTE: keyLength of values over 4 may take a long time.
  *
  * @param data The block of data to decrypt.
  * @param numberOfBytes The number of bytes to decrypt.
  * @param keyLength The length of the key to use when decrypting the data.
  *
  * @return The struct containing the key, message, and confidence score for the success found.
  */
xorDecryptedMessage *xorDecrypt(char *data, int numberOfBytes, int keyLength);


/**
  * Brute force decrypt the ciphertext by trying to XOR all possible combinations of common US ASCII character strings of a 
  * specified length and returning the match which contains the most US ASCII characters.
  *
  * Note: Thanks to roofis0 for helping me enumerate all possible key values of length n.
  *
  * @param result A preallocated xorDecryptedMessage struct which will be populated with the top match of the decryption attempt.
  * @param data The data we will attempt to decrypt.
  * @param messageLength The length of the message when decrypted.
  * @param keyBuffer The allocated memory used to recursively iterate through all possible keys.
  * @param index The index in the keyBuffer this recursive call is looking at.
  * @param keyLength The length of the key to XOR the ciphertext with.
  */
void checkAllKeyCombinations(xorDecryptedMessage* result, char *data, int messageLength, char *keyBuffer, int index, int keyLength);


/**
  * Calculate the Hamming distance between two blocks of data for a given number of bytes.
  *
  * @param dataOne The first block of data.
  * @param dataTwo The second block of data.
  * @param numberOfBytes The number of bytes to compute the Hamming distance for.
  *
  * @return The Hamming distance between the two blocks of data.
  */
int computeHammingDistance(char *dataOne, char *dataTwo, int numberOfBytes);


double getLetterScore(char letter);

#endif
