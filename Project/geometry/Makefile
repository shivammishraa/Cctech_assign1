# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -fPIC

# Paths
SRC_DIR = src
INCLUDE_DIR = include
OBJ = $(SRC_DIR)/logic.o
TARGET = $(SRC_DIR)/liblogic.so
INCLUDE = -I$(INCLUDE_DIR)

# Rule to compile logic.cpp to logic.o
$(OBJ): $(SRC_DIR)/logic.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

# Rule to create shared library
$(TARGET): $(OBJ)
	$(CXX) -shared -o $@ $<

# Clean compiled files
clean:
	rm -f $(OBJ) $(TARGET)
