SOURCES = main.c # source files
TARGET = main # final binary
CC = gcc # compiler

# the '!=' execute an shell command and takes the result
# in this case, i am using it to get the libs to link
# and others compilers flags that the lib needs
LIBS != pkg-config ncurses --libs --cflags

# compiler flags
CCFLAGS = -g -Wall $(LIBS)

# the recipe to make the final binary 
main : $(SOURCES)
	$(CC) $(SOURCES) $(CCFLAGS) -o $(TARGET) 

moving : movingWindows.c
		$(CC) movingWindows.c $(CCFLAGS) -o mov