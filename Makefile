CC = gcc


all: myls mytail mystat mysearch

myls: myls-remington.c
	$(CC) -o myls myls-remington.c

mytail: mytail-remington.c
	$(CC) -o mytail mytail-remington.c

mystat: mystat-remington.c
	$(CC) -o mystat mystat-remington.c

mysearch: mysearch-remington.c
	$(CC) -o mysearch mysearch-remington.c

.PHONY: clean

clean:
	rm myls mytail mystat mysearch
