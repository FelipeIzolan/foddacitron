# CC=x86_64-w64-mingw32-gcc
CC=gcc

ifeq ($(OS),Windows_NT)
	SHELL := powershell
endif

all: clean build

build:
	$(CC) ini.c main.c -o foddacitron.exe -Wall -Os -s
	cp config.def.ini config.ini

clean:
	rm -f foddacitron.exe config.ini
