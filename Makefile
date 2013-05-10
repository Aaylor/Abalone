SOURCES=src/ai.c src/board.c src/game.c src/interface.c src/main.c
OBJECTS=$(SOURCES:.c=.o)
CFLAGS= -std=c89 -Wall -Wextra -pedantic -ansi -g
EXECFOLDER=bin
EXECUTABLE=bin/abalone

$(EXECUTABLE): $(OBJECTS)
	mkdir -p $(EXECFOLDER)
	gcc -o $(EXECUTABLE) $(OBJECTS)

%.o : %.c
	gcc -c $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS)

rclean:
	make clean
	rm -f bin/abalone

ngame:
	./bin/abalone
