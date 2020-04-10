CC = gcc
CFLAGS = -g -Wall
HEADERS = def.h functii.h
OBJECTS = atm.o functii.o
EXEC = atm

.PHONY = default build clean

default: build

build: atm

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(EXEC): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

run: build
	./$(EXEC)

	
clean:
	-rm -f $(OBJECTS)
	-rm -f $(EXEC)