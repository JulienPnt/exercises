CC=gcc
CFLAGS=-std=c17 -W -Wall -ansi -pedantic
LDFLAGS=
EXEC=main

all: $(EXEC)

main: build main.o ring_buffer.o timer.o unit_test.o
	$(CC) -o build/main build/main.o build/ring_buffer.o build/timer.o build/unit_test.o $(LDFLAGS)

main.o: timer.o src/main.c
	$(CC) -o build/main.o -c src/main.c $(CFLAGS)

ring_buffer.o: timer.o src/ring_buffer.c
	$(CC) -o build/ring_buffer.o -c src/ring_buffer.c $(CFLAGS)

timer.o: src/timer.c
	$(CC) -o build/timer.o -c src/timer.c $(CFLAGS)

unit_test.o: src/unit_test.c
	$(CC) -o build/unit_test.o -c src/unit_test.c $(CFLAGS)

build:
	if ! [ -d build ]; then \
		mkdir build; \
	fi

clean:
	rm -rf build
