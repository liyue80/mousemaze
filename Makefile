OUTPUT = main.exe
CC = gcc

ifeq ($(DEBUG),YES)
	CFLAGS = -O -g -pipe -D_DEBUG
	LDFLAGS = -g
else
	CFLAGS = -Ofast
	#-minline-all-stringops
	#-pipe -mmmx -msse3 
	LDFLAGS = -Wl,-O2 -Wl,--as-needed -s
endif

all: main.c
	$(CC) $(CFLAGS) $(LDFLAGS) main.c -o $(OUTPUT)

clean:
	del *.o
	del $(OUTPUT)
	del elis.exe

elis: cpe.c
	$(CC) $(CFLAGS) $(LDFLAGS) cpe.c -o elis.exe

	
# gcc -Ofast -Wl,--as-needed -s main.c -o main.exe
