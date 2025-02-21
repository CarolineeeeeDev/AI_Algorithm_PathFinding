#include "ofApp.h"

void ofApp::setup() {
    followBoidsNum = 30;
    InitializeLeaderBoid();
    InitializeFollowBoids();
    target = ofVec2f(ofGetWidth() / 2, ofGetHeight() / 2);
}

void ofApp::InitializeFollowBoids()
{
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_real_distribution<float> angleDist(0, TWO_PI);
    std::uniform_real_distribution<float> speedDist(0.5, 1.5);
    std::uniform_real_distribution<float> posDistX(0, ofGetWidth());
    std::uniform_real_distribution<float> posDistY(0, ofGetHeight());

    for (int i = 0; i < followBoidsNum; ++i)
    {
        Boid* followBoid = new Boid();
        followBoid->colorR = 0;
        followBoid->colorG = 0;
        followBoid->colorB = 0;
        followBoid->rb.position = ofVec2f(posDistX(generator), posDistY(generator));
        followBoid->actualPosition = followBoid->rb.position;
        followBoid->rb.maxForce = 0.2;
        followBoid->rb.maxSpeed = 4;
        followBoid->weight = 1.0f;
        float angle = angleDist(generator);
        ofVec2f direction = ofVec2f(cos(angle), sin(angle));
        float speed = speedDist(generator);
        followBoid->rb.velocity = direction * speed;
        flock.push_back(followBoid);
    }
}



void ofApp::InitializeLeaderBoid()
{
    Boid* leadBoid = new Boid();
    leadBoid->rb.position = ofVec2f(ofGetWidth() / 2, ofGetHeight() / 2);
    leadBoid->actualPosition = leadBoid->rb.position;
    leadBoid->rb.maxForce = 0.2;
    leadBoid->rb.maxSpeed = 3.5;
    // set leader boid color to RED
    leadBoid->colorR = 255;
    leadBoid->colorG = 0;
    leadBoid->colorB = 0;
    leadBoid->weight = followBoidsNum;
    flock.push_back(leadBoid);
}

void ofApp::update() {

}

void ofApp::draw() {
    ofBackground(255);
    flock[0]->wander();
    for (int i = 1; i< followBoidsNum+1; ++i)
    {
        flock[i]->flock(flock);
    }
    for (auto boid : flock)
    {
        boid->update();
        boid->show();
        boid->edges();
    }
    
}

void ofApp::mousePressed(int x, int y, int button) {
    target.set(x, y);
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
