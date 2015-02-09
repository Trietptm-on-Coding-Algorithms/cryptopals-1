all: rot0x1a-common s1c01

rot0x1a-common: src/rot0x1a-common.c src/include/rot0x1a-common.h
	mkdir lib
	gcc -Wall -Werror -c src/rot0x1a-common.c -o lib/rot0x1a-common.o

s1c01: rot0x1a-common src/s1c01.c
	mkdir dist
	gcc -Wall -Werror lib/rot0x1a-common.o src/s1c01.c -o dist/s1c01 

clean:
	rm -f *~ lib/*.o src/s1c01
