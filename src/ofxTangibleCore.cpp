/*
 * ofxTangibleCore.cpp
 */

#include "ofxTangibleCore.h"

ofxTangibleCore::~ofxTangibleCore() {
	unregisterMouse();
}

ofxTangibleCore::ofxTangibleCore(const ofxTangibleCore& other){
	setup(other.x,other.y,other.width,other.height);
	listeners = other.listeners;
	if(other.bMouseRegistered){
		registerMouse();
	}
	bMouseRegistered = other.bMouseRegistered;
}

void ofxTangibleCore::setup(float _x,float _y, float _w, float _h){
	x = _x;
	y = _y;
	width = _w;
	height = _h;
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
	ofAddListener(ofEvents.mousePressed, this, &ofxTangibleCore::mousePressed);
	ofAddListener(ofEvents.mouseDragged, this, &ofxTangibleCore::mouseDragged);
	ofAddListener(ofEvents.mouseReleased, this, &ofxTangibleCore::mouseReleased);
	bMouseRegistered = true;
}

void ofxTangibleCore::unregisterMouse(){
	if(!bMouseRegistered)
		return;
	ofRemoveListener(ofEvents.mousePressed, this, &ofxTangibleCore::mousePressed);
	ofRemoveListener(ofEvents.mouseDragged, this, &ofxTangibleCore::mouseDragged);
	ofRemoveListener(ofEvents.mouseReleased, this, &ofxTangibleCore::mouseReleased);
	bMouseRegistered = false;
}

