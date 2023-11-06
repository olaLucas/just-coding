SOURCES = main.c
TARGET = main
CC = gcc
LIBS != curl-config --libs
CCFLAGS = -g -Wall $(LIBS)

main : main.c
	$(CC) $(SOURCES) $(CCFLAGS) -o $(TARGET) 