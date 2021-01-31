#------------------------------------------------------------------------------
# Makefile for FileReverse.c with Macros
#------------------------------------------------------------------------------

FLAGS = -std=c99 -Wall
SOURCES = FileReverse.c
OBJECTS = FileReverse.o
EXEBIN = FileReverse

all: $(EXEBIN)

$(EXEBIN) : $(OBJECTS)
	gcc -o $(EXEBIN) $(OBJECTS)

$(OBJECTS) : $(SOURCES)
	gcc -c $(FLAGS) $(SOURCES)

clean :
	rm $(EXEBIN) $(OBJECTS)

