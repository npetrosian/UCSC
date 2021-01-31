#------------------------------------------------------------------------------ 
# A Makefile with macros 
# Name: Natalie Petrosian
# CruzID: npetrosi
# Class: 12B
# File name: Makefile
# This Makefile compiles the Java source file into a class file and creates a 
# temporary Manifest file, which it uses to create the Recursion jar file.
#------------------------------------------------------------------------------

JAVASRC   = Autocomplete.java BinarySearchDeluxe.java Term.java
SOURCES   = Makefile $(JAVASRC)
MAINCLASS = Autocomplete
CLASSES   = Autocomplete.class BinarySearchDeluxe.class Term.class
JARFILE   = Autocomplete

all: $(JARFILE)

$(JARFILE): $(CLASSES)
	echo Main-class: $(MAINCLASS) > Manifest
	jar cvfm $(JARFILE) Manifest $(CLASSES)
	rm Manifest
	chmod +x $(JARFILE)

$(CLASSES): $(JAVASRC)
	javac -Xlint $(JAVASRC)

clean:
	rm $(JARFILE) *.class




