CC=gcc
CFLAGS=-W -Wall -ansi -pedantic
LDFLAGS=
EXEC=main

all: $(EXEC)

main: build main.o
	$(CC) -o build/main build/main.o $(LDFLAGS)

main.o: src/main.c
	$(CC) -o build/main.o -c src/main.c $(CFLAGS)

build:
	if ! [ -d build ]; then \
		mkdir build; \
	fi

clean:
	rm -rf build
