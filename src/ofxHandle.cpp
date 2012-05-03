/*
 * ofxHandle.cpp
 *
 *  Created on: May 3, 2012
 *      Author: spta
 */

#include "ofxHandle.h"


void ofxHandle::mousePressed(ofMouseEventArgs &e) {
	if (!bGrabbingEnabled || !isOver(e.x, e.y))
		return;

	bPressed = true;

	pX = e.x;
	pY = e.y;
}

void ofxHandle::mouseDragged(ofMouseEventArgs &e) {
	if (!bGrabbingEnabled || !bPressed)
		return;

	float dx = e.x - pX;
	float dy = e.y - pY;

	moveBy(dx,dy);

	pX = e.x;
	pY = e.y;
}

void ofxHandle::mouseReleased(ofMouseEventArgs &e) {
	if (!bGrabbingEnabled || !bPressed)
		return;

	bPressed = false;
}

