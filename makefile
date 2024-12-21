# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Iinclude

# Directories
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build

# Executable name
TARGET = $ game.exe 

# Source files and object files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

# Default target
all: $(TARGET)

# Link the executable
$(TARGET): $(OBJS) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

# Compile each source file into an object file
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Ensure the build directory exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Clean build files
clean:
	rm -rf $(BUILD_DIR)/*.o $(TARGET)
