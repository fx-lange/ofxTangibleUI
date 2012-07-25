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
};

class ofxTangibleRotateEvent : public ofEventArgs{
public:
	int id;
	float angle;
	static ofEvent <ofxTangibleRotateEvent> events;
};

class ofxTransmitter {
public:
	static int generateId(){
		return generatedId++;
	}

	ofxTransmitter();
	virtual ~ofxTransmitter(){};

	int getId(){
		return id;
	}

protected:
	virtual void moveListeners(float dx, float dy);
	virtual void rotateListeners(float angle);

private:
	int id;
	static int generatedId;
};

#endif /* OFXTRANSMITTER_H_ */
