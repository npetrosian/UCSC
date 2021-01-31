#------------------------------------------------------------------------------
# Makefile for the Blockchain ADT and its test client
# Name: Natalie Petrosian
# Class: 12M
# CruzID: npetrosi
#------------------------------------------------------------------------------

ADT_NAME  = Blockchain
BLOCK     = Block
SOURCES   = $(ADT_NAME).c $(ADT_NAME)Client.c $(BLOCK).c
OBJECTS   = $(ADT_NAME).o $(ADT_NAME)Client.o $(BLOCK).o
HEADERS   = $(ADT_NAME).h $(BLOCK).h
EXEBIN    = $(ADT_NAME)Client
FLAGS     = -std=c99 -Wall

all: $(EXEBIN)

$(EXEBIN) : $(OBJECTS) $(HEADERS) Block.o Blockchain.o
	gcc -o $(EXEBIN) $(OBJECTS)

$(BLOCK) : $(BLOCK).c $(BLOCK).h 
	gcc -c $(BLOCK).c -o $(BLOCK).o 

$(ADT_NAME) : $(ADT_NAME).c $(ADT_NAME).h 
	gcc -c $(ADT_NAME).c -o $(ADT_NAME).o 

$(OBJECTS) : $(SOURCES) $(HEADERS) 
	gcc -c $(FLAGS) $(SOURCES)

clean :
	rm -f $(EXEBIN) $(OBJECTS) 

check:
	valgrind --leak-check=full $(EXEBIN) 
