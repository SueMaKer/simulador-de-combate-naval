
# Variables
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
TARGET = naval_warfare
SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)

# Targets principales
all: compile

compile:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

play: compile
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJ)