#ifndef MAZE_HPP
#define MAZE_HPP

#include <vector>
#include <utility>

class Maze {
private:
    int width, height;
    std::vector<std::vector<char>> grid;
    std::vector<std::vector<bool>> visited;

    void generateMaze(int x, int y);
    bool isValid(int x, int y);
    void shuffleDirections(std::vector<std::pair<int, int>>& dirs);

public:
    Maze(int w, int h);
    void create();
    bool solve();
    void display() const;
};

#endif
#include "Maze.hpp"
#include <iostream>
#include <algorithm>
#include <random>
#include <queue>

Maze::Maze(int w, int h) : width(w), height(h) {
    grid.resize(height, std::vector<char>(width, '#'));
    visited.resize(height, std::vector<bool>(width, false));
}

void Maze::shuffleDirections(std::vector<std::pair<int, int>>& dirs) {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(dirs.begin(), dirs.end(), g);
}

bool Maze::isValid(int x, int y) {
    return x > 0 && y > 0 && x < width - 1 && y < height - 1;
}

void Maze::generateMaze(int x, int y) {
    visited[y][x] = true;
    grid[y][x] = ' ';

    std::vector<std::pair<int, int>> directions = {{2, 0}, {-2, 0}, {0, 2}, {0, -2}};
    shuffleDirections(directions);

    for (auto [dx, dy] : directions) {
        int nx = x + dx, ny = y + dy;
        if (isValid(nx, ny) && !visited[ny][nx]) {
            grid[y + dy / 2][x + dx / 2] = ' ';
            generateMaze(nx, ny);
        }
    }
}

void Maze::create() {
    generateMaze(1, 1);
    grid[0][1] = 'S'; // Start
    grid[height - 1][width - 2] = 'E'; // End
}

bool Maze::solve() {
    std::queue<std::pair<int, int>> q;
    std::vector<std::vector<bool>> visitedSolve(height, std::vector<bool>(width, false));
    std::vector<std::vector<std::pair<int, int>>> parent(height, std::vector<std::pair<int, int>>(width, {-1, -1}));

    q.push({0, 1});
    visitedSolve[0][1] = true;

    std::vector<std::pair<int, int>> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    bool found = false;

    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        if (grid[y][x] == 'E') {
            found = true;
            break;
        }

        for (auto [dx, dy] : dirs) {
            int nx = x + dx, ny = y + dy;
            if (nx >= 0 && ny >= 0 && nx < width && ny < height &&
                (grid[ny][nx] == ' ' || grid[ny][nx] == 'E') && !visitedSolve[ny][nx]) {
                visitedSolve[ny][nx] = true;
                parent[ny][nx] = {x, y};
                q.push({nx, ny});
            }
        }
    }

    if (!found) return false;

    // Trace back path
    int x = width - 2, y = height - 1;
    while (grid[y][x] != 'S') {
        auto [px, py] = parent[y][x];
        if (grid[y][x] != 'E') grid[y][x] = '.';
        x = px; y = py;
    }

    return true;
}

void Maze::display() const {
    for (const auto& row : grid) {
        for (char cell : row)
            std::cout << cell;
        std::cout << '\n';
    }
}
#include "Maze.hpp"
#include <iostream>

int main() {
    int width = 21, height = 21;
    Maze maze(width, height);

    maze.create();
    std::cout << "Generated Maze:\n";
    maze.display();

    if (maze.solve()) {
        std::cout << "\nSolved Maze:\n";
        maze.display();
    } else {
        std::cout << "\nNo solution found.\n";
    }

    return 0;
}



