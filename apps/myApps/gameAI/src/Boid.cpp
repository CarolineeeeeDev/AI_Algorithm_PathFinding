#include <random>
#include "Boid.h"

Boid::Boid()
{
    wanderTheta = PI / 2;
    currentPath = {};
    paths = { currentPath };
    alignMagnitude = 0.5;
    cohesionMagnitude = 1.0;
    separationMagnitude = 1.3;

}

void Boid::update() {
    rb.update();
    actualPosition += rb.velocity;
    currentPath.push_back(rb.position);
}

void Boid::show()
{
    float r = rb.r;
    ofSetColor(255,0, 0);
    ofPushMatrix();
    ofTranslate(rb.position);
    ofRotateDeg(rb.rotation);
    ofDrawCircle(0, 0, r-2);
    //ofDrawTriangle(-r / 2, -3 * r / 4, -r / 2, 3 * r / 4, 2*r, 0);
    ofPopMatrix();
    for (const auto& path : paths) {
        ofBeginShape();
        for (const auto& v : path) {
            ofVertex(v.x, v.y);
        }
        ofEndShape();
    }
}

void Boid::edges()
{
    hitEdge = false;
    if (rb.position.x > ofGetWidth() + rb.r)
    {
        rb.position.x = -rb.r;
        hitEdge = true;
    }
    else if (rb.position.x < -rb.r)
    {
        rb.position.x = ofGetWidth() + rb.r;
        hitEdge = true;
    }
    if (rb.position.y > ofGetHeight() + rb.r)
    {
        rb.position.y = -rb.r;
        hitEdge = true;
    }
    else if (rb.position.y < -rb.r)
    {
        rb.position.y = ofGetHeight() + rb.r;
        hitEdge = true;
    }
    if (hitEdge) {
        currentPath = {};
        paths.push_back(currentPath);
    }
}


ofVec2f Boid::seek(ofVec2f target) {
    ofVec2f force = target - rb.position;
    force.normalize();
    force *= rb.maxSpeed;
    force -= rb.velocity;
    force.limit(rb.maxForce);
    rb.applyForce(force);
    return force;
}

ofVec2f Boid::arrive(ofVec2f target)
{
    ofVec2f force = target - rb.position;
    float r = 100;

    float distance = force.length();


    if (distance < r) {
        float m = ofMap(distance, 0, r, 0, rb.maxSpeed);
        force.normalize();
        force *= m;
    }
    else {
        force.normalize();
        force *= rb.maxSpeed;
    }

    force -= rb.velocity;
    force.limit(rb.maxForce);

    return force;
}

// Arrive Method 2
//ofVec2f Boid::seek(ofVec2f target, bool arrival) {
//    ofVec2f force = target - rb.position;
//    float desiredSpeed = rb.maxSpeed;
//
//    if (arrival) {
//        float slowRadius = 50.0f;
//        float distance = force.length();
//        if (distance < slowRadius) {
//            desiredSpeed = ofMap(distance, 0, slowRadius, 0, rb.maxSpeed);
//        }
//    }
//    force.normalize();
//    force *= desiredSpeed;
//    force -= rb.velocity;
//    force.limit(rb.maxForce);
//    return force;
//}
//
//ofVec2f Boid::arrive(ofVec2f target)
//{
//    return seek(target, true);
//}

ofVec2f Boid::flee(ofVec2f target)
{
    return -seek(target);
}

ofVec2f Boid::pursue(Boid* boid)
{
    ofVec2f target = boid->rb.position;
    ofVec2f prediction = boid->rb.velocity;
    prediction *= 10;
    target += prediction;
    ofSetColor(0);
    ofDrawCircle(target.x, target.y, rb.r);
    return seek(target);
}

ofVec2f Boid::evade(Boid* boid)
{
    ofVec2f pursuit = pursue(boid);
    pursuit *= -1;
    return pursuit;
}

void Boid::wander()
{
    ofVec2f wanderPoint = rb.velocity;
    wanderPoint.normalize();
    wanderPoint *= 100;
    wanderPoint += rb.position;

    float wanderRadius = 50;

    float theta = wanderTheta + rb.rotation;

    float x = wanderRadius * cos(theta);
    float y = wanderRadius * sin(theta);
    wanderPoint += ofVec2f(x, y);


    ofVec2f steer = wanderPoint - rb.position;
    steer.normalize();
    steer *= rb.maxForce;
    rb.applyForce(steer);

    float displaceRange = 1.5;
    std::default_random_engine generator(time(0));
    std::uniform_real_distribution<float> distribution(-displaceRange, displaceRange);
    wanderTheta += distribution(generator);
}

//Wander Method 2
//void Boid::wander()
//{
//    float angle = perlin.noise(xoff, 0.0, 0.0) * glm::two_pi<float>() * 2;
//    glm::vec2 steer = glm::vec2(cos(angle), sin(angle)) * rb.maxForce;
//    rb.applyForce(steer);
//    xoff += 0.01f;
//}

ofVec2f Boid::align(vector<Boid*> boids)
{
    int perceptionRadius = 5000;
    ofVec2f steering = ofVec2f(0,0);
    int total = 0;
    for (auto other : boids)
    {
        float d = std::sqrt(std::pow(actualPosition.x - other->actualPosition.x, 2) + std::pow(actualPosition.y - other->actualPosition.y, 2));
        if (other != this && d < perceptionRadius)
        {
            steering+=(other->rb.velocity * other->weight);
            total+= other->weight;
        }
    }
    if (total > 0)
    {
        steering /= total;
        steering.normalize();
        steering *= rb.maxSpeed;
        steering -= rb.velocity;
        steering.limit(rb.maxForce);
    }
    return steering;
}

ofVec2f Boid::cohesion(vector<Boid*> boids)
{
    int perceptionRadius = 5000;
    ofVec2f steering = ofVec2f(0, 0);
    int total = 0;
    for (auto other : boids)
    {
        float d = std::sqrt(std::pow(actualPosition.x - other->actualPosition.x, 2) + std::pow(actualPosition.y - other->actualPosition.y, 2));
        if (other != this && d < perceptionRadius)
        {
            steering += (other->actualPosition * other->weight);
            total+= other->weight;
        }
    }
    if (total > 0)
    {
        steering /= total;
        steering -= actualPosition;
        steering.normalize();
        steering *= rb.maxSpeed;
        steering -= rb.velocity;
        steering.limit(rb.maxForce);
    }
    return steering;
}

ofVec2f Boid::separation(vector<Boid*> boids)
{
    int perceptionRadius = 100;
    ofVec2f steering = ofVec2f(0, 0);
    int total = 0;
    for (auto other : boids)
    {
        float d = std::sqrt(std::pow(actualPosition.x - other->actualPosition.x, 2) + std::pow(actualPosition.y - other->actualPosition.y, 2));

        if (other != this && d < perceptionRadius)
        {
            ofVec2f diff = actualPosition - other->actualPosition;

            diff /= (d * d);

            steering += diff;
            total ++;
        }
    }

    if (total > 0)
    {
        steering /= total;
        steering.normalize();
        steering *= rb.maxSpeed;
        steering -= rb.velocity;
        steering.limit(rb.maxForce);
    }

    return steering;
}


void Boid::flock(vector<Boid*> boids)
{
    ofVec2f alignSteering = align(boids);
    ofVec2f cohesionSteering = cohesion(boids);
    ofVec2f separationSteering = separation(boids);
    rb.acceleration += (alignSteering * alignMagnitude + cohesionSteering * cohesionMagnitude + separationSteering * separationMagnitude);
}