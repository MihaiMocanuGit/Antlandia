CC = g++

CFLAGS = -g -Wall

TARGET = antSim

$(TARGET): src/$(TARGET).cpp
	$(CC) $(CFLAGS) -o builds/$(TARGET) src/$(TARGET).cpp

clean:
	$(RM) $(TARGET)
