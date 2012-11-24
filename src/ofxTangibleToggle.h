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

	//TODO consider to inherit from ofxToggle (ofxGui)
	template<class ListenerClass>
	void addListener(ListenerClass * listener, void ( ListenerClass::*method )(bool&)){
		ofAddListener(hasChangedEvent,listener,method);
	}

	template<class ListenerClass>
	void removeListener(ListenerClass * listener, void ( ListenerClass::*method )(bool&)){
		ofRemoveListener(hasChangedEvent,listener,method);
	}

protected:
	bool bPressed;
	bool bClickable;
	ofEvent<bool> hasChangedEvent;
	bool bActive, bTmpSwitch;
	bool bChanged;
};

#endif /* OFXTOGGLE_H_ */
