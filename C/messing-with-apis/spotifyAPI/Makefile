SOURCES = main.c $(LIB_OUTPUT)
TARGET = main

REQUEST_SOURCE != find ../libs/request.c

LIB_OUTPUT = ../libs/request.o

CC = gcc
CCFLAGS = -g -Wall 
LIBSFLAGS = -c -g -Wall 

LIBS_CURL != curl-config --libs
LIBS_CJSON != pkg-config libcjson --libs --cflags


main : libs
	$(CC) main.c $(LIBSFLAGS) $(LIBS_CURL) $(LIBS_CJSON) -o $(TARGET)
	$(CC) $(SOURCES) $(CCFLAGS) $(LIBS_CURL) $(LIBS_CJSON) -o $(TARGET) 

libs : 
	$(CC) $(REQUEST_SOURCE) $(LIBSFLAGS) $(LIBS_CURL) $(LIBS_CJSON) -o ../libs/request.o
