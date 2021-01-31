#------------------------------------------------------------------------------
#   Makefile for List ADT
#------------------------------------------------------------------------------

# Variables
JARFILE    = ListClient
MAINCLASS  = ListClient
SOURCES    = List.java ListInterface.java ListClient.java\
             ListIndexOutOfBoundsException.java ListTest.java
CLASSES    = List.class ListInterface.class ListClient.class List\$$Node.class\
             ListIndexOutOfBoundsException.class ListTest.class

# Build Targets
all: $(JARFILE)

$(JARFILE): $(CLASSES)
	echo Main-class: $(MAINCLASS) > Manifest
	jar cvfm $(JARFILE) Manifest $(CLASSES)
	rm Manifest
	chmod +x $(JARFILE)

$(CLASSES): $(SOURCES)
	javac -Xlint $(SOURCES)  

clean:
	rm -f $(CLASSES) $(JARFILE)
