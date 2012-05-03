/*
 * ofxTangibleCore.cpp
 */

#include "ofxTangibleCore.h"

ofxTangibleCore::~ofxTangibleCore() {
	unregisterMouse();
}

bool ofxTangibleCore::isOver(float px, float py) {
	if( px > x && py > y && px < x + width && py < y + height){
		return true;
	}else{
		return false;
	}
}

void ofxTangibleCore::registerMouse() {
	if(isMouseRegistered)
		return;
	ofAddListener(ofEvents.mousePressed, this, &ofxTangibleCore::mousePressed);
	ofAddListener(ofEvents.mouseDragged, this, &ofxTangibleCore::mouseDragged);
	ofAddListener(ofEvents.mouseReleased, this, &ofxTangibleCore::mouseReleased);
	isMouseRegistered = true;
}

void ofxTangibleCore::unregisterMouse(){
	if(!isMouseRegistered)
		return;
	ofRemoveListener(ofEvents.mousePressed, this, &ofxTangibleCore::mousePressed);
	ofRemoveListener(ofEvents.mouseDragged, this, &ofxTangibleCore::mouseDragged);
	ofRemoveListener(ofEvents.mouseReleased, this, &ofxTangibleCore::mouseReleased);
	isMouseRegistered = false;
}

