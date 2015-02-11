#ifndef ROT0X1A_COMMON_H
#define ROT0X1A_COMMON_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static const char BASE64_ENCODING_VALUES[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

/**
  * A struct representing the result of an XOR decryption attempt.
  *
  * @param numberOfMatches The number of US ASCII characters found in the attempt.
  * @param key The string XOR'ed with the cipher text to arrive at this result.
  * @param message The deciphered text found by XOR'ing the ciphertext with the key.
  */
typedef struct {
    int numberOfMatches;
    char *key;
    char *message;
} xorDecryptedMessage;

/**
  * Provided a string of hex characters, allocate a chunk of memory and load
  * the hex characters into the chunk as raw data.
  *
  * @param hexString The hexadecimal characters load into memory.
  *
  * @return The memory address we loaded the hex data into.
  */
char *loadHexStringToMemory(char *hexString);


/**
  * Given a pointer to memory, encode the specified amount of data as base64 
  * and return the result as a string.
  *
  * @param data The location of the data to be encoded.
  * @param dataLength The number of bytes to encode.
  *
  * @return The base64 string representation of the data.
  */
char *base64Encode(char *data, int dataLength);


/**
  * XOR a datablock for a specified length using a specified key, repeating the key if necessary.
  *
  * @param dataBlock The block of data to XOR using the key.
  * @param xorKey The key to use when XOR'ing the dataBlock.
  * @param dataBlockLength The number of bytes to XOR.
  *
  * @return The string resulting from the XOR operation.
  */
char *xorDataBlock(char *dataBlock, char *xorKey, int dataBlockLength);


/**
  * Decrypt a hex string representing an XOR'ed ASCII string by finding the key of a 
  * specified length that results in the highest number of ASCII characters when XOR'ed again.
  *
  * NOTE: keyLength of values over 5 may take a long time.
  *
  * @param cipherText The hex string representing XOR'ed bytes of ASCII text.
  * @param keyLength The length of the key to use when XOR'ing the ciphertext.
  *
  * @return The struct containing the number of ASCII matches, the key, and the message found.
  */
xorDecryptedMessage *decryptHexStringUsingXOR(char *cipherText, int keyLength);


/**
  * Brute force decrypt the ciphertext by trying to XOR all possible combinations of common US ASCII character strings of a 
  * specified length and returning the match which contains the most US ASCII characters.
  *
  * Note: Thanks to roofis0 for helping me enumerate all possible key values of length n.
  *
  * @param result A preallocated xorDecryptedMessage struct which will be populated with the top match of the decryption attempt.
  * @param cipherText The XOR'ed ciphertext we will attempt to decrypt.
  * @param messageLength The length of the message when decrypted.
  * @param keyBuffer The allocated memory used to recursively iterate through all possible keys.
  * @param index The index in the keyBuffer this recursive call is looking at.
  * @param keyLength The length of the key to XOR the ciphertext with.
  */
void checkAllKeyCombinations(xorDecryptedMessage* result, char *cipherText, int messageLength, char *keyBuffer, int index, int keyLength);


#endif
