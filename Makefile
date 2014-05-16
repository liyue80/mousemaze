OUTPUT = main.exe

ifeq ($(DEBUG),YES)
	OBJS = main.o
	CFLAGS = -O -g -pipe -D_DEBUG
	LDFLAGS = -g
else
	OBJS = main.o
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
	del elis.exe

elis:
	$(CC) $(CFLAGS) $(LDFLAGS) cpe.c -o elis.exe
