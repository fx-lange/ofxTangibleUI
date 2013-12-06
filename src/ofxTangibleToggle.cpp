/*
 * ofxTangibleToggle.cpp
 */

#include "ofxTangibleToggle.h"

ofxTangibleToggle::ofxTangibleToggle(){
	color.set(255,255,0,215);
	hoverColor.set(255,255,0,255);
	bActive = false;
	bClickable = true;
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

void ofxTangibleToggle::setClickable(bool clickable){
	bClickable = clickable;
	bPressed = bPressedByTouch = false;
}

bool ofxTangibleToggle::isClickable(){
	return bClickable;
}

void ofxTangibleToggle::drawInner(){
	//REVISIT could be encapsulated by using sth. like preDraw() or styleBeforeDraw()

	//toggle only changes state on mouseRelease() / touchUp()
	// => temporary visual state needed if pressed
	bool bDrawAsActive = isActive();
	if(isPressed()){
		bDrawAsActive = !bDrawAsActive;
	}

	if(bDrawAsActive){
		ofFill();
	}else{
		ofNoFill();
	}

	if(bHovered){
		ofSetColor(hoverColor);
	}else{
		ofSetColor(color);
	}
	ofxTangibleCore::drawInner();
}

void ofxTangibleToggle::mousePressed(ofMouseEventArgs &e) {
	if (!bClickable || !isOver(e.x, e.y))
		return;

	setPressed(true);
}

void ofxTangibleToggle::mouseReleased(ofMouseEventArgs &e) {
	if (!bClickable || !bPressed || !isOver(e.x, e.y))
		return;

	setPressed(false);
	setActive(!bActive); //onRelease
}

void ofxTangibleToggle::mouseMoved(ofMouseEventArgs &e){
	if(!bClickable)
		return;

	if(isOver(e.x, e.y)){
		bHovered = true;
	}else{
		bHovered = false;
	}
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
		touchId = e.id;

		touchPressure = e.pressure;

		setPressedByTouch(true);
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

	setPressedByTouch(false);

	if (isOver(touchX,touchY)){
		setActive(!bActive); //onRelease
	}
}
