OUTPUT = main.exe
CC = gcc

ifeq ($(DEBUG),YES)
	OBJS = main.o
	CFLAGS = -O -g -pipe -D_DEBUG
	LDFLAGS = -g
else
	OBJS = main.o
	CFLAGS = -O3
	#-minline-all-stringops
	#-pipe -mmmx -msse3 
	LDFLAGS = -Wl,-O3 -Wl,--as-needed -s
endif

all: $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(OUTPUT)

%.o: %.c %.h
	$(CC) $(CFLAGS) $< -c -o $@

clean:
	del *.o
	del $(OUTPUT)
	del elis.exe

elis:
	$(CC) $(CFLAGS) $(LDFLAGS) cpe.c -o elis.exe
