all: main.c clean bezier.o
	gcc main.c -lSDL

bezier.o: bezier.c
	gcc -c bezier.c

clean:
	rm -rf bezier.o a.out
