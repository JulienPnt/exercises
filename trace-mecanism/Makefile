CC=gcc
CFLAGS=-std=c17 -W -Wall
LDFLAGS=
EXEC=main

all: $(EXEC)

main: build main.o logs.o
	$(CC) -o build/main build/main.o build/logs.o

main.o: src/main.c
	$(CC) -o build/main.o -c src/main.c $(CFLAGS)

logs.o: src/logs.c
	$(CC) -o build/logs.o -c src/logs.c $(CFLAGS)

build:
	if ! [ -d build ]; then \
		mkdir build; \
	fi

clean:
	rm -rf build
