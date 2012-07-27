/*
 * ofxTangibleHandle.h
 */

#ifndef OFXHANDLE_H_
#define OFXHANDLE_H_

#include "ofxTangibleCore.h"

class ofxTangibleHandle : public ofxTangibleCore{
public:
	ofColor color;
	bool fillMe;

	ofxTangibleHandle();
	//default destructor and copy/assignment constructor

	virtual void setup(float _x,float _y, float _w, float _h);

	virtual void draw();

	virtual void enableGrabbing();
	virtual void disableGrabbing();
	virtual void setGrabbing(bool bGrabbing);
	virtual void toggleGrabbing();
	virtual bool isGrabbingEnabled();

//	void setPressed(bool pressed, float x, float y){
//		bPressed = pressed;
//		pX = x;
//		pY = y;
//	}

	virtual void mouseDragged(ofMouseEventArgs &e);
	virtual void mousePressed(ofMouseEventArgs &e);
	virtual void mouseReleased(ofMouseEventArgs &e);

	virtual void touchDown(ofTouchEventArgs &e);
	virtual void touchMoved(ofTouchEventArgs &e);
	virtual void touchUp(ofTouchEventArgs &e);

	bool bPressed;
protected:
	bool bGrabbingEnabled;

	virtual void moveInner(float dx, float dy);

//	virtual void _dragged(float x, float y);
//	virtual void _down(float x,float y);
//	virtual void _up(float x,float y);
};

class ofxTangibleYFixedHandle : public ofxTangibleHandle{
public:
	virtual void moveBy(float dx, float dy){
		ofxListener::moveBy(dx,0.f);
	}
};

class ofxTangibleXFixedHandle : public ofxTangibleHandle{
public:
	virtual void moveBy(float dx, float dy){
		ofxListener::moveBy(0.f,dy);
	}
};

#endif /* OFXHANDLE_H_ */
