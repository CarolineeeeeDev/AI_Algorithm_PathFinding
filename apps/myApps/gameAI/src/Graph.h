#pragma once
#include "Node.h"
#include <unordered_map>

class Graph {
public:
    std::unordered_map<int, Node*> nodes;

    void addNode(int id, float x, float y);
    void addEdge(int from, int to, float weight);
    Node* getNode(int id);
};
