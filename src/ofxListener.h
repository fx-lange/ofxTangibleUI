#ifndef OFXLISTENER_H_
#define OFXLISTENER_H_

#include "ofMain.h"
#include "ofxTransmitter.h"

enum tangibleEventType {
	TANGIBLE_MOVE,
	TANGIBLE_MOVE_VERTICAL,
	TANGIBLE_MOVE_HORIZONTAL,
	TANGIBLE_ROTATE
};

/* ofxListener
 * - movable class but only by "listening" and not by interaction (unlike ofxTangibileCore)
 * - any listener can be a transmitter
 * - base class for ofxTangibleCore
 */
class ofxListener: public ofPoint, public ofxTransmitter {
public:
	ofxListener();
	virtual ~ofxListener();

	ofxListener(const ofxListener& other);
	ofxListener& operator=(const ofxListener& other);

	virtual void setup(float x, float y);

	//methods to handle events
	virtual void handleMoveEvent(ofxTangibleMoveEvent & e);
	virtual void handleRotateEvent(ofxTangibleRotateEvent & e);

	//methods to move or rotate by event or called external
	virtual void moveExternal(float dx,float dy);
	virtual void rotateExternal(float angle,float distance=0);

	//rotate listener shape around its center
	virtual void rotateInner(float degree); //REVISIT naming - rotate shape/object

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

	static void listenToEachOther(ofxListener & l1,ofxListener & l2, tangibleEventType type = TANGIBLE_MOVE);

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

	virtual void updateOldAngle();							//TODO perhaps need to be public or called internal if object size changes

	//core movement methods ...
	virtual void moveBy(float dx, float dy);				// by direction
	virtual void rotateBy(float angle, float distance = 0); // by rotation around a rotationCenter - //REVISIT naming? moveByRotate/roatetOuter/rotateAroundRotationCenter

	float innerRotate;
private:
	ofVec2f rotateCenter;
	float oldAngle;

	bool bKeepSameDistance;

	list<int> moveTransmitters;
	list<int> moveVerTransmitters;
	list<int> moveHorTransmitters;
	list<int> rotateTransmitters;
	bool bListeningToMove, bListeningToRotate;
	void copyInit(const ofxListener& other);
};

#endif /* OFXLISTENER_H_*/
