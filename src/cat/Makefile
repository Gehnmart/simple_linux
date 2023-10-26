CC = gcc

CFLAGS = -Wall -Werror -Wextra -std=c11

all: main

main: cat.o
	$(CC) -o s21_cat cat.o

cat.o: cat.c
	$(CC) $(CFLAGS) -c cat.c

clear:
	rm -rf cat.o a.out