/*
 * ofxTangibleToggle.cpp
 */

#include "ofxTangibleToggle.h"

void ofxTangibleToggle::setup(float _x,float _y, float _w, float _h){
	ofxTangibleCore::setup(_x,_y,_w,_w);
	color.set(255,255,0);
	bActive = bPressed = false;
	registerMouse();
	bClickable = true;
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
	ofRect(x,y,width,height);

	ofPopStyle();
}

void ofxTangibleToggle::mousePressed(ofMouseEventArgs &e) {
	if (!bClickable || !isOver(e.x, e.y))
		return;

	bPressed = true;
}

void ofxTangibleToggle::mouseDragged(ofMouseEventArgs &e) {
}

void ofxTangibleToggle::mouseReleased(ofMouseEventArgs &e) {
	if (!bClickable || !bPressed || !isOver(e.x, e.y))
		return;

	bActive = !bActive;
	bChanged = true;
	bPressed = false;
}
