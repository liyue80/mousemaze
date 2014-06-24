OUTPUT = rc2_yue.exe
CC = gcc

ifeq ($(DEBUG),YES)
	CFLAGS = -O -g -pipe -D_DEBUG
	LDFLAGS = -g
else
	CFLAGS = -Os -pipe
	LDFLAGS = -Wl,-Os -Wl,--as-needed -s
endif

all: main.c
	$(CC) $(CFLAGS) $(LDFLAGS) main.c -o $(OUTPUT)

clean:
	del *.o
	del $(OUTPUT)
