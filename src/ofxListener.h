/*
 * ofxListener.h
 */

#ifndef OFXLISTENER_H_
#define OFXLISTENER_H_

#include "ofMain.h"

/*TODO REVISIT
 * incorrect naming?!
 */

class ofxListener : public ofPoint{
public:
	ofxListener(){
		bLocked = false;
	}

	ofxListener(const ofxListener& other);

	virtual ~ofxListener();

	virtual void moveBy(float dx, float dy);

	void addListener(ofxListener* listener){
		listeners.push_back(listener);
		listener->addTransmitter(this);
	}

	void removeListener(ofxListener * listener);

protected:
	bool bLocked;

	void moveListener(float dx, float dy);

	std::list<ofxListener*> listeners;

private:
	//only to organize the pointer structure
	std::list<ofxListener*> listensTo;
	void addTransmitter(ofxListener* transmitter){
		listensTo.push_back(transmitter);
	}
};

#endif /* OFXLISTENER_H_*/
