CC = g++
CFLAGS = -g -fsanitize=address -Wall -O0
SRC_DIR = ./src
OBJ_DIR = ./builds/objects
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
TARGET = antSim
LIBS = -lsfml-graphics -lsfml-window -lsfml-system
all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o builds/$(TARGET) $(LIBS)  $^


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) builds/$(TARGET) builds/objects/*.o builds/objects/*.d

run:
	make && builds/./$(TARGET)

CFLAGS += -MMD
-include $(OBJ_FILES:.o=.d)
