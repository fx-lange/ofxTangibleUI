#pragma once

#include "ofMain.h"
#include "ofxTangibleHandle.h"

//TODO scale,inverse (=scale -1),calc sub methods
//fontSize

enum tangibleCalcValueMode{
	TANGIBLE_VALUE_MODE_VERTICAL,
	TANGIBLE_VALUE_MODE_HORIZONTAL,
	TANGIBLE_VALUE_MODE_BOTH
};

class ofxTangibleValue : public ofxTangibleHandle {
public:

	tangibleCalcValueMode calcValueMode;

	ofxTangibleValue();

	float getValue();

	void toggleUpdateAfterRelease();

	//mouse interaction
	virtual void mousePressed(ofMouseEventArgs &e);
	virtual void mouseDragged(ofMouseEventArgs &e);
	virtual void mouseReleased(ofMouseEventArgs &e);

	//touch interaction
	virtual void touchDown(ofTouchEventArgs &e);
	virtual void touchMoved(ofTouchEventArgs &e);
	virtual void touchUp(ofTouchEventArgs &e);

	virtual void drawInner();

protected:
	float tmpValue; //?
	bool bUpdateValueAfterRelease;

	void calcValueByPos(const ofVec2f & first,const ofVec2f & now);
	float value;
};


