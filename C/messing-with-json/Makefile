TARGET = main
SOURCES = main.c
CC = gcc
LIBS != pkg-config libcjson --cflags --libs
CCFLAGS = -g -Wall $(LIBS)

main : main.c
	$(CC) $(SOURCES) $(CCFLAGS) -o $(TARGET)

test : test.c
	$(CC) test.c $(CCFLAGS) -o test