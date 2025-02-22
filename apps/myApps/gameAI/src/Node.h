#pragma once
#include <vector>
#include <unordered_map>

class Node {
public:
    int id;
    float x, y;
    float f, g, h;
    Node* previous;
    std::unordered_map<Node*, float> neighbors;
    bool isObstacle;
    Node(int id, float x, float y);
    void addNeighbor(Node* neighbor, float weight);
};
