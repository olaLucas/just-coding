TARGET = main
CC = g++
CFLAGS = -Wall
LIBS != pkg-config --cflags	--libs gtkmm-4.0

$(TARGET) : main.cpp
	$(CC) main.cpp -o $(TARGET) $(cflags) $(LIBS)