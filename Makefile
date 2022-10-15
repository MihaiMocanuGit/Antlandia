CC = g++
CFLAGS = -g -fsanitize=address -Wall -O0
OBJECTS = antSim.o genericObject.o ant.o chunk.o objectHolder.o objectOrganizer.o
TARGET = antSim
LIBS = -lsfml-graphics -lsfml-window -lsfml-system
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o builds/$(TARGET) $(LIBS)  builds/objects/antSim.o builds/objects/genericObject.o builds/objects/ant.o builds/objects/chunk.o builds/objects/objectHolder.o builds/objects/objectOrganizer.o 

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

objectHolder.o: src/objectHolder.cpp
	$(CC) $(CFLAGS) -c src/objectHolder.cpp
	mv objectHolder.o builds/objects/

objectOrganizer.o: src/objectOrganizer.cpp
	$(CC) $(CFLAGS) -c src/objectOrganizer.cpp
	mv objectOrganizer.o builds/objects/

clean:
	$(RM) builds/$(TARGET) builds/objects/*.o

run:
	make && builds/./antSim
