#
# Author: Manuel Parra Z.
# Date: 03/01/2018
# License: MIT License
# Hardware:
# Description:
#

EXEC = BLINK
SCRIPTS =

CC = gcc
CPP =

CFLAGS = -c -g -Wall
CPPFLAGS =

LDFLAGS = -lwiringPi

SOURCES = blink.c
INCLUDES =

.PHONY: all clean

COBJECTS = $(SOURCES:.c=.o)
# CPPOBJECTS = $(SOURCES:.cpp=.o)

%.o: %.c $(INCLUDES)
	@echo " ... compile c objects from the sources."
	$(CC) $(CFLAGS) $< -o $@

# %.o: %.cpp $(INCLUDES)
# 	@echo " ... compile c++ objects from the sources."
# 	$(CPP) $(CPPFLAGS) $< -o $@

all: $(COBJECTS)
	@echo " ... compile and link c binary executables."
	$(CC) $(COBJECTS) $(LDFLAGS) -o $(EXEC)

# all: $(CPPOBJECTS)
# 	@echo " ... compile and link c++ binary executables."
# 	$(CPP) $(CPPOBJECTS) $(LDFLAGS) -o $(EXEC)

clean:
	@echo " . . . cleaning objects and executables."
	-rm -f *.o
	-rm -f $(EXEC)
