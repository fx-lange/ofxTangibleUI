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

void ofxTangibleHandle::clear(){
	bPressed = bPressedByTouch = false;
	touchs.clear();
}

void ofxTangibleHandle::enableGrabbing() {
	setGrabbing(true);
}

void ofxTangibleHandle::disableGrabbing() {
	setGrabbing(false);
}

void ofxTangibleHandle::setGrabbing(bool bGrabbing) {
	bGrabbingEnabled = bGrabbing;
	clear();
}

void ofxTangibleHandle::toggleGrabbing() {
	setGrabbing(!bGrabbingEnabled);
}

bool ofxTangibleHandle::isGrabbingEnabled() {
	return bGrabbingEnabled;
}


void ofxTangibleHandle::drawInner(){
	if (fillMe) {
		ofFill();
	} else {
		ofNoFill();
	}

	ofSetColor(color);
	ofxTangibleCore::drawInner();
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

	moveInternal(dx, dy);

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
		angleToTouchCenter = ofRadToDeg(atan2(touchs[0].x - touchCenter.x,touchs[0].y - touchCenter.y));
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

			moveInternal(dx, dy);
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
			moveInternal(diff.x, diff.y);
			touchCenter = newCenter;
			//rotate
			float newAngle = ofRadToDeg(atan2(touchs[0].x - touchCenter.x,touchs[0].y - touchCenter.y));
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

touchCursor& touchCursor::operator=(const ofTouchEventArgs& e){
	x = e.x;
	y = e.y;
	id = e.id;
	return *this;
}

touchCursor::touchCursor(const ofTouchEventArgs& e){
	x = e.x;
	y = e.y;
	id = e.id;
}

