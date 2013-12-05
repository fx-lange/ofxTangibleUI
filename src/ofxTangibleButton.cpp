#include "ofxTangibleButton.h"


void ofxTangibleButton::mousePressed(ofMouseEventArgs &e) {
	if (!bClickable || !isOver(e.x, e.y))
		return;

	setPressed(true);
}

void ofxTangibleButton::mouseReleased(ofMouseEventArgs &e) {
	if (!bClickable || !bPressed)
		return;

	setPressed(false);

	if(isOver(e.x,e.y)){
		setActive(true);
		bActive = false; //TODO irritating
	}

}

void ofxTangibleButton::touchDown(ofTouchEventArgs &e) {
	float touchX = e.x;
	float touchY = e.y;

	if(bScaleTouchEvent){
		touchX *= ofGetWidth();
		touchY *= ofGetHeight();
	}

	if (!bClickable || !isOver(touchX, touchY) || bPressedByTouch)
		return;

	touchId = e.id;

	setPressedByTouch(true);
}


void ofxTangibleButton::touchUp(ofTouchEventArgs &e) {
	float touchX = e.x;
	float touchY = e.y;

	if(bScaleTouchEvent){
		touchX *= ofGetWidth();
		touchY *= ofGetHeight();
	}

	if(!bPressedByTouch)
		return;

	if(touchId != e.id)
		return;

	setPressedByTouch(false);

	if(isOver(touchX,touchY)){
		setActive(true);
		bActive = false; //TODO kind of irritating
	}
}
