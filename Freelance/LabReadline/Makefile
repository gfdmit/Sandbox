CC = gcc
CFLAGS = -Wall -g #-Wextra

UTILS = lineUtils/lineUtils.c mystring/mystring.c

all: build

build: 
	$(CC) $(CFLAGS) $(UTILS) -o lab4a main/lab4a.c -lreadline
	$(CC) $(CFLAGS) $(UTILS) -o lab4b main/lab4b.c

clear:
	rm -f lab4a lab4b nothing.txt

test: build
	./lab4a < testfiles/test1.txt
	./lab4b < testfiles/test1.txt

valgrind: build
	valgrind -s --leak-check=full --track-origins=yes ./lab4a < testfiles/test1.txt 
	valgrind -s --leak-check=full --track-origins=yes ./lab4b < testfiles/test1.txt 

time: build
	time ./lab4a < testfiles/test2.txt > nothing.txt
	time ./lab4b < testfiles/test2.txt > nothing.txt

.PHONY: all run clear test valgrind time build
