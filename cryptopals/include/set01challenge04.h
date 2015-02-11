#ifndef S1C04_H
#define S1C04_H

#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "cryptopals-common.h"

xorDecryptedMessage *solveSet1Challenge04(char *fileName);

#endif
