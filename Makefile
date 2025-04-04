# Compiler
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

# Directories
SRC_DIR = src
INC_DIR = include
BIN_DIR = bin

# Files
SRCS = $(SRC_DIR)/main.cpp $(SRC_DIR)/EmergencyTree.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = $(BIN_DIR)/EmergencyResponseSystem

# Default target
all: build

# Build
build: $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile sources
$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp $(INC_DIR)/%.hpp
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c $< -o $@

# Clean compiled files
clean:
	rm -rf $(BIN_DIR) $(SRC_DIR)/*.o

# Run the program
run: build
	./$(TARGET)
