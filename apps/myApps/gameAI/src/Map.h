#pragma once
#include "Node.h"
#include <unordered_map>
#include <vector>

class Map {
public:
    Map(int width, int height, int cellSize);
    ~Map();

    void Initialize();
    void markObstacles();
    void addNeighbor(Node* node, Node* neighbor);

    Node* getStart() const { return start; }
    Node* getEnd() const { return end; }
    std::unordered_map<int, Node*> const GetNodes() { return nodes;  }

    int gridWidth, gridHeight, cellSize;
    std::unordered_map<int, Node*> nodes;

private:
    Node* start;
    Node* end;
};
