/*
 * ofxListener.cpp
 */

#include "ofxListener.h"

ofxListener::ofxListener() {
	bLocked = false;
	bListeningToMove = bListeningToRotate = false;
	moveListenersSpeed.set(1.f,1.f);
	rotateCenter.set(0.f,0.f);

	base.set(0,-1);
	zeroBaseCheck.set(1,0);
}

ofxListener::~ofxListener(){
	if(bListeningToMove){
		bListeningToMove = false;
		ofRemoveListener(ofxTangibleMoveEvent::events, this, &ofxListener::moveEvent);
	}
	if(bListeningToRotate){
		bListeningToRotate = false;
		ofRemoveListener(ofxTangibleRotateEvent::events, this, &ofxListener::rotateEvent);
	}
}

ofxListener::ofxListener(const ofxListener& other):
	ofxTransmitter(other){
	init(other);
	ofLog(OF_LOG_VERBOSE,"ofxListener COPY");
}

ofxListener& ofxListener::operator=(const ofxListener& other){
	init(other);
	return *this;
}

void ofxListener::init(const ofxListener& other){
	x = other.x;
	y = other.y;
	bLocked = other.bLocked;

	rotateCenter = other.rotateCenter;
	moveListenersSpeed = other.moveListenersSpeed;
	base = other.base;
	zeroBaseCheck = other.zeroBaseCheck;
	oldAngle = other.oldAngle;

	bListeningToMove = other.bListeningToMove;
	bListeningToRotate = other.bListeningToRotate;
	if(bListeningToMove){
		ofAddListener(ofxTangibleMoveEvent::events,this,&ofxListener::moveEvent);
		moveTransmitters = other.moveTransmitters;
	}
	if(bListeningToRotate){
		ofAddListener(ofxTangibleRotateEvent::events,this,&ofxListener::rotateEvent);
		rotateTransmitters = other.rotateTransmitters;
	}
}

void ofxListener::setup(float _x,float _y){
	x = _x;
	y = _y;

	updateOldAngle();
}

void ofxListener::startListeningTo(ofxTransmitter & transmitter,tangibleEventType type){
	startListeningTo(transmitter.getId(),type);
}

void ofxListener::startListeningTo(ofxTransmitter * transmitter,tangibleEventType type){
	startListeningTo(transmitter->getId(),type);
}

void ofxListener::startListeningTo(const int id,tangibleEventType type){
	if(type == TANGIBLE_MOVE){
		moveTransmitters.push_back(id);
		if(moveTransmitters.size()>0 && !bListeningToMove){
			bListeningToMove = true;
			ofAddListener(ofxTangibleMoveEvent::events, this, &ofxListener::moveEvent);
		}
	}else if(type == TANGIBLE_ROTATE){
		rotateTransmitters.push_back(id);
		if(rotateTransmitters.size()>0 && !bListeningToRotate){
			bListeningToRotate = true;
			ofAddListener(ofxTangibleRotateEvent::events, this, &ofxListener::rotateEvent);
		}
	}
}

void ofxListener::stopListeningTo(ofxTransmitter & transmitter,tangibleEventType type){
	stopListeningTo(transmitter.getId(),type);
}

void ofxListener::stopListeningTo(ofxTransmitter * transmitter,tangibleEventType type){
	stopListeningTo(transmitter->getId(),type);
}

void ofxListener::stopListeningTo(const int id,tangibleEventType type){
	if(type == TANGIBLE_MOVE){
		moveTransmitters.remove(id);
		if(moveTransmitters.size()==0 && bListeningToMove){
			bListeningToMove = false;
			ofRemoveListener(ofxTangibleMoveEvent::events, this, &ofxListener::moveEvent);
		}
	}else if(type == TANGIBLE_ROTATE){
		rotateTransmitters.remove(id);
		if(rotateTransmitters.size()==0 && bListeningToRotate){
			bListeningToRotate = false;
			ofRemoveListener(ofxTangibleRotateEvent::events, this, &ofxListener::rotateEvent);
		}
	}
}

void ofxListener::setMoveListenersSpeed(float vx,float vy){
	moveListenersSpeed.set(vx,vy);
}

void ofxListener::setMoveListenersSpeed(ofVec2f & v){
	setMoveListenersSpeed(v.x,v.y);
}

void ofxListener::moveEvent(ofxTangibleMoveEvent & e){
	bool bListenToTransmitter = false;
	for(list<int>::iterator it = moveTransmitters.begin();it != moveTransmitters.end();++it){
		if(e.id == *it){
			bListenToTransmitter = true;
			break;
		}
	}
	if(bListenToTransmitter){
		moveBy(e.dx,e.dy);
	}
}

void ofxListener::rotateEvent(ofxTangibleRotateEvent & e){
	bool bListenToTransmitter = false;
	for(list<int>::iterator it = rotateTransmitters.begin();it != rotateTransmitters.end();++it){
		if(e.id == *it){
			bListenToTransmitter = true;
			break;
		}
	}
	if(bListenToTransmitter){
		rotateBy(e.angle);
	}
}

void ofxListener::moveBy(float dx,float dy){
	if(bLocked)
		return;
	bLocked = true;

	x += dx;
	y += dy;

	moveListeners(dx * moveListenersSpeed.x,dy * moveListenersSpeed.y);

	float newAngle = (*this - rotateCenter).angle(base);
	if((*this - rotateCenter).angle(zeroBaseCheck) > 90.f){
		newAngle *= -1.f;
	}
	float angleDiff = newAngle - oldAngle;
	oldAngle = newAngle;

	rotateListeners(angleDiff);

	bLocked = false;
}

void ofxListener::rotateBy(float angle){
	if(bLocked)
		return;
	bLocked = true;

	ofVec3f vec = *this-rotateCenter;
	vec.rotate(0,0,angle);
	vec = rotateCenter + vec;
	x = vec.x;
	y = vec.y;

	rotateListeners(angle);

	updateOldAngle();

	bLocked = false;
}

void ofxListener::updateOldAngle(){
	oldAngle = (*this - rotateCenter).angle(base);
	if((*this - rotateCenter).angle(zeroBaseCheck) > 90.f){
		oldAngle *= -1.f;
	}
}



