CC = gcc
CFLAGS = -Wall -L. -g

all: stringProg

stringProg: main.o libstring_properties.a
	$(CC) $(CFLAGS) $< -lstring_properties -o $@

main.c: string_properties.h

libstring_properties.a: string_properties.o
	ar rcs $@ $^

string_properties.o: string_properties.h

clean:
	rm -f *.o *.a *~ stringProg

.PHONY: all clean
