/*
 * ofxTangibleHandle.cpp
 */

/*TODO
 * hover?!
 * */

#include "ofxTangibleHandle.h"

ofxTangibleHandle::ofxTangibleHandle() :
	bGrabbingEnabled(false), fillMe(false){
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
	ofPushMatrix();

	if (fillMe) {
		ofFill();
	} else {
		ofNoFill();
	}
	ofSetColor(color);
	if (drawType == TANGIBLE_DRAW_AS_RECT) {
//		ofTranslate(width/2.f,height/2.f);
//		ofTranslate(x,y);
//		ofRotate(innerRotate);
//		ofSetRectMode(OF_RECTMODE_CENTER);
//		ofRect(0, 0, width, height);
//		ofTranslate(x,y);
//			ofVec3f vecToShapeCenter = ofVec3f(width/2.f,height/2.f);
//			vecToShapeCenter.rotate(0,0,innerRotate);
//			ofTranslate(x,y);
//			ofCircle(0,0,5,5);
//			ofTranslate(vecToShapeCenter);
//			ofRotate(innerRotate);
//			ofCircle(0,0,5,5);
//			ofRect(0, 0, width, height);
//			vecToShapeCenter.rotate(0,0,-innerRotate);
//			ofTranslate(-vecToShapeCenter);
//			ofRect(0, 0, width, height);
				ofVec3f vecToShapeCenter = ofVec3f(width/2.f,height/2.f);
				ofTranslate(x,y);
				ofCircle(0,0,5,5);
				ofRotate(innerRotate);
				ofTranslate(-vecToShapeCenter);
				ofRect(0, 0, width, height);
	} else if (drawType == TANGIBLE_DRAW_AS_CENTER_RECT) {
		ofTranslate(x,y);
		ofRotate(innerRotate);
		ofSetRectMode(OF_RECTMODE_CENTER);
		ofRect(0, 0, width, height);
	} else {
		ofTranslate(x,y);
		ofEllipse(0, 0, width, height);
	}

	ofPopMatrix();
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
		bPressedByTouch = true;
	}else if(touchs.size()==1){
		touchs.push_back(e);
		touchs.back().x = touchX;
		touchs.back().y = touchY;
		//calc center
		touchCenter = (touchs[0] + touchs[1]) /2.f;
		//calc rotation
		angleToTouchCenter = (touchs[0] - touchCenter).angle(base);
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
		touchCursor & te = touchs[0];
		if(e.id == te.id){
			float dx = touchX - te.x;
			float dy = touchY - te.y;

			moveInner(dx, dy);
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
			touchCursor & et = touchs[1-otherIdx];
			et = e;
			if(bScaleTouchEvent){
				et.x *= ofGetWidth();
				et.y *= ofGetHeight();
			}
			//pan
			touchCursor & other = touchs[otherIdx];
			ofVec2f newCenter = (et+other)/2.f;
			ofVec2f diff = newCenter - touchCenter;
			moveInner(diff.x, diff.y);
			touchCenter = newCenter;
			//rotate
			float newAngle = (touchs[0] - touchCenter).angle(base);
			rotateInner(angleToTouchCenter - newAngle);
			angleToTouchCenter = newAngle;
		}
	}
}

void ofxTangibleHandle::touchUp(ofTouchEventArgs &e) {
	if (!bGrabbingEnabled )
		return;

	vector<touchCursor>::iterator it = touchs.begin();
	for(;it!=touchs.end();++it){
		touchCursor & et = *it;
		if(et.id==e.id){
			touchs.erase(it);
			break;
		}
	}

	if(touchs.empty())
		bPressedByTouch = false;
}

