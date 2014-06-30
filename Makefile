OUTPUT = rc2_yue.exe
CC = gcc

ifeq ($(DEBUG),YES)
	CFLAGS = -O -g -pipe -D_DEBUG
	LDFLAGS = -g
else
	CFLAGS = -Os -pipe -march=core2
	LDFLAGS = -Wl,--as-needed
	#-Wl,-Os -s
endif

all: main.c
	$(CC) $(CFLAGS) $(LDFLAGS) main.c -o $(OUTPUT)

clean:
	del *.o
	del $(OUTPUT)
