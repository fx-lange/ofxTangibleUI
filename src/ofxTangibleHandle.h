/*
 * ofxTangibleHandle.h
 */

#ifndef OFXHANDLE_H_
#define OFXHANDLE_H_

#include "ofxTangibleCore.h"

struct touchCursor : public ofVec2f{
	int id;

	touchCursor& operator=(const ofTouchEventArgs& e){
		x = e.x;
		y = e.y;
		id = e.id;
		return *this;
	}

	touchCursor(const ofTouchEventArgs& e){
		x = e.x;
		y = e.y;
		id = e.id;
	}
};

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

	virtual void mouseDragged(ofMouseEventArgs &e);
	virtual void mousePressed(ofMouseEventArgs &e);
	virtual void mouseReleased(ofMouseEventArgs &e);

	virtual void touchDown(ofTouchEventArgs &e);
	virtual void touchMoved(ofTouchEventArgs &e);
	virtual void touchUp(ofTouchEventArgs &e);

protected:
	bool bGrabbingEnabled;

	vector<touchCursor> touchs;
	ofVec2f touchCenter;
	float angleToTouchCenter;

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
