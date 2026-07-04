CC=gcc
CFLAGS=-std=c17 -W -Wall -ansi -pedantic
LDFLAGS=
EXEC=main

all: $(EXEC)

main: build main.o ring_buffer.o
	$(CC) -o build/main build/main.o build/ring_buffer.o $(LDFLAGS)

main.o: src/main.c
	$(CC) -o build/main.o -c src/main.c $(CFLAGS)

ring_buffer.o: src/ring_buffer.c
	$(CC) -o build/ring_buffer.o -c src/ring_buffer.c $(CFLAGS)

build:
	if ! [ -d build ]; then \
		mkdir build; \
	fi

clean:
	rm -rf build
