#pragma once
#include "ofMain.h"
#include "Boid.h"
#include "Spot.h"


class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void gotMessage(ofMessage msg);
    void dragEvent(ofDragInfo dragInfo);

private:
    static const int cols = 50;
    static const int rows = 50;
    static const int cellSize = 15;

    std::vector<std::vector<Spot>> grid;
    std::vector<Spot*> openSet, closedSet, path;
    Spot* start;
    Spot* end;

    void astar();
    float heuristic(Spot* a, Spot* b);
};
