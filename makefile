CFLAGS=-g -O0 -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror
VFLAGS=--leak-check=full --track-origins=yes --show-reachable=yes

compilar:
	gcc $(CFLAGS) -o salon main.c salon.c util.c

valgrind: compilar
	valgrind $(VFLAGS) ./salon

test: compilar-test
	valgrind $(VFLAGS) ./pruebas

compilar-test:
	gcc $(CFLAGS) -o pruebas pruebas.c util.c salon.c
