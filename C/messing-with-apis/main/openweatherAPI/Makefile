SOURCES = main.c $(LIB_OUTPUT)
TARGET = main
CC = gcc 

LIBS_CURL != curl-config --libs
LIBS_CJSON != pkg-config libcjson --libs --cflags
LIBS_NCURSES != pkg-config ncurses --libs --cflags

main : request.o interface.o main.o
	$(CC) main.o ../libs/request.o -g -Wall  $(LIBS_CURL) $(LIBS_CJSON) -o $(TARGET) 

main.o : main.c
	$(CC) main.c -c -g -Wall -o main.o

interface.o :  ../libs/interface.c ../libs/interface.h
	$(CC) ../libs/interface.c -c -g -Wall -o ../libs/interface.o

request.o :  ../libs/request.c ../libs/request.h
	$(CC) ../libs/request.c -c -g -Wall -o ../libs/request.o

clean :
	rm $(TARGET)
	rm main.o
	rm ../libs/request.o
	rm ../libs/interface.o