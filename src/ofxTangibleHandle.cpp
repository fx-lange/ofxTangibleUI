/*
 * ofxTangibleHandle.cpp
 */

/*TODO
 * hover?!
 * */

#include "ofxTangibleHandle.h"

ofxTangibleHandle::ofxTangibleHandle() :
	bGrabbingEnabled(false), bPressed(false), fillMe(false){
}

void ofxTangibleHandle::setup(float _x, float _y, float _w, float _h) {
	ofxTangibleCore::setup(_x, _y, _w, _h);
	color.set(255, 0, 0);
	registerMouse();
	registerTouch();
	enableGrabbing();
}

void ofxTangibleHandle::enableGrabbing() {
	setGrabbing(true);
}

void ofxTangibleHandle::disableGrabbing() {
	setGrabbing(false);
}

void ofxTangibleHandle::setGrabbing(bool bGrabbing) {
	bGrabbingEnabled = bGrabbing;
}

void ofxTangibleHandle::toggleGrabbing() {
	setGrabbing(!bGrabbingEnabled);
}

bool ofxTangibleHandle::isGrabbingEnabled() {
	return bGrabbingEnabled;
}

void ofxTangibleHandle::draw() {
	ofPushStyle();

	if (fillMe) {
		ofFill();
	} else {
		ofNoFill();
	}
	ofSetColor(color);
	if (drawType == TANGIBLE_DRAW_AS_RECT) {
		ofRect(x, y, width, height);
	} else if (drawType == TANGIBLE_DRAW_AS_CENTER_RECT) {
		ofSetRectMode(OF_RECTMODE_CENTER);
		ofRect(x, y, width, height);
	} else {
		ofCircle(x, y, width / 2, width / 2);
	}

	ofPopStyle();
}

void ofxTangibleHandle::moveInner(float dx, float dy) {
	moveBy(dx, dy);
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

	moveInner(dx, dy);

	pX = e.x;
	pY = e.y;
}

void ofxTangibleHandle::mouseReleased(ofMouseEventArgs &e) {
	if (!bPressed)
		return;
	bPressed = false;
}

void ofxTangibleHandle::touchDown(ofTouchEventArgs &e) {
	if (!bGrabbingEnabled || !isOver(e.x, e.y) || bPressed)
		return;

	touchId = e.id;
	bPressed = true;

	pX = e.x;
	pY = e.y;
}

void ofxTangibleHandle::touchMoved(ofTouchEventArgs &e) {
	if (!bGrabbingEnabled || !bPressed)
		return;

	if (touchId != e.id)
		return;

	float dx = e.x - pX;
	float dy = e.y - pY;

	moveBy(dx, dy);

	pX = e.x;
	pY = e.y;
}

void ofxTangibleHandle::touchUp(ofTouchEventArgs &e) {
	if (!bGrabbingEnabled || !bPressed)
		return;

	if (touchId != e.id)
		return;

	bPressed = false;
}

