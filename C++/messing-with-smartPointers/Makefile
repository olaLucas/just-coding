TARGET = main
objects = main.o libs/stack.o

default : $(TARGET)

	rm -f $(objects)

$(TARGET) : $(objects)
	g++ -g main.o libs/stack.o -o main

main.o : main.cpp
	g++ -g -c main.cpp -o main.o

stack.o : libs/stack.cpp
	g++ -g -c libs/stack.cpp -o libs/stack.o