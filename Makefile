CC = g++
CFLAGS = -g -Wall
OBJECTS = antSim.o genericObject.o ant.o chunk.o
TARGET = antSim

all: $(TARGET)

$(TARGET): antSim.o genericObject.o ant.o chunk.o
	$(CC) $(CFLAGS) -o builds/$(TARGET) builds/objects/antSim.o builds/objects/genericObject.o builds/objects/ant.o builds/objects/chunk.o 

antSim.o: src/antSim.cpp
	$(CC) $(CFLAGS) -c src/antSim.cpp
	mv antSim.o builds/objects/ 

ant.o: src/ant.cpp
	$(CC) $(CFLAGS) -c src/ant.cpp
	mv ant.o builds/objects/

genericObject.o: src/genericObject.cpp
	$(CC) $(CFLAGS) -c src/genericObject.cpp 
	mv genericObject.o builds/objects/

chunk.o: src/chunk.cpp
	$(CC) $(CFLAGS) -c src/chunk.cpp
	mv chunk.o builds/objects/

clean:
	$(RM) builds/$(TARGET) builds/objects/*.o 
