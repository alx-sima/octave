# Copyright Sima Alexandru 312CA 2022-2023

CC=gcc
CFLAGS=-Wall -Wextra -std=c99 -g

build: main.o alocare.o operatii.o utils.o
	$(CC) $(CFLAGS) -o my_octave $^

clean:
	rm -f my_octave *.o vgcore.*

pack: zip -FSr 312CA_SimaAlexandru_Tema2.zip README Makefile *.c *.h

.PHONY: pack clean