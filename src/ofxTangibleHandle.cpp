/*
 * ofxTangibleHandle.cpp
 */

/*TODO
 * hover?!
 * */

#include "ofxTangibleHandle.h"

void ofxTangibleHandle::setup(float _x,float _y, float _w, float _h){
	ofxTangibleCore::setup(_x,_y,_w,_h);
	color.set(255,0,0);
	fillMe = false;
	bPressed =	false;
	registerMouse();
	enableGrabbing();
}

void ofxTangibleHandle::draw(){
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

void ofxTangibleHandle::mousePressed(ofMouseEventArgs &e) {
	if (!bGrabbingEnabled || !isOver(e.x, e.y))
		return;

	bPressed = true;

	pX = e.x;
	pY = e.y;
}

void ofxTangibleHandle::mouseDragged(ofMouseEventArgs &e) {
	if (!bGrabbingEnabled || !bPressed)
		return;

	float dx = e.x - pX;
	float dy = e.y - pY;

	moveBy(dx,dy);

	pX = e.x;
	pY = e.y;
}

void ofxTangibleHandle::mouseMoved(ofMouseEventArgs &e){
	//override for hover effects
}

void ofxTangibleHandle::mouseReleased(ofMouseEventArgs &e) {
	if (!bGrabbingEnabled || !bPressed)
		return;

	bPressed = false;
}

