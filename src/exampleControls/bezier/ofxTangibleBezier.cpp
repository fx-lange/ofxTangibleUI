#include "ofxTangibleBezier.h"

void ofxTangibleBezier::setup() {
	ofxTangibleCore::setup(0, 0, 0, 0);
	registerMouse();
	bPressed = false;
	bGrabbingEnabled = false;
	bStartedAgain = false;
}

void ofxTangibleBezier::clear(){
	stopDrawing();
	controls.clear();
}

void ofxTangibleBezier::startDrawing(){
	bGrabbingEnabled = true;
	if(!controls.empty()){
		bStartedAgain = true;
	}
}

void ofxTangibleBezier::stopDrawing(){
	bGrabbingEnabled = false;
	if(!controls.empty()){
		controls.pop_back();
	}
}

void ofxTangibleBezier::toggleDrawing(){
	if(bGrabbingEnabled){
		stopDrawing();
	}else{
		startDrawing();
	}
}

void ofxTangibleBezier::mousePressed(ofMouseEventArgs &e) {
	if (bPressed || !bGrabbingEnabled) {
		return;
	}
	bPressed = true;

	if (!controls.empty()) {
		return;
	}

	pX = e.x;
	pY = e.y;

	ofxTangibleBezierControl control;
	control.setup(e.x, e.y, 10, 10);
	control.r2.enableGrabbing();
	control.r1.setKeepSameDistance(true);
	controls.push_back(control);
}

void ofxTangibleBezier::mouseMoved(ofMouseEventArgs &e) {
	if (controls.empty() || bPressed || !bGrabbingEnabled) {
		return;
	}

	if(bStartedAgain){
		ofxTangibleBezierControl control;
		control.setup(e.x, e.y, 10, 10);
		control.r2.enableGrabbing();
		control.r1.setKeepSameDistance(true);
		controls.push_back(control);
		bStartedAgain = false;
	}else{
		controls.back().moveBy(e.x - pX, e.y - pY);
	}
	pX = e.x;
	pY = e.y;
}

void ofxTangibleBezier::mouseDragged(ofMouseEventArgs &e) {
	pX = e.x;
	pY = e.y;
}

void ofxTangibleBezier::mouseReleased(ofMouseEventArgs &e) {
	bPressed = false;
	if (!bGrabbingEnabled) {
		return;
	}

	controls.back().enableGrabbing();
	controls.back().r1.enableGrabbing();
	controls.back().r1.setKeepSameDistance(false);

	ofxTangibleBezierControl control;
	control.setup(e.x, e.y, 10, 10);
	control.r2.enableGrabbing();
	control.r1.setKeepSameDistance(true);
	controls.push_back(control);
}

void ofxTangibleBezier::draw() {
	if (controls.empty())
		return;
	line.clear();
	BezierControls::iterator it_t0 = controls.begin();
	BezierControls::iterator it_t1 = controls.begin();
	it_t1++;
	line.addVertex(*it_t0);
	it_t0->draw();
	for (; it_t1 != controls.end(); ++it_t0,++it_t1) {
		ofxTangibleBezierControl & h0 = *it_t0;
		ofxTangibleBezierControl & h1 = *it_t1;
		line.bezierTo(h0.r2, h1.r1, h1);
		h1.draw();
	}
	line.draw();
}

