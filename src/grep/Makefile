CC = gcc

CFLAGS = -Wall -Werror -Wextra -std=c11

all: main

main: s21_grep.o
	$(CC) -o s21_grep s21_grep.o

s21_grep.o: s21_grep.c
	$(CC) $(CFLAGS) -c s21_grep.c

clear:
	rm -rf s21_grep.o s21_grep