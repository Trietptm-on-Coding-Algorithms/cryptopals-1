########################### variables ###########################
PROGRAM_NAME = cryptopals
DIRS = lib bin

INCLUDE_FOLDER = include
COMMON_SRC_FOLDER = src/common
SETS_SRC_FOLDER = src/sets

CRYPTOPALS_OBJECTS = lib/${PROGRAM_NAME}-common.o lib/set01.o
CRYPTOPALS_LIB = lib/${PROGRAM_NAME}.a

CRYPTOPALS_DEPENDENCIES = ${CRYPTOPALS_LIB} -lssl -lcrypto

CC = gcc
CC_FLAGS = -Wall -Werror -g -std=c99 -I${INCLUDE_FOLDER}
CC_CMD = ${CC} ${CC_FLAGS}


########################## cryptopals! ##########################
${PROGRAM_NAME}: libs
	${CC_CMD} src/${PROGRAM_NAME}.c ${CRYPTOPALS_DEPENDENCIES} -o bin/${PROGRAM_NAME}

${PROGRAM_NAME}-common: dirs ${COMMON_SRC_FOLDER}/${PROGRAM_NAME}-common.c
	${CC_CMD} -c ${COMMON_SRC_FOLDER}/${PROGRAM_NAME}-common.c -o lib/${PROGRAM_NAME}-common.o


############ Set 1 library and individual solutions. ############
sets: set01
	ar vrs lib/${PROGRAM_NAME}.a ${CRYPTOPALS_OBJECTS}

set01: dirs ${PROGRAM_NAME}-common
	${CC_CMD} -c ${SETS_SRC_FOLDER}/set01.c -o lib/set01.o


########################### grunt work ###########################
all: ${PROGRAM_NAME}

libs: dirs ${PROGRAM_NAME}-common sets

dirs:
	mkdir -p ${DIRS}

clean:
	rm -rf ${DIRS}

