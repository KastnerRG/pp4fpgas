# Define the compiler
CXX=g++

# Compiler flags
CXXFLAGS=-std=c++11 `pkg-config --cflags opencv4`

# Linker flags
LDFLAGS=`pkg-config --libs opencv4`

# Target executable names
TARGET1=video_2dfilter_opencv
TARGET2=compare_images_opencv

# Source files for each target
SOURCES1=video_2dfilter_opencv.cpp
SOURCES2=compare_images_opencv.cpp

# Object files for each target
OBJECTS1=$(SOURCES1:.cpp=.o)
OBJECTS2=$(SOURCES2:.cpp=.o)

# Rule to create object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Default rule to make
all: $(TARGET1) $(TARGET2)

$(TARGET1): $(OBJECTS1)
	$(CXX) $(OBJECTS1) -o $(TARGET1) $(LDFLAGS)

$(TARGET2): $(OBJECTS2)
	$(CXX) $(OBJECTS2) -o $(TARGET2) $(LDFLAGS)

# Rule for cleaning files generated during compilation
clean:
	rm -f $(OBJECTS1) $(TARGET1) $(OBJECTS2) $(TARGET2)