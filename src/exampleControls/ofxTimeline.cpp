/*
 * ofxTimeLine.cpp
 *
 *  Created on: Jun 4, 2012
 *      Author: spta
 */

#include "ofxTimeline.h"

void ofxTimeline::setup(float x, float y, float w, float h, int range ) {
	lineHeight = 30;
	lineCount = round(h / lineHeight);
	h = lineCount * lineHeight;
	y = ofGetHeight() - h;

	ofxTangibleHandle::setup(x,y,20,20);

//	bGrabbingEnabled = false;
	dropZone = ofRectangle(x,y,w*4,h);
	timerange = range;

	addMoveListener(&dropZone);
	setMoveListenersSpeed(-3,0);
//	settings.x0 = &(dropZone.x);
//	settings.y0 = &(dropZone.y);
//	settings.timerange = &timerange;
//	settings.width = &(dropZone.width);
//	settings.height = &(dropZone.height);
//	settings.stepSize = &stepSize;
//	checkTimeGrabber = false;
}

void ofxTimeline::draw() {
	ofPushStyle();
	ofEnableAlphaBlending();
	ofFill();
	ofSetColor(190, 240, 0, 100);
	ofRect(dropZone);
	ofNoFill();
	ofSetColor(30, 30, 30, 255);
	ofRect(dropZone);

	//draw current timepoint
//	float diff = (ofGetSystemTime() - startTime) / 1000.f;
//	float lineX = diff * timerange / width;
//	ofSetColor(0, 0, 0, 255);
//	ofLine(lineX, y, lineX, dropZone.y + dropZone.height);

//draw rows
	ofSetColor(30, 30, 30, 80);
	for (int yi = dropZone.y; yi < dropZone.y + dropZone.height; yi +=
			(int) lineHeight) {
		ofLine(dropZone.x, yi, dropZone.width + dropZone.x, yi);
	}




	//draw ticks (every second)
	int tickSize = dropZone.width / timerange;
	int count = 0;
	ofSetColor(30, 30, 30, 80);
	for (int xi = dropZone.x; xi < dropZone.x + dropZone.width;
			xi += tickSize) {
		if (count++ % 30 == 0) { //mark every 30seconds
			ofPushStyle();
			ofSetColor(0, 0, 0, 240);
			ofLine(xi, dropZone.y - lineHeight, xi,
					dropZone.y + dropZone.height);
			ofPopStyle();
		} else {
			ofLine(xi, dropZone.y, xi, dropZone.y + dropZone.height);
		}
	}

	ofxTangibleHandle::draw();

	//draw animations
//	for (int i = 0; i < animations.size(); i++) {
//		ofPushStyle();
//		ofSetColor(colors[i]);
//		ofSetRectMode(OF_RECTMODE_CENTER);
//		float yy = y + dropZone.height - lineHeight * (i + 0.5);
//		ofxGrabbableObject * timegrabber = animations[i]->getTimeGrabber();
//
//		ofRect(10, yy, 5, 5);
//		ofSetColor(255);
//		ofLine(10, yy, timegrabber->x, timegrabber->y);
//		ofPopStyle();
//	}

	//draw time windows
//	for (int i = 0; i < timeWindows.size(); ++i) {
//		timeWindows[i]->draw();
//	}
	ofDisableAlphaBlending();
	ofPopStyle();
}

