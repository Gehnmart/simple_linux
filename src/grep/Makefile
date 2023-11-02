CC = gcc

CFLAGS = -Wall -Werror -Wextra -std=c11

all: s21_grep

s21_grep: s21_grep.o parce_grep.o re_grep.o
	$(CC) -o s21_grep s21_grep.o parce_grep.o re_grep.o

s21_grep.o: s21_grep.c
	$(CC) $(CFLAGS) -c s21_grep.c

parce_grep.o: parce_grep.c
	$(CC) $(CFLAGS) -c parce_grep.c

re_grep.o: re_grep.c
	$(CC) $(CFLAGS) -c re_grep.c

clear:
	rm -rf s21_grep.o parce_grep.o re_grep.o s21_grep