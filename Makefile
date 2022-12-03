# Copyright Sima Alexandru 312CA 2022-2023

CC=gcc
CFLAGS=-Wall -Wextra -std=c99

OBJS=main.o alocari.o comenzi.o operatii.o strassen.o

build: my_octave

my_octave: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	-rm -f my_octave $(OBJS) vgcore.*

pack:
	zip -FSr 312CA_SimaAlexandru_Tema2.zip README Makefile *.c *.h

.PHONY: pack clean
