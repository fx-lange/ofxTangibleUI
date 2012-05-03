/*
 * ofxTangibleCore.cpp
 *
 *  Created on: May 3, 2012
 *      Author: spta
 */

#include "ofxTangibleCore.h"

ofxTangibleCore::ofxTangibleCore(float _x, float _y, float _width, float _height) :
		ofPoint(_x, _y) {
	width = _width;
	height = _height;
}

ofxTangibleCore::~ofxTangibleCore() {
	unregisterMouse();
}

virtual bool ofxTangibleCore::isOver(float px, float py) {
	if( px > x && py > y && px < x + width && py < y + height){
		return true;
	}else{
		return false;
	}
}

virtual void ofxTangibleCore::registerMouse() {
	ofAddListener(ofEvents.mousePressed, this, &ofxTangibleCore::mousePressed);
	ofAddListener(ofEvents.mouseDragged, this, &ofxTangibleCore::mouseDragged);
	ofAddListener(ofEvents.mouseReleased, this, &ofxTangibleCore::mouseReleased);
}

virtual void ofxTangibleCore::unregisterMouse(){
	ofRemoveListener(ofEvents.mousePressed, this, &ofxTangibleCore::mousePressed);
	ofRemoveListener(ofEvents.mouseDragged, this, &ofxTangibleCore::mouseDragged);
	ofRemoveListener(ofEvents.mouseReleased, this, &ofxTangibleCore::mouseReleased);
}

