CC=gcc
CFLAGS=-std=c99 -Wall
EXEC=pcx2gif

$(EXEC): pcx2gif.o pcx.o gif.o
	$(CC) pcx2gif.o pcx.o gif.o -o $@
pcx2gif.o: pcx2gif.c pcx2gif.h pcx.h gif.h
	$(CC) $(CFLAGS) pcx2gif.c -c
pcx.o: pcx.c pcx.h pcx2gif.h
	$(CC) $(CFLAGS) pcx.c -c
gif.o: gif.c gif.h pcx2gif.h
	$(CC) $(CFLAGS) gif.c -c

clean:
	rm -f *.o $(EXEC)

