/*
 * ofxTangibleToggle.cpp
 */

#include "ofxTangibleToggle.h"

ofxTangibleToggle::ofxTangibleToggle(){
	color.set(255,255,0);
	bActive = bPressed = false;
	bClickable = true;
	bChanged = false;
}

void ofxTangibleToggle::setup(float _x,float _y, float _w, float _h){
	ofxTangibleCore::setup(_x,_y,_w,_w);
	registerMouse();
	registerTouch();
}

bool ofxTangibleToggle::isActive(){
	return bActive;
}

void ofxTangibleToggle::setActive(bool active){
	if(bActive != active){
		bActive = active;
		ofNotifyEvent(hasChangedEvent,bActive,this);
	}
}

bool ofxTangibleToggle::hasChanged(){
	return bChanged;
}

void ofxTangibleToggle::resetChanged(){
	bChanged = false;
}

void ofxTangibleToggle::draw(){
	ofPushStyle();

	if(bActive){
		ofFill();
	}else{
		ofNoFill();
	}

	ofSetColor(color);
	if(drawType == TANGIBLE_DRAW_AS_RECT){
		ofRect(x,y,width,height);
	}else{
		ofCircle(x+width/2,y+width/2,width,width);
	}

	ofPopStyle();
}

void ofxTangibleToggle::mousePressed(ofMouseEventArgs &e) {
	if (!bClickable || !isOver(e.x, e.y))
		return;

	bPressed = true;
}

void ofxTangibleToggle::mouseReleased(ofMouseEventArgs &e) {
	if (!bClickable || !bPressed || !isOver(e.x, e.y))
		return;

	setActive(!bActive);
	bChanged = true;
	bPressed = false;
}

void ofxTangibleToggle::mouseMoved(ofMouseEventArgs &e){
	//TODO hover effets
}

void ofxTangibleToggle::touchDown(ofTouchEventArgs &e) {
	float touchX = e.x;
	float touchY = e.y;

	if(bScaleTouchEvent){
		touchX *= ofGetWidth();
		touchY *= ofGetHeight();
	}

	if (!bClickable || !isOver(touchX, touchY) || bPressed)
		return;

	touchId = e.id;
	bPressed = true;
}


void ofxTangibleToggle::touchUp(ofTouchEventArgs &e) {
	float touchX = e.x;
	float touchY = e.y;

	if(bScaleTouchEvent){
		touchX *= ofGetWidth();
		touchY *= ofGetHeight();
	}

	if (!bClickable || !bPressed || !isOver(touchX,touchY))
		return;

	if(touchId != e.id)
		return;

	setActive(!bActive);
	bChanged = true;
	bPressed = false;
}
