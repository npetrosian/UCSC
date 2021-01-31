#------------------------------------------------------------------------------ 
# A Makefile with macros 
# Name: Natalie Petrosian
# CruzID: npetrosi
# Class: 12M
# File name: Makefile
# This Makefile compiles the Java source file into a class file and creates a 
# temporary Manifest file, which it uses to create the StarWarsBattle jar file.
#------------------------------------------------------------------------------

JAVASRC   = StarWarsBattle.java StarWars2.java SpaceShip.java XWing.java Tie.java
SOURCES   = README Makefile $(JAVASRC)
MAINCLASS = StarWarsBattle
CLASSES   = StarWarsBattle.class StarWars2.class SpaceShip.class XWing.class Tie.class
JARFILE   = StarWarsBattle

all: $(JARFILE)

$(JARFILE): $(CLASSES)
	echo Main-class: $(MAINCLASS) > Manifest
	jar cvfm $(JARFILE) Manifest $(CLASSES)
	rm Manifest
	chmod +x $(JARFILE)

$(CLASSES): $(JAVASRC)
	javac -Xlint $(JAVASRC)

clean:
	rm $(CLASSES) $(JARFILE)
