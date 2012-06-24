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
	ofxListener::setup(_x,_y);
	x = _x;
	y = _y;
	width = _w;
	height = _h;
	touchId = -1;
}

bool ofxTangibleCore::isOver(float px, float py) {
	if(drawType == TANGIBLE_DRAW_AS_RECT){
		if( px > x && py > y && px < x + width && py < y + height){
			return true;
		}else{
			return false;
		}
	}else if(drawType == TANGIBLE_DRAW_AS_CENTER_RECT){
		if ( abs(px-x)<width/2 && abs(py-y)<height/2 ){
			return true;
		}else {
			return false;
		}
	}else{
		if( abs(px-x)<width/2 && abs(py-y)<width/2){
			return true;
		}else{
			return false;
		}
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

