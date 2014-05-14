all: FastDeque.o FixedMemPool.o main.o ParallelSpace.o
	gcc -o main.exe FastDeque.o FixedMemPool.o main.o ParallelSpace.o

FastDeque.o: FastDeque.c FastDeque.h Common.h
	gcc -c FastDeque.c

FixedMemPool.o: FixedMemPool.c FixedMemPool.h Common.h
	gcc -c FixedMemPool.c

ParallelSpace.o: ParallelSpace.c ParallelSpace.h Common.h
	gcc -c ParallelSpace.c

main.o: main.c Common.h
	gcc -c main.c
