#pragma once

#include "ofMain.h"
#include "ofxTangibleHandle.h"

//TODO calc sub methods

enum tangibleCalcValueMode{
	TANGIBLE_VALUE_MODE_VERTICAL,
	TANGIBLE_VALUE_MODE_HORIZONTAL,
	TANGIBLE_VALUE_MODE_BOTH
};

class ofxTangibleValue : public ofxTangibleHandle {
public:

	tangibleCalcValueMode calcValueMode;

	ofxTangibleValue();

	void setValue(float val);
	float getValue();

	void setMinValue(float min);
	void setMaxValue(float max);
	void setPixelToValueScaleFactor(float scale);
	void setRoundTo(float roundTo);

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
	float tmpValue, minValue, maxValue, scaleValue, roundTo;
	bool bUpdateValueAfterRelease;

	void calcValueByPos(const ofVec2f & first,const ofVec2f & now);
	void checkMinMax(float & val);
	void roundValue(float & val);
	float value;
};


