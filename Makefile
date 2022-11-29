# Copyright Sima Alexandru 312CA 2022-2023

CC=gcc
CFLAGS=-Wall -Wextra -std=c99 -g

OBJS=main.o alocari.o comenzi.o operatii.o utils.o

build: my_octave

my_octave: $(OBJS)
	$(CC) $(CFLAGS) -o my_octave $^

clean:
	-rm -f my_octave *.o vgcore.*

pack:
	zip -FSr 312CA_SimaAlexandru_Tema2.zip README Makefile *.c *.h

apara-ma-doamne: my_octave
	valgrind -s --track-origins=yes --leak-check=full ./my_octave < exemplu.in

.PHONY: pack clean apara-ma-doamne
