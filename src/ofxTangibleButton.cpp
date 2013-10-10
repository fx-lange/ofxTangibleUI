#include "ofxTangibleButton.h"


void ofxTangibleButton::mousePressed(ofMouseEventArgs &e) {
	if (!bClickable || !isOver(e.x, e.y))
		return;

	bDrawAsPressed = true;
	bPressed = true;
}

void ofxTangibleButton::mouseReleased(ofMouseEventArgs &e) {
	if (!bClickable || !bPressed)
		return;

	bPressed = false;
	bDrawAsPressed = false;

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

	bDrawAsPressed = true;
	bPressedByTouch = true;
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

	if(isOver(touchX,touchY)){
		setActive(true);
		bActive = false; //TODO kind of irritating
	}

	bDrawAsPressed = false;
	bPressedByTouch = false;
}
