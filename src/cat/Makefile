CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11

all: s21_cat

s21_cat: s21_cat.o
	$(CC) -o s21_cat s21_cat.o

s21_cat.o: s21_cat.c
	$(CC) $(CFLAGS) -c s21_cat.c

clear:
	rm -rf cat.o s21_cat