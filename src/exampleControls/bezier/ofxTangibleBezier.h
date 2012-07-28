#ifndef OFXTANGIBLEBEZIER_H_
#define OFXTANGIBLEBEZIER_H_

#include "ofMain.h"
#include "ofxTangibleBezierControl.h"

//TODO helper to a new controller should keep the same distance

class ofxTangibleBezier: public ofxTangibleCore {
public:

	//default constructor and so on

	virtual void setup();
	virtual void clear();

	virtual void startDrawing();
	virtual void stopDrawing();
	virtual void toggleDrawing();

	virtual void mousePressed(ofMouseEventArgs &e);
	virtual void mouseMoved(ofMouseEventArgs &e);
	virtual void mouseDragged(ofMouseEventArgs &e);
	virtual void mouseReleased(ofMouseEventArgs &e);

	virtual void draw();

protected:
	list<ofxTangibleBezierControl> controls;
	ofPolyline line;
	bool bPressed;
	bool bGrabbingEnabled;
	bool bStartedAgain;

};
#endif /* OFXTANGIBLEBEZIER_H_ */
