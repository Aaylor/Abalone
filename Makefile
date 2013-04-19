SOURCES=src/ai.c src/board.c src/game.c src/interface.c src/main.c
OBJECTS=$(SOURCES:.c=.o)
CFLAGS= -std=c89 -Wall -Wextra -pedantic -ansi -g
EXECUTABLE=bin/abalone

$(EXECUTABLE): $(OBJECTS)
	gcc -o $(EXECUTABLE) $(OBJECTS)

%.o : %.c
	gcc -c $(CFLAGS) $< -o $@

launch:
	./bin/abalone

clean:
	rm -f $(EXECUTABLE) $(OBJECTS)
