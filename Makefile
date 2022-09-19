CC = g++
CFLAGS = -g -Wall
OBJECTS = antSim.o genericObject.o ant.o
TARGET = antSim

all: $(TARGET)

$(TARGET): antSim.o genericObject.o ant.o
	$(CC) $(CFLAGS) -o builds/$(TARGET) builds/objects/antSim.o builds/objects/genericObject.o builds/objects/ant.o 

antSim.o: src/antSim.cpp
	$(CC) $(CFLAGS) -c src/antSim.cpp
	mv antSim.o builds/objects/ 

ant.o: src/ant.cpp
	$(CC) $(CFLAGS) -c src/ant.cpp
	mv ant.o builds/objects/

genericObject.o: src/genericObject.cpp
	$(CC) $(CFLAGS) -c src/genericObject.cpp 
	mv genericObject.o builds/objects/


clean:
	$(RM) builds/$(TARGET) builds/objects/*.o 
