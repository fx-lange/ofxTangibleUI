#ifndef OFXTOGGLE_H_
#define OFXTOGGLE_H_

#include "ofxTangibleCore.h"

class ofxTangibleToggle : public ofxTangibleCore{
public:
	ofxTangibleToggle();

	//default copy and assignment constructor

	virtual void setup(float _x,float _y, float _w, float _h);

	//control whether toggle is active and whether it's clickable
	bool isActive();
	void setActive(bool active, bool silent = false);
	void activateByEvent(bool & active);
	void setClickable(bool clickable);
	bool isClickable();

	//mouse interaction
	virtual void mouseMoved(ofMouseEventArgs &e);
	virtual void mousePressed(ofMouseEventArgs &e);
	virtual void mouseReleased(ofMouseEventArgs &e);

	//touch interaction
	virtual void touchDown(ofTouchEventArgs &e);
	virtual void touchUp(ofTouchEventArgs &e);

	/* add/remove methods of objects to be triggered if the state of the toggle changes
	 * TODO naming is inconsistent - compare to startListeningTo( MOVE/ROTATE )
	 * REVISIT consider to inherit from ofxToggle (ofxGui)
	 * TODO test if it's copy constructor safe */
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
	bool bActive;
	bool bDrawAsPressed; //REVISIT same as bPressed?! should be!

	/* is called by draw()
	 * coordinate system is centered at x,y and rotated by innerRotate
	 * you should override this function to style your own class */
	virtual void drawInner();
};

#endif /* OFXTOGGLE_H_ */
