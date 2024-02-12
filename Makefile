all: main.o matrix.o  algorithm.o
	gcc main.o matrix.o  algorithm.o -lm -o main -O2

main.o: main.c matrix.h  algorithm.h
	gcc main.c -c -o main.o -O2

matrix.o: matrix.c matrix.h
	gcc matrix.c -c -o matrix.o -O2

 algorithm.o:  algorithm.c  algorithm.h
	gcc  algorithm.c -c -o  algorithm.o -O2

clean:
	rm -f *.o
