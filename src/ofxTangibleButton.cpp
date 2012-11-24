#include "ofxTangibleButton.h"


void ofxTangibleButton::mousePressed(ofMouseEventArgs &e) {
	if (!bClickable || !isOver(e.x, e.y))
		return;

	if(bPressed == false){
		setActive(true);
		bChanged = true;
	}

	bPressed = true;
}

void ofxTangibleButton::mouseReleased(ofMouseEventArgs &e) {
	if (!bClickable || !bPressed)
		return;

	setActive(false);
	bPressed = false;
}

void ofxTangibleButton::touchDown(ofTouchEventArgs &e) {
	float touchX = e.x;
	float touchY = e.y;

	if(bScaleTouchEvent){
		touchX *= ofGetWidth();
		touchY *= ofGetHeight();
	}

	if (!bClickable || !isOver(touchX, touchY) || bPressed)
		return;

	touchId = e.id;
	setActive(true);
	bChanged = true;

	bPressed = true;
}


void ofxTangibleButton::touchUp(ofTouchEventArgs &e) {
	float touchX = e.x;
	float touchY = e.y;

	if(bScaleTouchEvent){
		touchX *= ofGetWidth();
		touchY *= ofGetHeight();
	}

	if (!bClickable || !bPressed)
		return;

	if(touchId != e.id)
		return;

	setActive(false);
	bChanged = true;
	bPressed = false;
}
