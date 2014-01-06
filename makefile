all:
	gcc -c main_stegano.c -o main_stegano.o
	gcc -c stegano.c -o stegano.o
	gcc main_stegano.o stegano.o -o stegano
