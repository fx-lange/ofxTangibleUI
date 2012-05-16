/*
 * ofxTangibleCore.cpp
 */

#include "ofxTangibleCore.h"

ofxTangibleCore::~ofxTangibleCore() {
	unregisterMouse();
	unregisterTouch();
}

ofxTangibleCore::ofxTangibleCore(const ofxTangibleCore& other)
	:ofxListener(other){
	setup(other.x,other.y,other.width,other.height);

	if(other.bMouseRegistered){
		registerMouse();
	}
	bMouseRegistered = other.bMouseRegistered;

	if(other.bTouchRegistered){
		registerTouch();
	}
	bTouchRegistered = other.bTouchRegistered;
}

void ofxTangibleCore::setup(float _x,float _y, float _w, float _h){
	x = _x;
	y = _y;
	width = _w;
	height = _h;
	touchId = -1;
}

bool ofxTangibleCore::isOver(float px, float py) {
	if( px >= x && py >= y && px <= x + width && py <= y + height){
		return true;
	}else{
		return false;
	}
}

void ofxTangibleCore::registerMouse() {
	if(bMouseRegistered)
		return;
	ofRegisterMouseEvents(this);
	bMouseRegistered = true;
}

void ofxTangibleCore::unregisterMouse(){
	if(!bMouseRegistered)
		return;
	ofUnregisterMouseEvents(this);
	bMouseRegistered = false;
}

void ofxTangibleCore::registerTouch() {
	if(bTouchRegistered)
		return;
	ofRegisterTouchEvents(this);
	bTouchRegistered = true;
}

void ofxTangibleCore::unregisterTouch(){
	if(!bTouchRegistered)
		return;
	ofUnregisterTouchEvents(this);
	bTouchRegistered = false;
}

