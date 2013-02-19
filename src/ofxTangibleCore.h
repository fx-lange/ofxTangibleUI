/*
 * ofxTangibleCore.h
 */

#ifndef OFXTANGIBLECORE_H_
#define OFXTANGIBLECORE_H_

#include "ofxListener.h"

/*TODO
 * save and load to and from xml
 */

enum tangibleDrawType{
	TANGIBLE_DRAW_AS_CIRCLE,
	TANGIBLE_DRAW_AS_CENTERED_RECT
};

class ofxXmlSettings;

class ofxTangibleCore: public ofxListener {
public:
	float width, height;
	tangibleDrawType drawType;
	bool bScaleTouchEvent;
	ofColor color;

	ofxTangibleCore();
	virtual ~ofxTangibleCore();

	ofxTangibleCore(const ofxTangibleCore& other);
	ofxTangibleCore& operator=(const ofxTangibleCore& other);

	virtual void setup(const ofRectangle & rect){
		setup(rect.x,rect.y,rect.width,rect.height);
	}

	virtual void setup(const ofPoint &center,float w, float h){
		setup(center.x,center.y,w,h);
	}

	virtual void setup(float _x,float _y, float _w, float _h);

	//Mouse
	virtual void mouseMoved(ofMouseEventArgs &e){}
	virtual void mousePressed(ofMouseEventArgs &e){}
	virtual void mouseDragged(ofMouseEventArgs &e){}
	virtual void mouseReleased(ofMouseEventArgs &e){}

	//Touch
	virtual void touchDoubleTap(ofTouchEventArgs &e){}
	virtual void touchDown(ofTouchEventArgs &e){}
	virtual void touchMoved(ofTouchEventArgs &e){}
	virtual void touchUp(ofTouchEventArgs &e){}
	virtual void touchCancelled(ofTouchEventArgs &e){}

	virtual void draw(); //for styling you should override drawInner() not draw() //TODO move to core?

	virtual void saveToXml(ofxXmlSettings & xml);
	virtual void loadFromXml(ofxXmlSettings & xml);

	bool bPressed, bPressedByTouch;//TODO change accessibility to protected
	bool bDrawDebug;
protected:

	float pX, pY;
	int touchId;

	virtual void registerMouse();
	virtual void unregisterMouse();

	virtual void registerTouch();
	virtual void unregisterTouch();

	virtual bool isOver(float px, float py);

	virtual void drawInner();
	virtual void drawDebug(); //as default same as drawInner - for later, once you start designing your own classes
private:
	bool bMouseRegistered, bTouchRegistered;
	void init(const ofxTangibleCore& other);
};

#endif /* OFXTANGIBLECORE_H_*/
