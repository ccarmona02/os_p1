CC=gcc

CFLAGS=-Wall -Werror


%.o: %.c 
	$(CC) -c -o $@ $< $(CFLAGS)


all:	cat size ls

	
cat:	mycat.o
	$(CC) $(CFLAGS) -o mycat  mycat.o 

size:	mysize.o
	$(CC) $(CFLAGS)  -o mysize  mysize.o

ls: 	myls.o
	$(CC) $(CFLAGS)  -o myls myls.o


clean:
	rm -f mycat myls mysize
	rm *.o
