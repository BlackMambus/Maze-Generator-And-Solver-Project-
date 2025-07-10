CXX = g++
CXXFLAGS = -std=c++17 -Iinclude

SRC = src/Maze.cpp src/main.cpp
OUT = maze_app

all:
    $(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)

clean:
    rm -f $(OUT)
