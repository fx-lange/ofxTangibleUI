#ifndef OFXTANGIBLEBUTTON_H_
#define OFXTANGIBLEBUTTON_H_

#include "ofxTangibleToggle.h"

class ofxTangibleButton : public ofxTangibleToggle{
public:
	//mouse interaction
	virtual void mousePressed(ofMouseEventArgs &e);
	virtual void mouseReleased(ofMouseEventArgs &e);

	//touch interaction
	virtual void touchDown(ofTouchEventArgs &e);
	virtual void touchUp(ofTouchEventArgs & e);
};

#endif /* OFXTANGIBLEBUTTON_H_ */
