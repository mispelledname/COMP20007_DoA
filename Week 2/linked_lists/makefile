main: main.o list.o
	gcc -Wall -o main main.o list.o

main.o: main.c list.h
	gcc -Wall -c main.c

list.o: list.c list.h
	gcc -Wall -c list.c