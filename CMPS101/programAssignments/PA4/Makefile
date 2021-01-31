#------------------------------------------------------------------------------
# Name: Natalie Petrosian
# UserID: npetrosi
# Assignment: PA4
#
# Makefile for CMPS 101-01 Programming Assignment 4
#
#       make                   makes DigraphProperties
#       make GraphProperties   makes DigraphProperties
#------------------------------------------------------------------------------

DigraphProperties: DigraphProperties.o Digraph.o List.o
		gcc -o DigraphProperties DigraphProperties.o List.o Digraph.o

DigraphProperties.o : DigraphProperties.c List.h Digraph.h 
		gcc -c -std=c99 -Wall DigraphProperties.c 

Digraph.o : Digraph.c Digraph.h
		gcc -c -std=c99 -Wall Digraph.c

List.o	: List.c List.h 
		gcc -c -std=c99 -Wall List.c

clean :
		rm -f  DigraphProperties DigraphProperties.o List.o Digraph.o
