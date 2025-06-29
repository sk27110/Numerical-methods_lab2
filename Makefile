CXX := g++
CXXFLAGS := -std=c++11 -Wall -Wextra -O3 -I.

TARGET := geodetic_test
SOURCES := geodetic.cpp test_geodetic.cpp
OBJECTS := $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp geodetic.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJECTS)

test: $(TARGET)
	./$(TARGET)

.PHONY: all clean test