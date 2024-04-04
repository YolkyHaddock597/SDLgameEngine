CC = gcc
CFLAGS = $(shell sdl2-config --cflags)
LIBS = $(shell sdl2-config --libs)

.PHONY: all clean

all: a.out
	./a.out

a.out: main.c
	$(CC) -o $@ $< $(CFLAGS) $(LIBS)

clean:
	rm -f a.out
