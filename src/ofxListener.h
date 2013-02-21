#ifndef OFXLISTENER_H_
#define OFXLISTENER_H_

#include "ofMain.h"
#include "ofxTransmitter.h"

/*REVISIT
 * incorrect naming?!
 */

enum tangibleEventType {
	TANGIBLE_MOVE, TANGIBLE_ROTATE
};

/* ofxListener
 * - movable class but only by "listening" and not by interaction (unlike ofxTangibileCore)
 * - any listener can be transmitter
 * - base class for ofxTangibleCore
 */
class ofxListener: public ofPoint, public ofxTransmitter {
public:
	ofxListener();
	virtual ~ofxListener();

	ofxListener(const ofxListener& other);
	ofxListener& operator=(const ofxListener& other);

	virtual void setup(float x, float y);

	//methods to move or rotate by event
	virtual void moveEvent(ofxTangibleMoveEvent & e);
	virtual void rotateEvent(ofxTangibleRotateEvent & e);

	//core movement and rotation functionality
	virtual void moveBy(float dx, float dy);
	virtual void rotateBy(float angle, float distance = 0);

	/* listening concept:
	 * ofxListener is listening to one static ofEvent - not to one ofEvent per transmitter!
	 * to filter all incoming tangible move or rotate events ofxListener stores the ids of corresponding transmitters.
	 * this solution (which is not using all advantages of the oF event system) is needed to
	 * ensure copy constructor safety.
	 * alternative: store pointers to transmitters, where each one has its own ofEvent. than could copy constructor
	 * and destructor add and remove transmitters via their pointers to ensure consistent connections/transmissions.
	*/
	virtual void startListeningTo(ofxTransmitter & transmitter, tangibleEventType type = TANGIBLE_MOVE);
	virtual void startListeningTo(ofxTransmitter * transmitter, tangibleEventType type = TANGIBLE_MOVE);
	virtual void startListeningTo(const int id, tangibleEventType type);
	virtual void stopListeningTo(ofxTransmitter & transmitter, tangibleEventType type);
	virtual void stopListeningTo(ofxTransmitter * transmitter, tangibleEventType type);
	virtual void stopListeningTo(const int id, tangibleEventType type);

	void setMoveListenersSpeed(float vx, float vy);
	void setMoveListenersSpeed(const ofVec2f & v);
	const ofVec2f& getMoveListenerSpeed() const;

	//
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

	virtual void rotateInner(float degree); //TODO move up?, naming - rotate shape/ object vs rotateBy() = moveByRotate - rotateAroundRotationCenter
	float innerRotate;
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
