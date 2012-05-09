/*
 * ofxHandle.h
 */

#ifndef OFXHANDLE_H_
#define OFXHANDLE_H_

#include "ofxTangibleCore.h"

class ofxTangibleHandle : public ofxTangibleCore{
public:
	ofColor color;
	bool fillMe;

	virtual void setup(float _x,float _y, float _w, float _h);

	virtual void draw();

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

class ofxTangibleYFixedHandle : public ofxTangibleHandle{
	virtual void moveBy(float dx, float dy){
		ofxListener::moveBy(dx,0.f);
	}
};

class ofxTangibleXFixedHandle : public ofxTangibleHandle{
	virtual void moveBy(float dx, float dy){
		ofxListener::moveBy(0.f,dy);
	}
};

#endif /* OFXHANDLE_H_ */
