OUTPUT = main.exe

ifeq ($(DEBUG),YES)
	OBJS = main.o FastDeque.o FixedMemPool.o ParallelSpace.o StandardSpace.o Performance.o Common.o
	CFLAGS = -O -g -pipe -D_DEBUG -DPERFORMANCE_TEST
	LDFLAGS = -g
else
	OBJS = main.o FastDeque.o FixedMemPool.o ParallelSpace.o StandardSpace.o Common.o
	CFLAGS = -O2 -pipe -mmmx -msse3 -minline-all-stringops
	LDFLAGS = -Wl,-O2 -Wl,--as-needed -s
endif

all: $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(OUTPUT)

%.o: %.c %.h
	$(CC) $(CFLAGS) $< -c -o $@

clean:
	del *.o
	del $(OUTPUT)
