# Compiler
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -fPIC

# Paths
GEOMETRY_DIR = geometry
APPLICATION_DIR = Application
LIB_DIR = $(GEOMETRY_DIR)/lib
SRC_DIR = src
BIN_DIR = $(APPLICATION_DIR)/bin

# Include paths
INCLUDE = -I$(GEOMETRY_DIR)/include

# Object files
GEOMETRY_OBJ = $(GEOMETRY_DIR)/src/logic.o $(GEOMETRY_DIR)/src/shapes.o
APPLICATION_OBJ = $(APPLICATION_DIR)/src/main.o

# Targets
LIBRARY = $(LIB_DIR)/libgeometry.so
EXECUTABLE = $(BIN_DIR)/app

# Rule to build everything
all: $(LIBRARY) $(EXECUTABLE)

# Compile Geometry (Library)
$(GEOMETRY_DIR)/src/%.o: $(GEOMETRY_DIR)/src/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

# Create shared library
$(LIBRARY): $(GEOMETRY_OBJ)
	mkdir -p $(LIB_DIR)
	$(CXX) -shared -o $@ $^

# Compile Application
$(APPLICATION_DIR)/src/%.o: $(APPLICATION_DIR)/src/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

# Link Application with Geometry Library
$(EXECUTABLE): $(APPLICATION_OBJ) $(LIBRARY)
	mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $(APPLICATION_OBJ) -L$(LIB_DIR) -lgeometry -Wl,-rpath=$(LIB_DIR)

# Clean compiled files
clean:
	rm -f $(GEOMETRY_OBJ) $(APPLICATION_OBJ) $(LIBRARY) $(EXECUTABLE)

# Run the application
run: $(EXECUTABLE)
	./$(EXECUTABLE)
