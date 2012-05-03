/*
 * ofxTangibleCore.h
 *
 *  Created on: May 3, 2012
 *      Author: spta
 */

#ifndef OFXTANGIBLECORE_H_
#define OFXTANGIBLECORE_H_

#include "ofxListener.h"

class ofxTangibleCore: public ofxListener {
public:
	float width, height;

	ofxTangibleCore(){
		isMouseRegistered = false;
	}
	virtual ~ofxTangibleCore();

	//TODO copyconstructor and destrcutor - see ofxGrabbablePolyLine
	virtual void registerMouse();
	virtual void unregisterMouse();

	virtual void mousePressed(ofMouseEventArgs &e) = 0; //REVISIT perhaps use wrapper functions like in simpleguitoo
	virtual void mouseDragged(ofMouseEventArgs &e) = 0;
	virtual void mouseReleased(ofMouseEventArgs &e) = 0;

protected:
	float pX, pY;

	bool isMouseRegistered;
	virtual bool isOver(float px, float py);
};

#endif OFXTANGIBLECORE_H_
