TARGET = blink
CC = gcc
CFLAGS = -c -g -Wall
LDFLAGS = -lwiringPi

.PHONY: all clean

OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
HEADERS = $(wildcard *.h)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@

all: $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $(TARGET)

clean:
	-rm -f *.o
	-rm -f $(TARGET)
