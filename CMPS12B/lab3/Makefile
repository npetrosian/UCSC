#------------------------------------------------------------------------------
# Makefile for charType.c with Macros
# File name: Makefile
# Name: Natalie Petrosian
# Class: 12M
# CruzID: npetrosi
# Compiles charType.c 
#------------------------------------------------------------------------------

FLAGS = -std=c99 -Wall
SOURCES = charType.c
OBJECTS = charType.o
EXEBIN = charType

all: $(EXEBIN)

$(EXEBIN) : $(OBJECTS)
	gcc -o $(EXEBIN) $(OBJECTS)

$(OBJECTS) : $(SOURCES)
	gcc -c $(FLAGS) $(SOURCES)

clean :
	rm $(EXEBIN) $(OBJECTS)

