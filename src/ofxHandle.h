/*
 * ofxHandle.h
 *
 *  Created on: May 3, 2012
 *      Author: spta
 */

#ifndef OFXHANDLE_H_
#define OFXHANDLE_H_

#include "ofxTangibleCore.h"

class ofxHandle : public ofxTangibleCore{
public:
	ofColor color;
	bool fillMe;

	void setup(const ofRectangle & rect){
		setup(rect.x,rect.y,rect.width,rect.height);
	}

	void setup(const ofPoint &center,float w, float h){
		setup(center.x,center.y,w,h);
	}

	virtual void setup(float _x,float _y, float _w, float _h){
		x = _x;
		y = _y;
		width = _w;
		height = _h;
		color.set(255,0,0);
		fillMe = false;
		bPressed =	false;
		registerMouse();
	}

	void enableGrabbing() {
		setGrabbing(true);
	}

	void disableGrabbing() {
		setGrabbing(false);
	}

	virtual void setGrabbing(bool bGrabbing){
		bGrabbingEnabled = bGrabbing;
	}

	void toggleGrabbing(){
		setGrabbing(!bGrabbingEnabled);
	}

	virtual void mouseDragged(ofMouseEventArgs &e);
	virtual void mousePressed(ofMouseEventArgs &e);
	virtual void mouseReleased(ofMouseEventArgs &e);


protected:
	float pX, pY;
	bool bGrabbingEnabled;
	bool bPressed;
};

#endif /* OFXHANDLE_H_ */
