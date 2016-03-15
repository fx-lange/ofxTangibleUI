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
	TANGIBLE_DRAW_AS_RECT,
	TANGIBLE_DRAW_AS_CENTER_RECT
};

class ofxXmlSettings;

class ofxTangibleCore: public ofxListener {
public:
	float width, height;
	tangibleDrawType drawType;

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
    virtual void mouseScrolled(ofMouseEventArgs &e){}
    virtual void mouseEntered(ofMouseEventArgs &e){}
    virtual void mouseExited(ofMouseEventArgs &e){}

	//Touch
	virtual void touchDoubleTap(ofTouchEventArgs &e){}
	virtual void touchDown(ofTouchEventArgs &e){}
	virtual void touchMoved(ofTouchEventArgs &e){}
	virtual void touchUp(ofTouchEventArgs &e){}
	virtual void touchCancelled(ofTouchEventArgs &e){}

	virtual void draw() = 0;

	virtual void saveToXml(ofxXmlSettings & xml);
	virtual void loadFromXml(ofxXmlSettings & xml);

	bool bPressed, bPressedByTouch;

	static ofCoreEvents * customEvents;
protected:
	float pX, pY;
	int touchId;

	virtual void registerMouse();
	virtual void unregisterMouse();

	virtual void registerTouch();
	virtual void unregisterTouch();

	template<class ListenerClass>
	static void registerCustomMouseEvents(ListenerClass * listener){
		ofAddListener(customEvents->mouseMoved,listener,&ListenerClass::mouseMoved);
		ofAddListener(customEvents->mousePressed,listener,&ListenerClass::mousePressed);
		ofAddListener(customEvents->mouseDragged,listener,&ListenerClass::mouseDragged);
		ofAddListener(customEvents->mouseReleased,listener,&ListenerClass::mouseReleased);
	}

	template<class ListenerClass>
	static void unregisterCustomMouseEvents(ListenerClass * listener){
		ofRemoveListener(customEvents->mouseMoved,listener,&ListenerClass::mouseMoved);
		ofRemoveListener(customEvents->mousePressed,listener,&ListenerClass::mousePressed);
		ofRemoveListener(customEvents->mouseDragged,listener,&ListenerClass::mouseDragged);
		ofRemoveListener(customEvents->mouseReleased,listener,&ListenerClass::mouseReleased);
	}

	template<class ListenerClass>
	static void registerCustomTouchEvents(ListenerClass * listener){
		ofAddListener(customEvents->touchDown,listener,&ListenerClass::touchDown);
		ofAddListener(customEvents->touchMoved,listener,&ListenerClass::touchMoved);
		ofAddListener(customEvents->touchUp,listener,&ListenerClass::touchUp);
	}

	template<class ListenerClass>
	static void unregisterCustomTouchEvents(ListenerClass * listener){
		ofRemoveListener(customEvents->touchDown,listener,&ListenerClass::touchDown);
		ofRemoveListener(customEvents->touchMoved,listener,&ListenerClass::touchMoved);
		ofRemoveListener(customEvents->touchUp,listener,&ListenerClass::touchUp);
	}

	virtual bool isOver(float px, float py);

private:
	bool bMouseRegistered, bTouchRegistered;
	void init(const ofxTangibleCore& other);
};

#endif /* OFXTANGIBLECORE_H_*/
