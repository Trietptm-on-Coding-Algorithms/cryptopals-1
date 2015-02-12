#ifndef S1C04_H
#define S1C04_H

#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "cryptopals-common.h"

/**
  * Provided a file containing a list of hexadecimal strings that represents blocks of data XOR'ed with a single
  * character, determine which string originally contained a secret message.
  *
  * @param fileName The location of the file storing the list of hexadecimal strings.
  *
  * @return The xorDecryptedMessage containing the original key, message, and score indicating the confidence.
  */
  xorDecryptedMessage *solveSet1Challenge04(char *fileName);

#endif
