#include "ofxRotaryKnob.h"

ofxRotaryKnob::ofxRotaryKnob()
	:ofxTangibleHandle(){
	drawType = TANGIBLE_DRAW_AS_CIRCLE;
}

void ofxRotaryKnob::mousePressed(ofMouseEventArgs &e) {
	if (!bGrabbingEnabled || !isOver(e.x, e.y))
		return;

	bPressed = true;

	angleToTouchCenter = ofRadToDeg(atan2(e.x - getRotateCenter().x,e.y - getRotateCenter().y));
}

void ofxRotaryKnob::mouseDragged(ofMouseEventArgs &e) {
	if (!bGrabbingEnabled || !bPressed)
		return;

	float newAngle = ofRadToDeg(atan2(e.x - getRotateCenter().x,e.y - getRotateCenter().y));
	rotateInner(angleToTouchCenter - newAngle);
	angleToTouchCenter = newAngle;
}

void ofxRotaryKnob::mouseReleased(ofMouseEventArgs &e) {
	if (!bPressed)
		return;
	bPressed = false;
}

void ofxRotaryKnob::touchDown(ofTouchEventArgs &e) {
	if(!bGrabbingEnabled || bPressedByTouch)
		return;

	float touchX = e.x;
	float touchY = e.y;

	if(bScaleTouchEvent){
		touchX *= ofGetWidth();
		touchY *= ofGetHeight();
	}

	if (!isOver(touchX, touchY))
		return;

	touchs.push_back(e);
	touchs.back().x = touchX;
	touchs.back().y = touchY;

	angleToTouchCenter = ofRadToDeg(atan2(touchX - getRotateCenter().x,touchY - getRotateCenter().y));
	bPressedByTouch = true;
}

void ofxRotaryKnob::touchMoved(ofTouchEventArgs &e) {
	if (!bGrabbingEnabled || !bPressedByTouch)
		return;

	float touchX = e.x;
	float touchY = e.y;

	if(bScaleTouchEvent){
		touchX *= ofGetWidth();
		touchY *= ofGetHeight();
	}

	touchCursor & te = touchs[0];
	if(e.id == te.id){
		float newAngle = ofRadToDeg(atan2(touchX - getRotateCenter().x,touchY - getRotateCenter().y));
		rotateInner(angleToTouchCenter - newAngle);
		angleToTouchCenter = newAngle;
	}
}

void ofxRotaryKnob::touchUp(ofTouchEventArgs &e) {
	if (!bGrabbingEnabled || !bPressedByTouch)
		return;

	touchCursor & te = touchs[0];
	if(e.id == te.id){
		touchs.clear();
		bPressedByTouch = false;
	}
}

void ofxRotaryKnob::drawInner(){
	ofPushStyle();
	ofxTangibleHandle::drawInner();
	ofSetColor(color);
	ofFill();
	ofCircle( 0, - height * 0.3, 5);
	ofPopStyle();
}

