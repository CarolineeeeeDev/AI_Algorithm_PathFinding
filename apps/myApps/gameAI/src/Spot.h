#pragma once
#include "ofMain.h"

class Spot {
public:
    int i, j;
    float f, g, h;
    bool wall;
    Spot* previous;
    std::vector<Spot*> neighbors;

    Spot(int x, int y);
    void addNeighbors(std::vector<std::vector<Spot>>& grid);
};
