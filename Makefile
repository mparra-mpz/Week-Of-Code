#
# Author: Manuel Parra Z.
# Date: 03/01/2018
# License: MIT License
# Hardware:
# Description:
#

EXEC =
SCRIPTS =

CC =
CPP =

CFLAGS =
CPPFLAGS =

LDFLAGS =

SOURCES =
INCLUDES =

COBJECTS = $(SOURCES:.c=.o)
CPPOBJECTS = $(SOURCES:.cpp=.o)

%.o: %.c $(INCLUDES)
	@echo " ... compile c objects from the sources."
	$(CC) $(CFLAGS) $< -o $@

%.o: %.cpp $(INCLUDES)
	@echo " ... compile c++ objects from the sources."
	$(CPP) $(CPPFLAGS) $< -o $@

.PHONY: all
all: $(COBJECTS)
	@echo " ... compile and link c binary executables."
	$(CC) $(COBJECTS) $(LDFLAGS) -o $(EXEC)

.PHONY: all
all: $(CPPOBJECTS)
	@echo " ... compile and link c++ binary executables."
	$(CPP) $(CPPOBJECTS) $(LDFLAGS) -o $(EXEC)

.PHONY: clean
clean:
	@echo " . . . cleaning objects and executables."
	-rm -f *.o
	-rm -f $(EXEC)
