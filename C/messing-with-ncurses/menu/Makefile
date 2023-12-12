SOURCES = menu.c
TARGET = menuStatic
CC = gcc
LIBS != pkg-config ncurses --libs --static --cflags
CCFLAGS = -g -Wall -static $(LIBS)

$(TARGET) : $(SOURCES)
	$(CC) $(SOURCES) $(CCFLAGS) -o $(TARGET) 
