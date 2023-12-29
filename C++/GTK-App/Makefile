TARGET = main
CC = g++
CFLAGS = -Wall -g -static
LIBS != pkg-config gtkmm-4.0 --static --libs --cflags

$(TARGET) : main.cpp
	$(CC) main.cpp -o $(TARGET) $(CFLAGS) $(LIBS)
