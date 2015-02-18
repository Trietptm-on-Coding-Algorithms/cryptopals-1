#ifndef CRYPTOPALS_COMMON_H
#define CRYPTOPALS_COMMON_H

#include <openssl/aes.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __clang__
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#endif 

static const char BASE64_ENCODING_VALUES[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

/**
  * A struct representing the result of an XOR decryption attempt.
  *
  * @param score The score based on English ASCII characters found.
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
char *xorDataBlock(char *data, int numberOfBytes, char *xorKey, int keyLength);


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
  * @param numberOfBytes The number of bytes the decrypted message contains.
  * @param keyLength The length of the key to XOR the ciphertext with.
  * @param keyBuffer The allocated memory used to recursively iterate through all possible keys.
  * @param index The index in the keyBuffer this recursive call is looking at.
  */
void checkAllKeyCombinations(xorDecryptedMessage* result, char *data, int numberOfBytes, int keyLength, char *keyBuffer, int index);


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


/**
  * Given a char, return a score based on it's frequency in the English alphabet.
  *
  * Punctuation, spaces, newlines, and NULL terminators receive no score.
  * Non-English characters receive a negative score.
  *
  * @param char The character whose score we want to retrieve.
  *
  * @return The frequency score of the char provided.
  */
double getLetterScore(char letter);


/**
  * Given a block of data, the number of bytes to look at, and the maximum key size allowed,
  * find the average hamming distance between blocks of various keysizes.
  *
  * The key size that results in the lowest normalized hamming distance is likely to be the
  * key size and that is what is returned.
  *
  * @param data The data to determine the key size for.
  * @param numberOfBytes The number of bytes represented by the data.
  * @param maxKeySize The maximum key size we will try to find. 
  *
  * @return The key size resulting in the lowest normalized hamming distance.
  */
int determineKeySize(char *data, int numberOfBytes, int maxKeySize);


/**
  * Given a block of data, the number of bytes to look at, and the desired block size,
  * divide the original data into an array of blockSize data blocks.
  *
  * @param data The data to divide into blocks.
  * @param numberOfBytes The number of bytes represented by the data.
  * @param blockSize The blocksize the data will be divided into.
  *
  * @return The array of blockSize blocks containing the original data.
  */
char **divideDataIntoBlocks(char *data, int numberOfBytes, int blockSize);


/**
  * Given an array of blocks of data, transpose the blocks such that the number
  * of rows becomes the number of colums, and the number of columns is now
  * the number of rows.
  *
  *                                                                   Column
  *                   Column                                       ------------                         
  *             ------------------                                | 1  2  3  4 |
  *            | 1  2  3  4  5  6 |                           ----+------------|
  *        ----+------------------|                           | 1 | A  G  M  S |
  *     R  | 1 | A  B  C  D  E  F |                        R  | 2 | B  H  N  T |
  *     o  | 2 | G  H  I  J  K  L |     -------------->    o  | 3 | C  I  O  U |
  *     w  | 3 | M  N  O  P  Q  R |                        w  | 4 | D  J  P  V |
  *     s  | 4 | S  T  U  V  W  X |                        s  | 2 | E  K  Q  W |
  *         ----------------------                            | 3 | F  L  R  X |
  *                                                            ----------------
  * @param dataBlocks The array of data to transpose.
  * @param numRows The number of rows the dataBlocks contains.
  * @param numColumns The number of columns the dataBlocks contains.
  *
  * @return The array of transposed data.
  */
char **transposeBlocks(char **dataBlocks, int numRows, int numColumns);


/**
  * Given a block of data, the size of the data, and the desired size
  *
  * @param data The data to divide into blocks.
  * @param numberOfBytes The number of bytes represented by the data.
  * @param desiredNumberOfBytes The blocksize the data will be divided into.
  *
  * @return The data padded to the desired length with PKCS7 padding.
  */
char *pkcs7(char *data, int numberOfBytes, int desiredNumberOfBytes);


void *aesDecryptECB(void *data, int dataLength, void *key, int keyLength);
void *aesEncryptECB(void *data, int dataLength, void *key, int keyLength);
void aesCheck(char *data, char *key, char *answer);

#endif
