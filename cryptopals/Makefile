########################### variables ###########################
PROGRAM_NAME = cryptopals
DIRS = lib bin

INCLUDE_FOLDER = include
COMMON_SRC_FOLDER = src/common
SET_1_SRC_FOLDER = src/set01

COMMON_LIBS = lib/cryptopals-common.o
SET_ONE_LIBS = lib/set01challenge01.o lib/set01challenge02.o lib/set01challenge03.o lib/set01challenge04.o lib/set01challenge05.o lib/set01challenge06.o lib/set01challenge07.o
ALL_LIBS = ${COMMON_LIBS} lib/set01.a
DEPENDENCIES = -lssl -lcrypto

CC = gcc
CC_FLAGS = -Wall -Werror -g -std=c99 -I${INCLUDE_FOLDER}
CC_CMD = ${CC} ${CC_FLAGS}


########################## cryptopals! ##########################
${PROGRAM_NAME}: libs
	${CC_CMD} src/${PROGRAM_NAME}.c ${ALL_LIBS} ${DEPENDENCIES} -o bin/${PROGRAM_NAME}

${PROGRAM_NAME}-common: dirs ${COMMON_SRC_FOLDER}/${PROGRAM_NAME}-common.c
	${CC_CMD} -c ${COMMON_SRC_FOLDER}/${PROGRAM_NAME}-common.c -o lib/${PROGRAM_NAME}-common.o


############ Set 1 library and individual solutions. ############
set01: set01challenge01 set01challenge02 set01challenge03 set01challenge04 set01challenge05 set01challenge06 set01challenge07
	ar rvs lib/set01.a ${SET_ONE_LIBS}

set01challenge01: dirs ${PROGRAM_NAME}-common
	${CC_CMD} -c ${SET_1_SRC_FOLDER}/set01challenge01.c -o lib/set01challenge01.o

set01challenge02: dirs ${PROGRAM_NAME}-common
	${CC_CMD} -c ${SET_1_SRC_FOLDER}/set01challenge02.c -o lib/set01challenge02.o

set01challenge03: dirs ${PROGRAM_NAME}-common
	${CC_CMD} -c ${SET_1_SRC_FOLDER}/set01challenge03.c -o lib/set01challenge03.o

set01challenge04: dirs ${PROGRAM_NAME}-common
	${CC_CMD} -c ${SET_1_SRC_FOLDER}/set01challenge04.c -o lib/set01challenge04.o

set01challenge05: dirs ${PROGRAM_NAME}-common
	${CC_CMD} -c ${SET_1_SRC_FOLDER}/set01challenge05.c -o lib/set01challenge05.o

set01challenge06: dirs ${PROGRAM_NAME}-common
	${CC_CMD} -c ${SET_1_SRC_FOLDER}/set01challenge06.c -o lib/set01challenge06.o

set01challenge07: dirs ${PROGRAM_NAME}-common
	${CC_CMD} -c ${SET_1_SRC_FOLDER}/set01challenge07.c -o lib/set01challenge07.o


########################### grunt work ###########################
all: ${PROGRAM_NAME}

libs: dirs ${PROGRAM_NAME}-common set01

dirs:
	mkdir -p ${DIRS}

clean:
	rm -rf ${DIRS}

