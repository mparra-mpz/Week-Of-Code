TARGET = blink
CC = gcc
CFLAGS = -c -g -Wall
LDFLAGS = -lm
LIBS = -lwiringPi

.PHONY: default all clean

default: $(TARGET)

OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
HEADERS = $(wildcard *.h)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -Wall $(LIBS) -o $@

all: default

clean:
	-rm -f *.o
	-rm -f $(TARGET)
