# CC=x86_64-w64-mingw32-gcc
CC=gcc

all: clean build

build:
	$(CC) main.c -o foddacitron.exe -Wall -Os -s

clean:
	rm -f foddacitron.exe
