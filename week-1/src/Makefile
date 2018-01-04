#
# Author: Manuel Parra Z.
# Date: 03/01/2018
# License: MIT License
# Hardware:
# Description:
#

EXEC = BLINK
#SCRIPTS =

CC = gcc
#CXX =

CFLAGS = -c -g -Wall
#CXXFLAGS =

LDFLAGS = -lwiringPi

SOURCES = blink.c
INCLUDES =

.PHONY: all clean

OBJECTS = $(SOURCES:.c=.o)

%.o: %.c $(INCLUDES)
	@echo " ... compile c objects from the sources."
	$(CC) $(CFLAGS) $< -o $@

all: $(OBJECTS)
	@echo " ... compile and link c binary executables."
	$(CC) $(OBJECTS) $(LDFLAGS) -o $(EXEC)

clean:
	@echo " . . . cleaning objects and executables."
	-rm -f *.o
	-rm -f $(EXEC)
