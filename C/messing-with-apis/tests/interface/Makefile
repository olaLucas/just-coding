SOURCES = interface.c
TARGET = interface
CC = gcc
LIBS != pkg-config ncurses --libs --cflags
CCFLAGS = -g -Wall $(LIBS)

$(TARGET) : $(SOURCES)
	$(CC) $(SOURCES) $(CCFLAGS) -o $(TARGET) 