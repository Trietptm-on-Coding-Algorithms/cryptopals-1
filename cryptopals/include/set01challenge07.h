#ifndef S1C07_H
#define S1C07_H

#include "cryptopals-common.h"

#include <fcntl.h>
#include <unistd.h>
#include <openssl/aes.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "cryptopals-common.h"

/**
  * Provided a file containing an AES-128 ECB encrypted message, decrypt it using the provided key.
  *
  * @param fileName The location of the file containing the encrypted message.
  * @param key The key to use for decryption.
  *
  * @return The decrypted message.
  */
char *solveSet1Challenge07(char *fileName, char *key);

#endif
