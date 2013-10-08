#pragma once

#include "ofxTangibleHandle.h"

class ofxRotaryKnob : public ofxTangibleHandle{
public:
	ofxRotaryKnob();

	//mouse interaction
	virtual void mousePressed(ofMouseEventArgs &e);
	virtual void mouseDragged(ofMouseEventArgs &e);
	virtual void mouseReleased(ofMouseEventArgs &e);

	//touch interaction
	virtual void touchDown(ofTouchEventArgs &e);
	virtual void touchMoved(ofTouchEventArgs &e);
	virtual void touchUp(ofTouchEventArgs &e);

	virtual void drawInner();
};
