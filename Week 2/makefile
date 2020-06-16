main: racecar_test.o racecar.o
	gcc -Wall -o main racecar_test.o racecar.o

racecar_test.o: racecar_test.c racecar.h
	gcc -Wall -c racecar_test.c

racecar.o: racecar.c racecar.h
	gcc -Wall -c racecar.c