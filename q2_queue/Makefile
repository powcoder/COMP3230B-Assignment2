CC = gcc
CFLAGS = -g -Wall -pthread -fopenmp

OBJ = main.o queue.o
DEPS = queue.h

all: testQ.out

testQ.out: $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@; rm $^

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean

run:
	./testQ.out

clean:
	rm -f $(OBJ) *.out
