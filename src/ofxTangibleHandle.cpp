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
	float touchX = e.x;
	float touchY = e.y;

	if(bScaleTouchEvent){
		touchX *= ofGetWidth();
		touchY *= ofGetHeight();
	}

	if (!bGrabbingEnabled || !isOver(touchX, touchY))
		return;

	if(touchs.empty()){
		touchs.push_back(e);
		touchs.back().x = touchX;
		touchs.back().y = touchY;
	}else if(touchs.size()==1){
		touchs.push_back(e);
		touchs.back().x = touchX;
		touchs.back().y = touchY;
		//calc center
		touchCenter.x = (touchs[0].x + touchs[1].x)/2.f;
		touchCenter.y = (touchs[0].y + touchs[1].y)/2.f;
	}//else ignore
}

void ofxTangibleHandle::touchMoved(ofTouchEventArgs &e) {
	if (!bGrabbingEnabled || touchs.empty())
		return;

	float touchX = e.x;
	float touchY = e.y;

	if(bScaleTouchEvent){
		touchX *= ofGetWidth();
		touchY *= ofGetHeight();
	}

	if(touchs.size()==1){
		ofTouchEventArgs & te = touchs[0];
		if(e.id == te.id){
			float dx = touchX - te.x;
			float dy = touchY - te.y;

			moveBy(dx, dy);
			te.x = touchX;
			te.y = touchY;
		}
	}else if(touchs.size()==2){
		int otherIdx = -1;
		if(e.id == touchs[0].id){
			otherIdx = 1;
		}else if(e.id == touchs[1].id){
			otherIdx = 0;
		}

		if(otherIdx!=-1){
			ofTouchEventArgs & et = touchs[1-otherIdx];
			et = e;
			if(bScaleTouchEvent){
				et.x *= ofGetWidth();
				et.y *= ofGetHeight();
			}
			ofTouchEventArgs & other = touchs[otherIdx];
			ofVec2f newCenter((et.x+other.x)/2.f,(et.y+other.y)/2.f);
			ofVec2f diff = newCenter - touchCenter;
			moveBy(diff.x, diff.y);
			touchCenter = newCenter;
		}
	}
}

void ofxTangibleHandle::touchUp(ofTouchEventArgs &e) {
	if (!bGrabbingEnabled )
		return;

	vector<ofTouchEventArgs>::iterator it = touchs.begin();
	for(;it!=touchs.end();++it){
		ofTouchEventArgs & et = *it;
		if(et.id==e.id){
			touchs.erase(it);
			break;
		}
	}
}

