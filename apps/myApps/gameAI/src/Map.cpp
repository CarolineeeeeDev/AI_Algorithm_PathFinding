#include "Map.h"
#include "Node.h"
#include <cstdlib>

Map::Map(int width, int height, int cellSize)
    : gridWidth(width), gridHeight(height), cellSize(cellSize), start(nullptr), end(nullptr) {
    Initialize();
}

Map::~Map() {
    for (auto& pair : nodes) {
        delete pair.second;
    }
}

void Map::Initialize() {
    for (int j = 0; j < gridHeight; ++j) {
        for (int i = 0; i < gridWidth; ++i) {
            int nodeId = i + j * gridWidth;
            Node* node = new Node(nodeId, i * cellSize, j * cellSize);
            nodes[nodeId] = node;
        }
    }

    markObstacles();

    for (int j = 0; j < gridHeight; ++j) {
        for (int i = 0; i < gridWidth; ++i) {
            int nodeId = i + j * gridWidth;
            Node* node = nodes[nodeId];

            // Horizontal and vertical neighbors
            if (i > 0) {
                addNeighbor(node, nodes[nodeId - 1]); // Left
            }
            if (i < gridWidth - 1) {
                addNeighbor(node, nodes[nodeId + 1]); // Right
            }
            if (j > 0) {
                addNeighbor(node, nodes[nodeId - gridWidth]); // Up
            }
            if (j < gridHeight - 1) {
                addNeighbor(node, nodes[nodeId + gridWidth]); // Down
            }

            // Diagonal neighbors
            if (i > 0 && j > 0 && !nodes[nodeId - gridWidth]->isObstacle && !nodes[nodeId - 1]->isObstacle) {
                addNeighbor(node, nodes[nodeId - gridWidth - 1]); // Top-left
            }
            if (i < gridWidth - 1 && j > 0 && !nodes[nodeId - gridWidth]->isObstacle && !nodes[nodeId + 1]->isObstacle) {
                addNeighbor(node, nodes[nodeId - gridWidth + 1]); // Top-right
            }
            if (i > 0 && j < gridHeight - 1 && !nodes[nodeId + gridWidth]->isObstacle && !nodes[nodeId - 1]->isObstacle) {
                addNeighbor(node, nodes[nodeId + gridWidth - 1]); // Bottom-left
            }
            if (i < gridWidth - 1 && j < gridHeight - 1 && !nodes[nodeId + gridWidth]->isObstacle && !nodes[nodeId + 1]->isObstacle) {
                addNeighbor(node, nodes[nodeId + gridWidth + 1]); // Bottom-right
            }
        }
    }

    start = nodes[0];
    end = nodes[gridWidth * gridHeight - 1];
}



void Map::markObstacles() {
    for (int i = 0; i < 50; ++i) {
        int x = rand() % gridWidth;
        int y = rand() % gridHeight;
        nodes[x + y * gridWidth]->isObstacle = true;
    }
}

void Map::addNeighbor(Node* node, Node* neighbor) {
    if (!neighbor->isObstacle) {
        node->neighbors[neighbor] = 1.0f; // Weight is 1
    }
}
