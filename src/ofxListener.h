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
	ofPoint rotateCenter;
	ofVec3f base;
	ofVec3f zeroBaseCheck;
	float oldAngle;

	ofxListener(){
		bLocked = false;
		setup(0,0);
	}

	ofxListener(const ofxListener& other);

	virtual ~ofxListener();

	virtual void setup(float _x,float _y){
		x = _x;
		y = _y;

		moveListenersSpeed.set(1.f,1.f);
		rotateCenter.set(0.f,0.f);

		base.set(0,-1);
		zeroBaseCheck.set(1,0);

		updateOldAngle();
	}

	virtual void moveBy(float dx, float dy);
	virtual void rotateBy(float angle);

	void addMoveListener(ofxListener* listener){
		movelisteners.push_back(listener);
		listener->addMoveTransmitter(this);
	}

	void addRotateListener(ofxListener* listener){
		rotatelisteners.push_back(listener);
		listener->addRotateTransmitter(this);
	}

	void removeMoveListener(ofxListener * listener);
	void removeRotateListener(ofxListener * listener);

	void setMoveListenersSpeed(float vx,float vy){
		moveListenersSpeed.set(vx,vy);
	}

	void setMoveListenersSpeed(ofVec2f & v){
		setMoveListenersSpeed(v.x,v.y);
	}

protected:
	bool bLocked;
	ofVec2f moveListenersSpeed;

	virtual void updateOldAngle(){
		oldAngle = (*this - rotateCenter).angle(base);
		if((*this - rotateCenter).angle(zeroBaseCheck) > 90.f){
			oldAngle *= -1.f;
		}
	}

	virtual void moveListeners(float dx, float dy);
	virtual void rotateListeners(float angle);

	std::list<ofxListener*> movelisteners;
	std::list<ofxListener*> rotatelisteners;
private:
	//only to organize the pointer structure
	std::list<ofxListener*> moveListensTo;
	void addMoveTransmitter(ofxListener* transmitter){
		moveListensTo.push_back(transmitter);
	}
	std::list<ofxListener*> rotateListensTo;
	void addRotateTransmitter(ofxListener* transmitter){
		moveListensTo.push_back(transmitter);
	}
};

#endif /* OFXLISTENER_H_*/
