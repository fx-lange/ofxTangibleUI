/*
 * ofxListener.cpp
 */

#include "ofxListener.h"


void ofxListener::moveBy(float dx,float dy){
	x += dx;
	y += dy;

	//TODO can result in infinite loops
	moveListener(dx,dy);
}

void ofxListener::moveListener(float dx, float dy) {
	std::list<ofxListener*>::iterator it = listeners.begin();
	for(;it != listeners.end();++it){
		ofxListener * listener = *it;
		listener->moveBy(dx,dy);
	}
}



