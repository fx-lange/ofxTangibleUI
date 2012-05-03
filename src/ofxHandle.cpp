/*
 * ofxHandle.cpp
 */

/*TODO
 * hover?!
 * */

#include "ofxHandle.h"

void ofxHandle::setup(float _x,float _y, float _w, float _h){
	x = _x;
	y = _y;
	width = _w;
	height = _h;
	color.set(255,0,0);
	fillMe = false;
	bPressed =	false;
	registerMouse();
	enableGrabbing();
}

void ofxHandle::draw(){
	ofPushStyle();

	if(fillMe){
		ofFill();
	}else{
		ofNoFill();
	}
	ofSetColor(color);
	ofRect(x,y,width,height);

	ofPopStyle();
}

void ofxHandle::mousePressed(ofMouseEventArgs &e) {
	if (!bGrabbingEnabled || !isOver(e.x, e.y))
		return;

	bPressed = true;

	pX = e.x;
	pY = e.y;
}

void ofxHandle::mouseDragged(ofMouseEventArgs &e) {
	if (!bGrabbingEnabled || !bPressed)
		return;

	float dx = e.x - pX;
	float dy = e.y - pY;

	moveBy(dx,dy);

	pX = e.x;
	pY = e.y;
}

void ofxHandle::mouseReleased(ofMouseEventArgs &e) {
	if (!bGrabbingEnabled || !bPressed)
		return;

	bPressed = false;
}

