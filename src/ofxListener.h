/*
 * ofxListener.h
 */

#ifndef OFXLISTENER_H_
#define OFXLISTENER_H_

#include "ofMain.h"


class ofxListener : public ofPoint{
public:
	ofxListener(){
		bLocked = false;
	}

	//REVISIT public vs protected
//	void moveTo(float x, float y);
	virtual void moveBy(float dx, float dy);

	void addListener(ofxListener* listener){
		listeners.push_back(listener);
	}

protected:
	bool bLocked;

	void moveListener(float dx, float dy);

	std::list<ofxListener*> listeners;
};


#endif OFXLISTENER_H_
