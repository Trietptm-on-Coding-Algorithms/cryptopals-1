CC = gcc
CC_FLAGS = -Wall -Werror
CC_CMD = ${CC} ${CC_FLAGS}

DIRS = lib dist

all: rot0x1a-common s1c01 s1c02

dirs:
	mkdir -p ${DIRS}

rot0x1a-common: dirs src/rot0x1a-common.c src/include/rot0x1a-common.h
	${CC_CMD} -c src/rot0x1a-common.c -o lib/rot0x1a-common.o

s1c01: dirs rot0x1a-common src/s1c01.c
	${CC_CMD} lib/rot0x1a-common.o src/s1c01.c -o dist/s1c01 

s1c02: dirs rot0x1a-common src/s1c02.c
	${CC_CMD} lib/rot0x1a-common.o src/s1c02.c -o dist/s1c02 

clean:
	rm -rf ${DIRS}
