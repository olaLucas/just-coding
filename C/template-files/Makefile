CC = gcc
SOURCE = main.c
BIN = main
FLAGS = -g -o

build: main.c
	$(CC) $(SOURCE) $(FLAGS) $(BIN)

install: $(BIN)
	sudo cp $(BIN) /usr/bin/$(BIN)

uninstall:
	sudo rm /usr/bin/$(BIN)

clean:
	rm $(BIN)
