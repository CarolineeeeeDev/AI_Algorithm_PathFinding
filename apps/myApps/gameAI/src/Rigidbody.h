#pragma once
#include "ofMain.h"

class Rigidbody {
public:
    ofVec2f position;
    ofVec2f velocity;
    ofVec2f acceleration;
    float rotation;
    float orientation;
    float maxSpeed;
    float maxForce;
    float r;

    Rigidbody();
    Rigidbody(ofVec2f pos);
    void update();
    void applyForce(ofVec2f force);
    void setOrientation(float angle);
};
