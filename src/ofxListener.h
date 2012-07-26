/*
 * ofxListener.h
 */

#ifndef OFXLISTENER_H_
#define OFXLISTENER_H_

#include "ofMain.h"
#include "ofxTransmitter.h"

/*TODO REVISIT
 * incorrect naming?!
 */

enum tangibleEventType {
	TANGIBLE_MOVE, TANGIBLE_ROTATE
};

class ofxListener: public ofPoint, public ofxTransmitter {
public:
	ofPoint rotateCenter;
	ofVec3f base;
	ofVec3f zeroBaseCheck;
	float oldAngle;

	ofxListener();
	virtual ~ofxListener();

	ofxListener(const ofxListener& other);
	ofxListener& operator=(const ofxListener& other);

	virtual void setup(float x, float y);

	virtual void moveEvent(ofxTangibleMoveEvent & e);
	virtual void rotateEvent(ofxTangibleRotateEvent & e);

	virtual void moveBy(float dx, float dy);
	virtual void rotateBy(float angle);

	void startListeningTo(ofxTransmitter & transmitter, tangibleEventType type = TANGIBLE_MOVE);
	void startListeningTo(ofxTransmitter * transmitter, tangibleEventType type = TANGIBLE_MOVE);
	void startListeningTo(const int id, tangibleEventType type);
	void stopListeningTo(ofxTransmitter & transmitter, tangibleEventType type);
	void stopListeningTo(ofxTransmitter * transmitter, tangibleEventType type);
	void stopListeningTo(const int id, tangibleEventType type);

	void setMoveListenersSpeed(float vx, float vy);
	void setMoveListenersSpeed(ofVec2f & v);

protected:
	bool bLocked;
	ofVec2f moveListenersSpeed;
	virtual void updateOldAngle();

private:
	list<int> moveTransmitters;
	list<int> rotateTransmitters;
	bool bListeningToMove, bListeningToRotate;
	void init(const ofxListener& other);
};

#endif /* OFXLISTENER_H_*/
