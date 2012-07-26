/*
 * ofxTangibleCore.cpp
 */

#include "ofxTangibleCore.h"

ofxTangibleCore::ofxTangibleCore(){
	bMouseRegistered = false;
	bTouchRegistered = false;
	drawType = TANGIBLE_DRAW_AS_RECT;
	touchId = -1;
}

ofxTangibleCore::~ofxTangibleCore() {
	unregisterMouse();
	unregisterTouch();
}

ofxTangibleCore::ofxTangibleCore(const ofxTangibleCore& other)
	:ofxListener(other){ //REVISIT isn't this default behaviour?

	init(other); //REVISIT call before body?
}

ofxTangibleCore& ofxTangibleCore::operator= (const ofxTangibleCore& other){
	ofxListener::operator=(other);
	init(other);
	return *this;
}

void ofxTangibleCore::init(const ofxTangibleCore& other){
	drawType = other.drawType;
	touchId = other.touchId;
	width = other.width;
	height = other.height;

	pX = other.pX;
	pY = other.pY;

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
	width = _w;
	height = _h;
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

