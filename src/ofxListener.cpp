/*
 * ofxListener.cpp
 */

#include "ofxListener.h"

ofxListener::~ofxListener(){
	//keeping pointer up to date
	//
	//	little overhead but this way the listening concept is null-pointer safe
	list<ofxListener*>::iterator it = rotateListensTo.begin();
	for(;it!=rotateListensTo.end();++it){
		ofxListener * transmitter = *it;
		transmitter->removeRotateListener(this);
	}
	rotatelisteners.clear();
	rotateListensTo.clear();

	ofRemoveListener(ofxTangibleMoveEvent::events, this, &ofxListener::moveEvent); //TODO nur vor dem Programm!
}

ofxListener::ofxListener(const ofxListener& other){
	bLocked = other.bLocked;
	rotateCenter = other.rotateCenter;
	moveListenersSpeed = other.moveListenersSpeed;
	base = other.base;
	zeroBaseCheck = other.zeroBaseCheck;
	oldAngle = other.oldAngle;
	//keeping pointer up to date
	//	 new listener should listen to the same transmitters
	//	 this way ofxListener and extensions can be stored in std::containern
	list<ofxListener*> transmitters_ = other.rotateListensTo;
	list<ofxListener*>::iterator it = transmitters_.begin();
	it = transmitters_.begin();
	for(;it!=transmitters_.end();++it){
		ofxListener * transmitter = *it;
		transmitter->addRotateListener(this);
	}

	transmitters = other.transmitters;
}

void ofxListener::removeRotateListener(ofxListener * listener){
	list<ofxListener*>::iterator it = rotatelisteners.begin();
	for(;it!=rotatelisteners.end();++it){
		if(*it == listener){
			rotatelisteners.erase(it);
			break;
		}
	}
}

void ofxListener::moveEvent(ofxTangibleMoveEvent & e){
	bool bListenToTransmitter = false;
	for(list<int>::iterator it = transmitters.begin();it != transmitters.end();++it){
		if(e.id == *it){
			bListenToTransmitter = true;
			break;
		}
	}
	if(bListenToTransmitter){
		moveBy(e.dx,e.dy);
	}
}

void ofxListener::moveBy(float dx,float dy){
	if(bLocked)
		return;
	bLocked = true;

	x += dx;
	y += dy;

	moveListeners(dx * moveListenersSpeed.x,dy * moveListenersSpeed.y);

	float newAngle = (*this - rotateCenter).angle(base);
	if((*this - rotateCenter).angle(zeroBaseCheck) > 90.f){
		newAngle *= -1.f;
	}
	float angleDiff = newAngle - oldAngle;
	oldAngle = newAngle;

	rotateListeners(angleDiff);

	bLocked = false;
}

void ofxListener::rotateBy(float angle){
	if(bLocked)
		return;
	bLocked = true;

	ofVec3f vec = *this-rotateCenter;
	vec.rotate(0,0,angle);
	vec = rotateCenter + vec;
	x = vec.x;
	y = vec.y;

	rotateListeners(angle);

	updateOldAngle();

	bLocked = false;
}

void ofxListener::rotateListeners(float angle) {
	std::list<ofxListener*>::iterator it = rotatelisteners.begin();
	for(;it != rotatelisteners.end();++it){
		ofxListener * listener = *it;
		listener->rotateBy(angle);
	}
}



