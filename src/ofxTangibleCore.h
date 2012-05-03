/*
 * ofxTangibleCore.h
 */

#ifndef OFXTANGIBLECORE_H_
#define OFXTANGIBLECORE_H_

#include "ofxListener.h"

class ofxTangibleCore: public ofxListener {
public:
	float width, height;

	ofxTangibleCore(){
		bMouseRegistered = false;
	}

	virtual ~ofxTangibleCore();

	void setup(const ofRectangle & rect){
		setup(rect.x,rect.y,rect.width,rect.height);
	}

	void setup(const ofPoint &center,float w, float h){
		setup(center.x,center.y,w,h);
	}

	virtual void setup(float _x,float _y, float _w, float _h);

	//TODO copyconstructor and destrcutor - see ofxGrabbablePolyLine
	virtual void registerMouse();
	virtual void unregisterMouse();

	virtual void mousePressed(ofMouseEventArgs &e) = 0; //REVISIT perhaps use wrapper functions like in simpleguitoo
	virtual void mouseDragged(ofMouseEventArgs &e) = 0;
	virtual void mouseReleased(ofMouseEventArgs &e) = 0;

	virtual void draw() = 0;

protected:
	float pX, pY;

	bool bMouseRegistered;
	virtual bool isOver(float px, float py);
};

#endif OFXTANGIBLECORE_H_
