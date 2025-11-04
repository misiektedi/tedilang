CXX = g++
CXXFLAGS = -Wall -g -std=c++23 -Isrc/include

SOURCES = $(wildcard src/*.cpp) $(wildcard src/core/*.cpp)
OBJECTS = $(SOURCES:src/%.cpp=obj/%.o)
TARGET = bin/tedilang

all: $(TARGET)
	$(MAKE) clean

$(TARGET): $(OBJECTS)
	mkdir -p bin
	$(CXX) $(CXXFLAGS) -o $@ $^

obj/%.o: src/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf obj