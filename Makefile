

CC = g++
CFLAGS = -g -Wall

all: test_ocr

test_ocr: bmplib.o test_ocr.o
	g++ -g -Wall -o test_ocr bmplib.o test_ocr.o

# example using MAKE variables $(CC) is replaced with g++, etc.
bmplib.o: bmplib.cpp
	$(CC) $(CFLAGS) -c bmplib.cpp

test_ocr.o: bmplib.h test_ocr.cpp
	$(CC) $(CFLAGS) -c test_ocr.cpp

clean:
	rm -f *.o test_ocr *~
