/*
 * ofxListener.h
 */

#ifndef OFXLISTENER_H_
#define OFXLISTENER_H_

#include "ofMain.h"

/*TODO REVISIT
 * potential null pointer exceptions - if listener will be deleted or moved (vector/container)
 * incorrect naming
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

	void removeListener(ofxListener * listener){
		list<ofxListener*>::iterator it = listeners.begin();
		for(;it!=listeners.end();++it){
			if(*it == listener){
				listeners.erase(it);
				break;
			}
		}
	}

protected:
	bool bLocked;

	void moveListener(float dx, float dy);

	std::list<ofxListener*> listeners;

private:
	std::list<ofxListener*> listensTo;
	void addTransmitter(ofxListener* transmitter){
		listensTo.push_back(transmitter);
	}
};

#endif OFXLISTENER_H_
