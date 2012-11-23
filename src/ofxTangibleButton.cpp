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
