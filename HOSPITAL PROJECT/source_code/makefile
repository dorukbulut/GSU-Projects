all: main.o functions.o
	gcc main.o functions.o -o main -lm

main.o: main.c functions.h
	gcc -I . -c main.c 

functions.o: functions.c functions.h
	gcc -I . -c functions.c 

clean:
	rm -rf *.o
	rm main 