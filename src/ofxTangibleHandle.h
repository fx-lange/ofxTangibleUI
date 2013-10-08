#ifndef OFXHANDLE_H_
#define OFXHANDLE_H_

#include "ofxTangibleCore.h"

/* TODO
 * hover?!
 * test >=3 finger rotation (any problems?) */

struct touchCursor : public ofVec2f{
	int id;
	touchCursor& operator=(const ofTouchEventArgs& e);
	touchCursor(const ofTouchEventArgs& e);
};

class ofxTangibleHandle : public ofxTangibleCore{
public:
	bool fillMe;

	ofxTangibleHandle();
	//default destructor and copy/assignment constructor

	virtual void setup(float _x,float _y, float _w, float _h);

	//control whether grabbing the object is possible
	virtual void enableGrabbing();
	virtual void disableGrabbing();
	virtual void setGrabbing(bool bGrabbing);
	virtual void toggleGrabbing();
	virtual bool isGrabbingEnabled();

	//mouse interaction
	virtual void mousePressed(ofMouseEventArgs &e);
	virtual void mouseDragged(ofMouseEventArgs &e);
	virtual void mouseReleased(ofMouseEventArgs &e);

	//touch interaction
	virtual void touchDown(ofTouchEventArgs &e);
	virtual void touchMoved(ofTouchEventArgs &e);
	virtual void touchUp(ofTouchEventArgs &e);

protected:
	bool bGrabbingEnabled;

	vector<touchCursor> touchs; //0-2 touch cursor stored
	ofVec2f touchCenter;		//center of touch cursors
	float angleToTouchCenter;	//angle of the touch cursors to the touchCenter

	/* is called by draw()
	 * coordinate system is centered at x,y and rotated by innerRotate
	 * you should override this function to style your own class */
	virtual void drawInner();
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
