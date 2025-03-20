CXX=g++
CXXFLAGS=-fopenmp -Wall
TARGET=sections

all: $(TARGET)

$(TARGET): sections.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) sections.cpp

clean:
	rm -f $(TARGET)
