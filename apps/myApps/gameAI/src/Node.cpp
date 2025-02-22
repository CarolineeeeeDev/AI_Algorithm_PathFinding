#include "Node.h"

Node::Node(int id, float x, float y) : id(id), x(x), y(y), f(0), g(0), h(0),isObstacle(false), previous(nullptr) {}


void Node::addNeighbor(Node* neighbor, float weight) {
    neighbors[neighbor] = weight;
}
