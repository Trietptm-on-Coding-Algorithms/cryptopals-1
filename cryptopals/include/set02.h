#ifndef SET02_H
#define SET02_H

#include "cryptopals-common.h"
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

char *solveSet2Challenge01(char *data, int desiredLength);
char *solveSet2Challenge02(char *fileName);
#endif