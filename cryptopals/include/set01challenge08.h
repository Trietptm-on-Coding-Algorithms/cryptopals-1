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

char *solveSet1Challenge08(char *fileName);

#endif
