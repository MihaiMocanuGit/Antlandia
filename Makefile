CC = g++
CFLAGS = -g -Wall
OBJECTS = antSim.o genericObject.o ant.o
TARGET = antSim

all: $(TARGET)

$(TARGET): src/$(TARGET).cpp
	$(CC) $(CFLAGS) -o builds/$(TARGET) src/$(TARGET).cpp src/ant.cpp src/genericObject.cpp

clean:
	$(RM) $(TARGET)
