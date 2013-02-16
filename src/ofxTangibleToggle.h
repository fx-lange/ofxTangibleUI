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
	void setActive(bool active, bool silent = false);
	void activateByEvent(bool & active);
	bool hasChanged();
	void resetChanged();
	void setClickable(bool clickable);
	bool isClickable();

	virtual void mouseMoved(ofMouseEventArgs &e);
	virtual void mousePressed(ofMouseEventArgs &e);
	virtual void mouseReleased(ofMouseEventArgs &e);

	virtual void touchDown(ofTouchEventArgs &e);
	virtual void touchUp(ofTouchEventArgs &e);

	//TODO consider to inherit from ofxToggle (ofxGui)
	//TODO cpy constructor safe?
	template<class ListenerClass>
	void addEventListener(ListenerClass * listener, void ( ListenerClass::*method )(bool&)){
		ofAddListener(hasChangedEvent,listener,method);
	}

	template<class ListenerClass>
	void removeEventListener(ListenerClass * listener, void ( ListenerClass::*method )(bool&)){
		ofRemoveListener(hasChangedEvent,listener,method);
	}

protected:
	bool bClickable;
	ofEvent<bool> hasChangedEvent;
	bool bActive, bDrawAsPressed;
	bool bChanged;
};

#endif /* OFXTOGGLE_H_ */
