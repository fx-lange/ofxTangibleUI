/*
 * ofxTangibleToggle.h
 */

#ifndef OFXTOGGLE_H_
#define OFXTOGGLE_H_

#include "ofxTangibleCore.h"

class ofxTangibleToggle : public ofxTangibleCore{
public:

	ofColor color;

	ofxTangibleToggle();

	//default copy and assignment constructor

	virtual void setup(float _x,float _y, float _w, float _h);

	virtual void draw();

	bool isActive();
	void setActive(bool active);
	bool hasChanged();
	void resetChanged();

	virtual void mouseMoved(ofMouseEventArgs &e);
	virtual void mousePressed(ofMouseEventArgs &e);
	virtual void mouseReleased(ofMouseEventArgs &e);

	virtual void touchDown(ofTouchEventArgs &e);
	virtual void touchUp(ofTouchEventArgs &e);

protected:
	bool bPressed;
	bool bClickable;
	bool bActive;
	bool bChanged;
};

#endif /* OFXTOGGLE_H_ */
