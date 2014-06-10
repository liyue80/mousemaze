OUTPUT = main.exe
CC = gcc

ifeq ($(DEBUG),YES)
	CFLAGS = -O -g -pipe -D_DEBUG
	LDFLAGS = -g
else
	CFLAGS = -Os -pipe
	#CFLAGS = -O3 -pipe -fomit-frame-pointer -fforce-addr -falign-functions=4 -fprefetch-loop-arrays -march=pentium3
	#-fomit-frame-pointer -march=pentium4
	#-minline-all-stringops
	#-pipe -mmmx -msse3 
	LDFLAGS = -Wl,-Os -Wl,--as-needed -s
	
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
