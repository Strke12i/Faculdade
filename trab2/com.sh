gcc -c main.c -o main.o
gcc -c heap.c -o heap.o
gcc main.o heap.o -o exec
