#pragma once
#include "ofMain.h"
#include "Boid.h"
#include "Graph.h"
#include "Map.h"


class ofApp : public ofBaseApp {
public:
    void setup();
    void InitializeBoid();
    void update();
    void draw();
    void aStar();
    float heuristic(Node* a, Node* b);

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

    void InitializeMap();
    //void InitializeFirstGraph();
    //void InitializeSecondGraph();
    //void dijkstra();

private:
    Map* map;
    Boid* boid;
    std::unordered_map<int, Node*> nodes;
    Node* start;
    Node* end;
    //Graph graph;
    //long long dijkstraTime;
    //long long aStarTime;
    std::vector<Node*> path;
    std::vector<Node*> aStarPath;
};
