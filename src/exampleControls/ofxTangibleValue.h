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

	virtual void setValue(float val);
	virtual float getValue();

	virtual void setMinValue(float min);
	virtual void setMaxValue(float max);
	virtual void setPixelToValueScaleFactor(float scale);
	virtual void setRoundTo(float roundTo);

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

	virtual void calcValueByPos(const ofVec2f & first,const ofVec2f & now);
	virtual void checkMinMax(float & val);
	virtual void roundValue(float & val);

	virtual void confirmValue();
	virtual void clearDraggedDistance();	//for state safety: if the value gets changed (from outside) while pressed

	float value;
	bool bClearDragging;
};


