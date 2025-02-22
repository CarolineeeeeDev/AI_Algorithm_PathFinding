#include "Graph.h"

void Graph::addNode(int id, float x, float y) {
    if (nodes.find(id) == nodes.end()) {
        nodes[id] = new Node(id, x, y);
    }
}


void Graph::addEdge(int from, int to, float weight) {
    nodes[from]->addNeighbor(nodes[to], weight);
}

Node* Graph::getNode(int id) {
    return nodes.find(id) != nodes.end() ? nodes[id] : nullptr;
}
