#pragma once
#include "ofMain.h"
#include "Boid.h"

class ofApp : public ofBaseApp {
public:
    ofVec2f target;
    vector<Boid*> flock;
    int followBoidsNum;

    void setup();
    void InitializeFollowBoids();
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
    void InitializeLeaderBoid();
};
