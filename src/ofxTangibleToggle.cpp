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
	if(drawType == TANGIBLE_DRAW_AS_RECT){
		ofRect(x,y,width,height);
	}else{
		ofCircle(x+width/2,y+width/2,width,width);
	}

	ofPopStyle();
}

void ofxTangibleToggle::mousePressed(ofMouseEventArgs &e) {
	if (!bClickable || !isOver(e.x, e.y))
		return;

	bPressed = true;
}

void ofxTangibleToggle::mouseReleased(ofMouseEventArgs &e) {
	if (!bClickable || !bPressed || !isOver(e.x, e.y))
		return;

	bActive = !bActive;
	bChanged = true;
	bPressed = false;
}

void ofxTangibleToggle::mouseMoved(ofMouseEventArgs &e){
	//TODO hover effets
}

void ofxTangibleToggle::touchDown(ofTouchEventArgs &e) {
	if (!bClickable || !isOver(e.x, e.y) || bPressed)
		return;

	touchId = e.id;
	bPressed = true;
}


void ofxTangibleToggle::touchUp(ofTouchEventArgs &e) {
	if (!bClickable || !bPressed || isOver(e.x,e.y))
		return;

	if(touchId != e.id)
		return;

	bActive = !bActive;
	bChanged = true;
	bPressed = false;
}
