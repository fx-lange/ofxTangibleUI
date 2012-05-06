/*
 * ofxToggle.h
 */

#ifndef OFXTOGGLE_H_
#define OFXTOGGLE_H_

#include "ofxTangibleCore.h"

class ofxToggle : public ofxTangibleCore{
public:

	ofColor color;

	virtual void setup(float _x,float _y, float _w, float _h);

	virtual void draw();

	bool isActive(){
		return bActive;
	}

	void setActive(bool active){
		bActive = active;
	}

	bool hasChanged(){
		return bChanged;
	}

	void resetChanged(){
		bChanged = false;
	}

	virtual void mouseDragged(ofMouseEventArgs &e);
	virtual void mousePressed(ofMouseEventArgs &e);
	virtual void mouseReleased(ofMouseEventArgs &e);

protected:
	bool bPressed;
	bool bClickable;
	bool bActive;
	bool bChanged;
};

#endif /* OFXTOGGLE_H_ */
