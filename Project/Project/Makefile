# Compiler Settings
CXX = g++
CXXFLAGS = -Wall -std=c++17 -Igeometry/include -D_DLL

# Directories
BIN_DIR = bin
DATA_DIR = data
SRC_DIR = application/src
GEOM_SRC_DIR = geometry/src
GEOM_INC_DIR = geometry/include

# Executable and DLL Targets
TARGET = $(BIN_DIR)/shape_plotter.exe
DLL_TARGET = $(BIN_DIR)/geometry.dll
LIBRARY = $(BIN_DIR)/libgeometry.a

# Object Files
OBJ = $(patsubst $(SRC_DIR)/%.cpp, $(BIN_DIR)/%.o, $(wildcard $(SRC_DIR)/*.cpp)) \
      $(patsubst $(GEOM_SRC_DIR)/%.cpp, $(BIN_DIR)/%.o, $(wildcard $(GEOM_SRC_DIR)/*.cpp))

# Build the final executable
$(TARGET): $(OBJ) $(DLL_TARGET)
	$(CXX) $(OBJ) -o $(TARGET) -lm -L$(BIN_DIR) -lgeometry

# Compile the DLL
$(DLL_TARGET): $(GEOM_SRC_DIR)/transform_utils.o $(GEOM_SRC_DIR)/plot_utils.o $(GEOM_SRC_DIR)/objToStl.o $(GEOM_SRC_DIR)/stl_shape.o \
               $(GEOM_SRC_DIR)/cuboid.o $(GEOM_SRC_DIR)/cylinder.o $(GEOM_SRC_DIR)/sphere.o $(GEOM_SRC_DIR)/polyline.o $(GEOM_SRC_DIR)/bezier.o \
               $(GEOM_SRC_DIR)/triangle.o $(GEOM_SRC_DIR)/polygon.o $(GEOM_SRC_DIR)/line3D.o $(GEOM_SRC_DIR)/scene.o
	$(CXX) -shared $(CXXFLAGS) -o $(DLL_TARGET) $^ -Wl,--out-implib,$(LIBRARY)

# Compile source files in application/src to object files in bin/
$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile source files in geometry/src to object files in bin/
$(BIN_DIR)/%.o: $(GEOM_SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	@echo Cleaning up build files...
	@for %%f in ($(BIN_DIR)\*.o) do del /q /f %%f
	@for %%f in ($(BIN_DIR)\*.exe) do del /q /f %%f
	@for %%f in ($(BIN_DIR)\*.dll) do del /q /f %%f
	@for %%f in ($(BIN_DIR)\*.a) do del /q /f %%f
	@for %%f in ($(DATA_DIR)\*.dat) do del /q /f %%f
	@if exist $(BIN_DIR)\libgeometry.a del /q /f $(BIN_DIR)\libgeometry.a


# Build and run the project
run: $(TARGET)
	@echo "Starting program..."
	@$(BIN_DIR)/shape_plotter.exe
