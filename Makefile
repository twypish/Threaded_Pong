## Makefile for Lab4

CC=gcc
CFLAGS=-c -Wall -Wextra -g
## -lm to link the math library
LDFLAGS=-lncurses -pthread -lm
SOURCES =  paddle.c ball.c field.c scoreboard.c game.c menu.c driver.c
OBJECTS=$(SOURCES:.c=.o)
## lab4.out for the executable name
EXECUTABLE=pong.out

all: $(SOURCES) $(EXECUTABLE) 

# pull in dependency info for *existing* .o files
-include $(OBJECTS:.o=.d)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.c.o: 
	$(CC) $(CFLAGS) $< -o $@
	$(CC) -MM $< > $*.d

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE) *.d
