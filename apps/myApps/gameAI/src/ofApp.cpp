#include "ofApp.h"

void ofApp::setup() {
    ofSetFrameRate(60);
    ofBackground(45, 197, 244);

    grid.resize(cols, std::vector<Spot>(rows, Spot(0, 0)));
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            grid[i][j] = Spot(i, j);
        }
    }

    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            grid[i][j].addNeighbors(grid);
        }
    }

    start = &grid[0][0];
    end = &grid[cols - 1][rows - 1];
    start->wall = false;
    end->wall = false;

    openSet.push_back(start);
}

float ofApp::heuristic(Spot* a, Spot* b) {
    return ofDist(a->i, a->j, b->i, b->j);
}

void ofApp::astar() {
    if (openSet.empty()) return;

    int winner = 0;
    for (int i = 1; i < openSet.size(); i++) {
        if (openSet[i]->f < openSet[winner]->f) {
            winner = i;
        }
    }
    Spot* current = openSet[winner];

    if (current == end) {
        path.clear();
        while (current) {
            path.push_back(current);
            current = current->previous;
        }
        return;
    }

    openSet.erase(openSet.begin() + winner);
    closedSet.push_back(current);

    for (Spot* neighbor : current->neighbors) {
        if (std::find(closedSet.begin(), closedSet.end(), neighbor) != closedSet.end() || neighbor->wall)
            continue;

        float tempG = current->g + heuristic(current, neighbor);
        bool newPath = false;

        if (std::find(openSet.begin(), openSet.end(), neighbor) == openSet.end()) {
            openSet.push_back(neighbor);
            newPath = true;
        }
        else if (tempG < neighbor->g) {
            newPath = true;
        }

        if (newPath) {
            neighbor->g = tempG;
            neighbor->h = heuristic(neighbor, end);
            neighbor->f = neighbor->g + neighbor->h;
            neighbor->previous = current;
        }
    }
}
void ofApp::update() {
    if (!path.size()) {
        astar();
    }
}

void ofApp::draw() {
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            if (grid[i][j].wall) {
                ofSetColor(112, 50, 126);
                ofDrawRectangle(i * cellSize, j * cellSize, cellSize, cellSize);
            }
            else {
                ofSetColor(200);
                ofNoFill();
                ofDrawRectangle(i * cellSize, j * cellSize, cellSize, cellSize);
            }
        }
    }

    ofFill();
    for (Spot* s : closedSet) {
        ofSetColor(236, 1, 90, 100);
        ofDrawRectangle(s->i * cellSize, s->j * cellSize, cellSize, cellSize);
    }

    for (Spot* s : openSet) {
        ofSetColor(240, 99, 164, 100);
        ofDrawRectangle(s->i * cellSize, s->j * cellSize, cellSize, cellSize);
    }

    if (!path.empty()) {
        ofSetColor(252, 238, 33);
        ofSetLineWidth(3);
        ofNoFill();
        ofBeginShape();
        for (Spot* s : path) {
            ofVertex(s->i * cellSize + cellSize / 2, s->j * cellSize + cellSize / 2);
        }
        ofEndShape();
    }
}

void ofApp::mousePressed(int x, int y, int button) {

}

void ofApp::keyPressed(int key) {
}

void ofApp::keyReleased(int key) {
}

void ofApp::mouseMoved(int x, int y) {
}

void ofApp::mouseDragged(int x, int y, int button) {
}

void ofApp::mouseReleased(int x, int y, int button) {
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
