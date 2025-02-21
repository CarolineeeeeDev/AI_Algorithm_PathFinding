#include "Target.h"

Target::Target(float x, float y)
{
	rb.velocity = ofVec2f(ofRandom(-1, 1), ofRandom(-1, 1));
	rb.velocity *= 5;
}

void Target::show()
{
	ofSetColor(255, 0, 0);
	ofPushMatrix();
	ofTranslate(rb.position);
	ofDrawCircle(rb.position.x, rb.position.y, rb.r * 2);
	ofPopMatrix();
}
