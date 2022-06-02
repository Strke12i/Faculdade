gcc -c -o main.o main.c
gcc -c -o matriz.o matriz.c
gcc -o exec main.o matriz.c
./exec < entradas.txt
