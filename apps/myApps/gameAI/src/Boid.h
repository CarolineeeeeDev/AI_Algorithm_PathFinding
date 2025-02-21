#pragma once
#include "ofMain.h"
#include "Rigidbody.h"
//#include "PerlinNoise/PerlinNoise.h"

class Boid {

public:
    Boid();
    vector<ofVec2f> currentPath;
    vector<vector<ofVec2f>> paths;
    bool hitEdge;
    Rigidbody rb;
    float weight;
    float wanderTheta;
    int colorR;
    int colorG;
    int colorB;
    ofVec2f actualPosition;
    //float xoff;
    //PerlinNoise perlin;
    float alignMagnitude;
    float cohesionMagnitude;
    float separationMagnitude;
    void update();
    void show();
    void edges();
    ofVec2f seek(ofVec2f target);
    ofVec2f arrive(ofVec2f target);
    ofVec2f flee(ofVec2f target);
    ofVec2f pursue(Boid* boid);
    ofVec2f evade(Boid* boid);
    void wander();
    ofVec2f align(vector<Boid*> boids);
    ofVec2f cohesion(vector<Boid*> boids);
    ofVec2f separation(vector<Boid*> boids);
    void flock(vector<Boid*> boids);
};
