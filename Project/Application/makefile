# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

# Paths
APP_SRC_DIR = src
GEOMETRY_DIR = ../geometry/src
INCLUDE = -I../geometry/include
LDFLAGS = -L$(GEOMETRY_DIR) -llogic
OBJ = $(APP_SRC_DIR)/main.o
TARGET = $(APP_SRC_DIR)/main

# Ensure geometry library is built first
all: ../geometry/src/liblogic.so $(TARGET)

# Compile main.cpp to main.o
$(OBJ): $(APP_SRC_DIR)/main.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

# Link main.o with liblogic.so
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ) $(LDFLAGS)

# Clean compiled files
clean:
	rm -f $(OBJ) $(TARGET)
