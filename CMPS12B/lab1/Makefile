#------------------------------------------------------------------------------ 
# A Makefile with macros 
# Name: Natalie Petrosian
# CruzID: npetrosi
# Class: 12M
# File name: Makefile
# This Makefile compiles the Java source files into class files and creates a 
# temporary Manifest file, which it uses to create the Hello jar file.
#------------------------------------------------------------------------------

JAVASRC   = HelloUser.java HelloUser2.java
SOURCES   = README Makefile $(JAVASRC)
MAINCLASS = HelloUser2
CLASSES   = HelloUser.class HelloUser2.class
JARFILE   = Hello

all: $(JARFILE)

$(JARFILE): $(CLASSES)
	echo Main-class: $(MAINCLASS) > Manifest
	jar cvfm $(JARFILE) Manifest $(CLASSES)
	rm Manifest
	chmod +x $(JARFILE)

$(CLASSES): $(JAVASRC)
	javac -Xlint $(JAVASRC)

clean:
	rm $(CLASSES)
