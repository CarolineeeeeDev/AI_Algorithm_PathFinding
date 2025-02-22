#include "Rigidbody.h"

Rigidbody::Rigidbody() : position(ofVec2f(0, 0)), velocity(ofVec2f(0, 0)), rotation(0), orientation(0), maxSpeed(8), maxForce(0.4), r(20.0) {}

Rigidbody::Rigidbody(ofVec2f pos) : position(pos), velocity(ofVec2f(0, 0)), rotation(0), orientation(0), maxSpeed(8), maxForce(0.4), r(20.0) {}

void Rigidbody::update() {
    velocity += acceleration;
    velocity.limit(maxSpeed);
    position += velocity;
    acceleration = ofVec2f(0, 0);

    if (velocity.length() > 0) {
        setOrientation(atan2(velocity.y, velocity.x));
    }
}

void Rigidbody::applyForce(ofVec2f force) {
    acceleration += force;
}

void Rigidbody::setOrientation(float angle) {
    orientation = angle;
    rotation = ofRadToDeg(angle);
}