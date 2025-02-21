#include "Spot.h"

Spot::Spot(int x, int y) : i(x), j(y), f(0), g(0), h(0), previous(nullptr) {
    wall = false;
}

void Spot::addNeighbors(std::vector<std::vector<Spot>>& grid) {
    if (i < grid.size() - 1) neighbors.push_back(&grid[i + 1][j]);
    if (i > 0) neighbors.push_back(&grid[i - 1][j]);
    if (j < grid[0].size() - 1) neighbors.push_back(&grid[i][j + 1]);
    if (j > 0) neighbors.push_back(&grid[i][j - 1]);
}
