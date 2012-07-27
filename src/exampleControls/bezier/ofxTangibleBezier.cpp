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
	if(controls.size()>0){
		bStartedAgain = true;
	}
}

void ofxTangibleBezier::stopDrawing(){
	bGrabbingEnabled = false;
	if(controls.size() > 0){
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

	if (controls.size() != 0) {
		return;
	}

	pX = e.x;
	pY = e.y;

	ofxTangibleBezierControl control;
	control.setup(e.x, e.y, 10, 10);
	control.r2.enableGrabbing();
	control.r1.keepSameDistance(true);
	controls.push_back(control);
}

void ofxTangibleBezier::mouseMoved(ofMouseEventArgs &e) {
	if (controls.size() == 0 || bPressed || !bGrabbingEnabled) {
		return;
	}

	if(bStartedAgain){
		ofxTangibleBezierControl control;
		control.setup(e.x, e.y, 10, 10);
		control.r2.enableGrabbing();
		control.r1.keepSameDistance(true);
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
	controls.back().r1.keepSameDistance(false);

	ofxTangibleBezierControl control;
	control.setup(e.x, e.y, 10, 10);
	control.r2.enableGrabbing();
	control.r1.keepSameDistance(true);
	controls.push_back(control);
}

void ofxTangibleBezier::draw() {
	if (controls.size() == 0)
		return;
	line.clear();
	line.addVertex(controls[0]);
	controls[0].draw();
	for (unsigned int i = 1; i < controls.size(); ++i) {
		line.bezierTo(controls[i - 1].r2, controls[i].r1, controls[i]);
		controls[i].draw();
	}
	line.draw();
}

