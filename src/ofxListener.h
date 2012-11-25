/*
 * ofxListener.h
 */

#ifndef OFXLISTENER_H_
#define OFXLISTENER_H_

#include "ofMain.h"
#include "ofxTransmitter.h"

/*TODO REVISIT
 * incorrect naming?!
 * much functionality has nothhing to do with the listening concept and therefore should get moved into the core
 */

enum tangibleEventType {
	TANGIBLE_MOVE, TANGIBLE_ROTATE
};

class ofxListener: public ofPoint, public ofxTransmitter {
public:
	ofxListener();
	virtual ~ofxListener();

	ofxListener(const ofxListener& other);
	ofxListener& operator=(const ofxListener& other);

	virtual void setup(float x, float y);

	virtual void moveEvent(ofxTangibleMoveEvent & e);
	virtual void rotateEvent(ofxTangibleRotateEvent & e);

	virtual void moveBy(float dx, float dy);
	virtual void rotateBy(float angle, float distance);

	void startListeningTo(ofxTransmitter & transmitter, tangibleEventType type = TANGIBLE_MOVE);
	void startListeningTo(ofxTransmitter * transmitter, tangibleEventType type = TANGIBLE_MOVE);
	void startListeningTo(const int id, tangibleEventType type);
	void stopListeningTo(ofxTransmitter & transmitter, tangibleEventType type);
	void stopListeningTo(ofxTransmitter * transmitter, tangibleEventType type);
	void stopListeningTo(const int id, tangibleEventType type);

	void setMoveListenersSpeed(float vx, float vy);
	void setMoveListenersSpeed(const ofVec2f & v);
	const ofVec2f& getMoveListenerSpeed() const;

	void setRotateCenter(float x, float y);
	void setRotateCenter(const ofVec2f& rc);
	void moveRotateCenter(float dx, float dy, bool bUpdateAngle = false);
	void moveRotateCenter(const ofVec2f& diff, bool bUpdateAngle = false);
	const ofVec2f& getRotateCenter() const;
	void setKeepSameDistance(bool sameDistance);

protected:
	bool bLocked;
	ofVec2f moveListenersSpeed;

	virtual void updateOldAngle();

	const ofVec3f base;
	const ofVec3f zeroBaseCheck;

	float innerRotate;
	virtual void rotateInner(float degree);
private:
	ofVec2f rotateCenter;
	float oldAngle;

	bool bKeepSameDistance;

	list<int> moveTransmitters;
	list<int> rotateTransmitters;
	bool bListeningToMove, bListeningToRotate;
	void init(const ofxListener& other);
};

#endif /* OFXLISTENER_H_*/
