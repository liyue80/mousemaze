ifeq ($(DEBUG),YES)
	CFLAGS = -O -g -pipe -D_DEBUG
	LDFLAGS = -g
else
	CFLAGS = -O2 -pipe -mmmx -msse3 -minline-all-stringops
	LDFLAGS = -Wl,-O2 -Wl,--as-needed -s
endif

all: main.o FastDeque.o FixedMemPool.o ParallelSpace.o StandardSpace.o
	$(CC) $(LDFLAGS) main.o FastDeque.o FixedMemPool.o ParallelSpace.o StandardSpace.o -o main.exe

main.o: main.c Common.h
	$(CC) $(CFLAGS) main.c -c

FastDeque.o: FastDeque.c FastDeque.h Common.h
	$(CC) $(CFLAGS) FastDeque.c -c

FixedMemPool.o: FixedMemPool.c FixedMemPool.h Common.h
	$(CC) $(CFLAGS) FixedMemPool.c -c

ParallelSpace.o: ParallelSpace.c ParallelSpace.h Common.h
	$(CC) $(CFLAGS) ParallelSpace.c -c

StandardSpace.o: StandardSpace.c StandardSpace.h Common.h
	$(CC) $(CFLAGS) StandardSpace.c -c

clean:
	del *.o
	del main.exe
