/*
 * ofxTransmitter.h
 */

#ifndef OFXTRANSMITTER_H_
#define OFXTRANSMITTER_H_

#include "ofMain.h"

class ofxTangibleMoveEvent : public ofEventArgs{
public:
	int id;
	float dx, dy;
	static ofEvent <ofxTangibleMoveEvent> events;

	//ofAddListener(ofxTangibleMoveEvent::events, this, &testApp::gameEvent);
};

class ofxTransmitter {
public:
	static int generateId(){
		return generatedId++;
	}

	ofxTransmitter();
	virtual ~ofxTransmitter();

	int getId(){
		return id;
	}

protected:
	virtual void moveListeners(float dx, float dy);

private:
	int id;
	static int generatedId;
};

#endif /* OFXTRANSMITTER_H_ */
