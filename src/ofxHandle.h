/*
 * ofxHandle.h
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

class ofxHandleYFixed : public ofxHandle{
	virtual void moveBy(float dx, float dy){
		ofxListener::moveBy(dx,0.f);
	}
};

class ofxHandleXFixed : public ofxHandle{
	virtual void moveBy(float dx, float dy){
		ofxListener::moveBy(0.f,dy);
	}
};

#endif /* OFXHANDLE_H_ */
