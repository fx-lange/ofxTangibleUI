/*
 * ofxListener.cpp
 */

#include "ofxListener.h"

ofxListener::~ofxListener(){
	//keeping pointer up to date
	//
	//	little overhead but this way the listening concept is null-pointer safe
	list<ofxListener*>::iterator it = listensTo.begin();
	for(;it!=listensTo.end();++it){
		ofxListener * transmitter = *it;
		transmitter->removeListener(this);
	}
	listeners.clear();
	listensTo.clear();
}

ofxListener::ofxListener(const ofxListener& other){
	listeners = other.listeners;
	//keeping pointer up to date
	//	 new listener should listen to the same transmitters
	//	 this way ofxListener and extensions can be stored in std::containern
	list<ofxListener*> transmitters = other.listensTo;
	list<ofxListener*>::iterator it = transmitters.begin();
	for(;it!=transmitters.end();++it){
		ofxListener * transmitter = *it;
		transmitter->addListener(this);
	}
}

void ofxListener::removeListener(ofxListener * listener){
	list<ofxListener*>::iterator it = listeners.begin();
	for(;it!=listeners.end();++it){
		if(*it == listener){
			listeners.erase(it);
			break;
		}
	}
}

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



