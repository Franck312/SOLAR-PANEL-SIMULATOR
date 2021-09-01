CC = gcc
CFLAGS=-g

main.o: main.c csv.h
	gcc -c main.c

list.o: list.c list.h csv.h
	gcc -c list.c

csv.o: csv.c csv.h
	gcc -c csv.c

stat.o: stat.c stat.h
	gcc -c stat.c

solarpanel: main.o list.o csv.o stat.o
	gcc main.o list.o csv.o stat.o -o solarpanel -lm