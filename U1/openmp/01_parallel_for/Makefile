CXX=g++
CXXFLAGS=-fopenmp -Wall
TARGET=parallel_for

all: $(TARGET)

$(TARGET): parallel_for.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) parallel_for.cpp

clean:
	rm -f $(TARGET)
