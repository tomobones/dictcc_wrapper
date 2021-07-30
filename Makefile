CC = gcc
SRC = lang_is_valid_id.c
CFLAGS = -c -ggdb -Wall
LFLAGS = -ggdb -Wall

all: clean a.out

compile: clean
	$(CC) $(CFLAGS) $(SRC)

a.out: compile
	$(CC) $(LFLAGS) *.o
	rm -f *.o

clean:
	rm -f a.out *.o
