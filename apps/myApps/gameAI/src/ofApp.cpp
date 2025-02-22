#include "ofApp.h"

void ofApp::setup() {

    InitializeMap();
    InitializeBoid();
    
}

void ofApp::InitializeBoid()
{
    boid = new Boid();
    boid->rb.r = map->cellSize / 2;
    boid->rb.position = ofVec2f(start->x + map->cellSize/2, start->y  + map->cellSize/2);
}

void ofApp::update()
{
    if (!aStarPath.empty() && boid->currentTargetIndex!= aStarPath.size()) {
        Node* targetNode = aStarPath[boid->currentTargetIndex];
        ofVec2f targetPosition(targetNode->x + map->cellSize / 2,
            targetNode->y + map->cellSize / 2);
        ofVec2f force = boid->arrive(targetPosition);
        boid->rb.applyForce(force);
        float distanceToTarget = (boid->rb.position - targetPosition).length();
        if (distanceToTarget < 5.0f && boid->currentTargetIndex < aStarPath.size() - 1) {
            boid->currentTargetIndex++;
        }
        
    }
    
}


void ofApp::draw() {
    ofBackground(0);

    int gridWidth = map->gridWidth;
    int gridHeight = map->gridHeight;
    int cellSize = map->cellSize;

    // Draw the grid
    for (int i = 0; i < gridWidth; ++i) {
        for (int j = 0; j < gridHeight; ++j) {
            int nodeId = i + j * gridWidth;
            Node* node = nodes[nodeId];
            if (node->isObstacle) {
                // Draw obstacle in black
                ofSetColor(0, 0, 0);
                ofDrawRectangle(i * cellSize, j * cellSize, cellSize, cellSize);
            }
            else {
                // Draw walkable node in white
                ofSetColor(255, 255, 255);
                ofDrawRectangle(i * cellSize, j * cellSize, cellSize, cellSize);
            }
            if (end && node == end && !end->isObstacle)
            {
                ofSetColor(0, 255, 0);
                ofDrawRectangle(i * cellSize, j * cellSize, cellSize, cellSize);
            }
        }
    } 

    //draw path
    if (!aStarPath.empty() && boid->currentTargetIndex != aStarPath.size())
    {
        for (int i = boid->currentTargetIndex; i < aStarPath.size(); ++i)
        {
            ofSetColor(0, 0, 255);
            ofDrawCircle(aStarPath[i]->x  + cellSize/2, aStarPath[i]->y  + cellSize / 2, 5);
        }
    }
    
    boid->update();
    boid->show();
}


void ofApp::InitializeMap()
{
    int gridWidth = 40;
    int gridHeight = 40;
    int cellSize = 20;

    map = new Map(gridWidth, gridHeight, cellSize);
    nodes = map->nodes;
    start = nodes[0];
}

void ofApp::aStar() {
    auto startTime = std::chrono::high_resolution_clock::now();

    for (auto& pair : nodes) {
        Node* node = pair.second;
        node->g = std::numeric_limits<float>::max();
        node->previous = nullptr;
    }

    std::priority_queue<Node*, std::vector<Node*>, std::function<bool(Node*, Node*)>> pq(
        [](Node* left, Node* right) {
            return left->f > right->f;
        }
    );

    start->g = 0;
    start->h = heuristic(start, end);
    start->f = start->g + start->h;
    pq.push(start);

    while (!pq.empty()) {
        Node* current = pq.top();
        pq.pop();

        if (current == end) {
            break;
        }

        for (auto& neighborPair : current->neighbors) {
            Node* neighbor = neighborPair.first;
            if (neighbor->isObstacle) {
                continue;
            }
            float weight = neighborPair.second;

            float tentative_g = current->g + weight;
            if (tentative_g < neighbor->g) {
                neighbor->previous = current;
                neighbor->g = tentative_g;
                neighbor->h = heuristic(neighbor, end);
                neighbor->f = neighbor->g + neighbor->h;
                pq.push(neighbor);
            }
        }
    }

    Node* current = end;
    aStarPath.clear();
    while (current != nullptr) {
        aStarPath.push_back(current);
        current = current->previous;
    }
    std::reverse(aStarPath.begin(), aStarPath.end());
}

float ofApp::heuristic(Node* a, Node* b) {
    return std::sqrt(std::pow(a->x - b->x, 2) + std::pow(a->y - b->y, 2));
}

//heuristic2
//float ofApp::heuristic(Node* a, Node* b) {
//    return std::abs(a->x - b->x) + std::abs(a->y - b->y);
//}


void ofApp::keyPressed(int key) {
}

void ofApp::keyReleased(int key) {
}

void ofApp::mousePressed(int x, int y, int button) {

    if (!aStarPath.empty() && boid->currentTargetIndex != aStarPath.size()-1)
    {
        return; //pathfinding cannot be interrupted
    }

    int gridX = x / map->cellSize;
    int gridY = y / map->cellSize;

    if (gridX >= 40 || gridY >= 40) return;

    if (nodes[gridX + gridY * map->gridWidth]->isObstacle) return;

    end = nodes[gridX + gridY * map->gridWidth];

    aStar();
    boid->currentTargetIndex = 1;
    start = end;
    cout << endl;
    cout << "A* Path: ";
    for (auto* p : aStarPath) {
        cout << p->id << " ";
    }
}


void ofApp::mouseReleased(int x, int y, int button) {
}

void ofApp::mouseMoved(int x, int y) {
}

void ofApp::mouseDragged(int x, int y, int button) {
}

void ofApp::mouseEntered(int x, int y) {
}

void ofApp::mouseExited(int x, int y) {
}

void ofApp::windowResized(int w, int h) {
}

void ofApp::gotMessage(ofMessage msg) {
}

void ofApp::dragEvent(ofDragInfo dragInfo) {
}

//
//std::unordered_map<int, std::pair<float, float>> provinceCoords = {
//    {0, {50, 50}},
//    {1, {150, 50}},
//    {2, {100, 100}},
//    {3, {200, 100}},
//    {4, {300, 50}},
//    {5, {400, 80}},
//    {6, {450, 120}},
//    {7, {500, 200}},
//    {8, {600, 100}},
//    {9, {550, 150}},
//    {10, {600, 200}},
//    {11, {550, 250}},
//    {12, {650, 250}},
//    {13, {500, 300}},
//    {14, {400, 300}},
//    {15, {350, 350}},
//    {16, {450, 350}},
//    {17, {500, 400}},
//    {18, {600, 400}},
//    {19, {650, 500}},
//    {20, {600, 600}},
//    {21, {200, 500}},
//    {22, {250, 550}},
//    {23, {300, 600}},
//    {24, {350, 650}},
//    {25, {450, 650}},
//    {26, {300, 400}},
//    {27, {250, 350}},
//    {28, {150, 550}},
//    {29, {100, 500}},
//    {30, {50, 650}},
//    {31, {650, 150}},
//    {32, {675, 175}}
//};
//
//std::unordered_map<int, std::vector<int>> adjacencyList = {
//    {0, {1, 2}},
//    {1, {0, 2}},
//    {2, {0, 1, 3}},
//    {3, {2, 4}},
//    {4, {3, 5}},
//    {5, {4, 6, 7}},
//    {6, {5, 7}},
//    {7, {5, 6, 9}},
//    {8, {9, 10, 31}},
//    {9, {7, 8, 10, 11}},
//    {10, {8, 9, 32}},
//    {11, {9, 12}},
//    {12, {11, 13}},
//    {13, {12, 14}},
//    {14, {13, 15}},
//    {15, {14, 16, 26}},
//    {16, {15, 17}},
//    {17, {16, 18}},
//    {18, {17, 19}},
//    {19, {18, 20}},
//    {20, {19, 25}},
//    {21, {22, 28}},
//    {22, {21, 23}},
//    {23, {22, 24}},
//    {24, {23, 25}},
//    {25, {20, 24}},
//    {26, {15, 27}},
//    {27, {26, 28}},
//    {28, {21, 27, 29}},
//    {29, {28, 30}},
//    {30, {29}},
//    {31, {8, 32}},
//    {32, {10, 31}}
//};
//
//void ofApp::InitializeFirstGraph()
//{
//    for (const auto& province : provinceCoords) {
//        int id = province.first;
//        float x = province.second.first;
//        float y = province.second.second;
//        nodes[id] = new Node(id, x, y);
//    }
//
//    for (const auto& adjacency : adjacencyList) {
//        int from = adjacency.first;
//        for (int to : adjacency.second) {
//            nodes[from]->addNeighbor(nodes[to], 1.0f);
//        }
//    }
//}
//
//void ofApp::InitializeSecondGraph()
//{
//    int numNodes = 1000;
//    float edgeProbability = 0.01;
//    for (int i = 0; i < numNodes; i++) {
//        float x = ofRandom(0, ofGetWidth());
//        float y = ofRandom(0, ofGetHeight());
//        nodes[i] = new Node(i, x, y);
//    }
//    std::default_random_engine generator;
//    std::uniform_real_distribution<float> distribution(0.0, 1.0);
//    for (int i = 0; i < numNodes; i++) {
//        for (int j = 0; j < numNodes; j++) {
//            if (i != j && distribution(generator) < edgeProbability) {
//                float weight = ofRandom(1.0f, 10.0f);
//                nodes[i]->addNeighbor(nodes[j], weight);
//            }
//        }
//    }
//}
//
//void ofApp::dijkstra() {
//    auto startTime = std::chrono::high_resolution_clock::now();
//
//    std::priority_queue<Node*, std::vector<Node*>, std::function<bool(Node*, Node*)>> pq(
//        [](Node* left, Node* right) {
//            return left->g > right->g;
//        }
//    );
//
//    start->g = 0;
//    pq.push(start);
//
//    while (!pq.empty()) {
//        Node* current = pq.top();
//        pq.pop();
//
//        if (current == end) {
//            break;
//        }
//
//        for (auto& neighborPair : current->neighbors) {
//            Node* neighbor = neighborPair.first;
//            float weight = neighborPair.second;
//
//            float tentative_g = current->g + weight;
//            if (tentative_g < neighbor->g) {
//                neighbor->g = tentative_g;
//                neighbor->previous = current;
//                pq.push(neighbor);
//            }
//        }
//    }
//
//    auto endTime = std::chrono::high_resolution_clock::now();
//    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
//    dijkstraTime = duration.count();
//
//    Node* current = end;
//    path.clear();
//    while (current != nullptr) {
//        path.push_back(current);
//        current = current->previous;
//    }
//    std::reverse(path.begin(), path.end());
//}