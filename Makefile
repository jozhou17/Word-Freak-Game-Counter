all: wordfreak
hw3.o: hw3.c hw3.h
	gcc -c hw3.c -o hw3.o
bst.o: bst.c bst.h
	gcc -c bst.c -o bst.o
wordfreak: hw3.o bst.o 
	gcc hw3.o bst.o -o wordfreak
