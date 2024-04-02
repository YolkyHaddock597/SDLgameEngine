CC = gcc
CFLAGS = $(shell sdl2-config --cflags)
LIBS = $(shell sdl2-config --libs)

.PHONY: all clean

all: myprogram
	./myprogram

myprogram: main.c
	$(CC) -o $@ $< $(CFLAGS) $(LIBS)

clean:
	rm -f myprogram
