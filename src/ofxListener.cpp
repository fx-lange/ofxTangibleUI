/*
 * ofxListener.cpp
 */

#include "ofxListener.h"


void ofxListener::moveBy(float dx,float dy){
	if(bLocked)
		return;
	bLocked = true;

	x += dx;
	y += dy;

	moveListener(dx,dy);

	bLocked = false;
}

void ofxListener::moveListener(float dx, float dy) {
	std::list<ofxListener*>::iterator it = listeners.begin();
	for(;it != listeners.end();++it){
		ofxListener * listener = *it;
		listener->moveBy(dx,dy);
	}
}



