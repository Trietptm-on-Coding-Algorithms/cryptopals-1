#ifndef S1C08_H
#define S1C08_H

#ifdef __clang__
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#endif 

#include <fcntl.h>
#include <unistd.h>
#include <openssl/aes.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "cryptopals-common.h"

/**
  * Provided a file containing multiple strings, determine which is an AES-ECB encrypted message.
  *
  * @param fileName The location of the file containing the strings.
  *
  * @return The AES-ECB encrypted message.
  */
char *solveSet1Challenge08(char *fileName);

#endif
