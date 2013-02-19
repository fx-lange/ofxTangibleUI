/*
 * ofxTangibleToggle.cpp
 */

#include "ofxTangibleToggle.h"

ofxTangibleToggle::ofxTangibleToggle(){
	color.set(255,255,0);
	bActive = bDrawAsPressed = false;
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

void ofxTangibleToggle::setActive(bool active, bool silent){
	if(bActive != active){
		bActive = active;
		if(!silent)
			ofNotifyEvent(hasChangedEvent,bActive,this);
	}
}

void ofxTangibleToggle::activateByEvent(bool & active){
	setActive(active==true);
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

bool ofxTangibleToggle::isClickable(){
	return bClickable;
}

void ofxTangibleToggle::drawInner(){

	bool bDrawActive = bActive;
	if(bDrawAsPressed){
		bDrawActive = !bDrawActive;
	}

	if(bDrawActive){
		ofFill();
	}else{
		ofNoFill();
	}

	ofSetColor(color);
	ofxTangibleCore::drawInner();
}

void ofxTangibleToggle::mousePressed(ofMouseEventArgs &e) {
	if (!bClickable || !isOver(e.x, e.y))
		return;

	bPressed = true;
	bDrawAsPressed = true;
}

void ofxTangibleToggle::mouseReleased(ofMouseEventArgs &e) {
	bDrawAsPressed = false;
	if (!bClickable || !bPressed || !isOver(e.x, e.y))
		return;

	setActive(!bActive); //onRelease
	bChanged = true;
	bPressed = false;
}

void ofxTangibleToggle::mouseMoved(ofMouseEventArgs &e){
	//TODO hover effets
}

void ofxTangibleToggle::touchDown(ofTouchEventArgs &e) {
	if (!bClickable || bPressedByTouch)
			return;

	float touchX = e.x;
	float touchY = e.y;

	if(bScaleTouchEvent){
		touchX *= ofGetWidth();
		touchY *= ofGetHeight();
	}

	if (isOver(touchX, touchY)){
		bDrawAsPressed = true;

		touchId = e.id;
		bPressedByTouch = true;
	}
}


void ofxTangibleToggle::touchUp(ofTouchEventArgs &e) {
	if (!bClickable || !bPressedByTouch)
		return;

	float touchX = e.x;
	float touchY = e.y;

	if(bScaleTouchEvent){ //for example tuio coordinates are between 0 and 1
		touchX *= ofGetWidth();
		touchY *= ofGetHeight();
	}

	if(touchId != e.id)
		return;

	bDrawAsPressed = false;
	bPressedByTouch = false;

	if (isOver(touchX,touchY)){
		setActive(!bActive); //onRelease
		bChanged = true;
	}
}
