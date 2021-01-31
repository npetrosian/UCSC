#------------------------------------------------------------------------------
# Name: Natalie Petrosian
# UserID: npetrosi
# Assignment: PA3
#
# Makefile for CMPS 101-01 Programming Assignment 3
#
#       make                   makes DigraphProperties
#       make GraphProperties   makes DigraphProperties
#------------------------------------------------------------------------------

DigraphProperties: DigraphProperties.o Digraph.o List.o Stack.o Queue.o
		gcc -g -o DigraphProperties DigraphProperties.o List.o Digraph.o Stack.o Queue.o

DigraphProperties.o : DigraphProperties.c List.h Digraph.h 
		gcc -g -c -std=c99 -Wall DigraphProperties.c 

Digraph.o : Digraph.c Digraph.h
		gcc -g -c -std=c99 -Wall Digraph.c

List.o	: List.c List.h 
		gcc -g -c -std=c99 -Wall List.c

Stack.o	: Stack.c Stack.h
		gcc -g -c -std=c99 -Wall Stack.c

Queue.o	: Queue.c Queue.h
		gcc -g -c -std=c99 -Wall Queue.c

clean :
		rm -f  DigraphProperties DigraphProperties.o List.o Digraph.o Stack.o Queue.o
