/*
 * ofxTangibleToggle.cpp
 */

#include "ofxTangibleToggle.h"

ofxTangibleToggle::ofxTangibleToggle(){
	color.set(255,255,0);
	bActive = bTmpSwitch = false;
	bClickable = true;
	bChanged = false;
}

void ofxTangibleToggle::setup(float _x,float _y, float _w, float _h){
	ofxTangibleCore::setup(_x,_y,_w,_h);
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

void ofxTangibleToggle::setClickable(bool clickable){
	bClickable = clickable;
}

void ofxTangibleToggle::draw(){
	ofPushStyle();
	ofPushMatrix();

	bool bDrawActive = bActive;
	if(bTmpSwitch){
		bDrawActive = !bDrawActive;
	}

	if(bDrawActive){
		ofFill();
	}else{
		ofNoFill();
	}

	ofSetColor(color);
	if (drawType == TANGIBLE_DRAW_AS_RECT) {
		ofTranslate(width/2.f,height/2.f);
		ofTranslate(x,y);
		ofRotate(innerRotate);
		ofSetRectMode(OF_RECTMODE_CENTER);
		ofRect(0, 0, width, height);
	} else if (drawType == TANGIBLE_DRAW_AS_CENTER_RECT) {
		ofTranslate(x,y);
		ofRotate(innerRotate);
		ofSetRectMode(OF_RECTMODE_CENTER);
		ofRect(0, 0, width, height);
	} else {
		ofCircle(x, y, width / 2, width / 2);
	}

	ofPopMatrix();
	ofPopStyle();
}

void ofxTangibleToggle::mousePressed(ofMouseEventArgs &e) {
	if (!bClickable || !isOver(e.x, e.y))
		return;

	bPressed = true;
	bTmpSwitch = true;
}

void ofxTangibleToggle::mouseReleased(ofMouseEventArgs &e) {
	bTmpSwitch = false;
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
	if (!bClickable || bPressed)
			return;

	float touchX = e.x;
	float touchY = e.y;

	if(bScaleTouchEvent){
		touchX *= ofGetWidth();
		touchY *= ofGetHeight();
	}

	if (isOver(touchX, touchY)){
		bTmpSwitch = true;

		touchId = e.id;
		bPressed = true;
	}
}


void ofxTangibleToggle::touchUp(ofTouchEventArgs &e) {
	if (!bClickable || !bPressed)
		return;

	float touchX = e.x;
	float touchY = e.y;

	if(bScaleTouchEvent){
		touchX *= ofGetWidth();
		touchY *= ofGetHeight();
	}

	if(touchId != e.id)
		return;

	bTmpSwitch = false;
	bPressed = false;

	if (isOver(touchX,touchY)){
		setActive(!bActive);
		bChanged = true;
	}
}
