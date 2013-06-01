#include "ofxListener.h"

ofxListener::ofxListener() {
	bLocked = false;
	bListeningToMove = bListeningToRotate = false;
	bKeepSameDistance = false;
	moveListenersSpeed.set(1.f, 1.f);
	rotateCenter.set(0.f, 0.f);
	oldAngle = 0;
}

ofxListener::~ofxListener() {
	if (bListeningToMove) {
		moveTransmitters.clear();
		moveVerTransmitters.clear();
		moveHorTransmitters.clear();
		bListeningToMove = false;
		ofRemoveListener(ofxTangibleMoveEvent::events, this, &ofxListener::handleMoveEvent);
	}
	if (bListeningToRotate) {
		bListeningToRotate = false;
		ofRemoveListener(ofxTangibleRotateEvent::events, this, &ofxListener::handleRotateEvent);
	}
}

ofxListener::ofxListener(const ofxListener& other)
	:ofxTransmitter(other){
	copyInit(other);
	ofLog(OF_LOG_VERBOSE, "ofxListener COPY");
}

ofxListener& ofxListener::operator=(const ofxListener& other){
	ofxTransmitter::operator=(other);
	copyInit(other);
	return *this;
}

void ofxListener::copyInit(const ofxListener& other) {
	x = other.x;
	y = other.y;
	bLocked = other.bLocked;
	innerRotate = other.innerRotate;

	rotateCenter = other.rotateCenter;
	moveListenersSpeed = other.moveListenersSpeed;
	oldAngle = other.oldAngle;
	bKeepSameDistance = other.bKeepSameDistance;

	bListeningToMove = other.bListeningToMove;
	bListeningToRotate = other.bListeningToRotate;
	if (bListeningToMove) {
		ofAddListener(ofxTangibleMoveEvent::events, this, &ofxListener::handleMoveEvent);
		moveTransmitters = other.moveTransmitters;
		moveVerTransmitters = other.moveVerTransmitters;
		moveHorTransmitters = other.moveHorTransmitters;
	}
	if (bListeningToRotate) {
		ofAddListener(ofxTangibleRotateEvent::events, this, &ofxListener::handleRotateEvent);
		rotateTransmitters = other.rotateTransmitters;
	}
}

void ofxListener::setup(float _x, float _y) {
	x = _x;
	y = _y;

	updateOldAngle();
}

void ofxListener::setMoveListenersSpeed(float vx, float vy) {
	moveListenersSpeed.set(vx, vy);
}

void ofxListener::setMoveListenersSpeed(const ofVec2f & v) {
	setMoveListenersSpeed(v.x, v.y);
}

const ofVec2f& ofxListener::getMoveListenerSpeed() const {
	return moveListenersSpeed;
}

void ofxListener::setRotateCenter(const ofVec2f & rc) {
	setRotateCenter(rc.x, rc.y);
}

void ofxListener::setRotateCenter(float x, float y) {
	rotateCenter.x = x;
	rotateCenter.y = y;
	updateOldAngle();
}

void ofxListener::moveRotateCenter(const ofVec2f& diff, bool bUpdateAngle) {
	moveRotateCenter(diff.x, diff.y, bUpdateAngle);
}

void ofxListener::moveRotateCenter(float dx, float dy, bool bUpdateAngle) {
	rotateCenter.x += dx;
	rotateCenter.y += dy;
	if (bUpdateAngle) {
		updateOldAngle();
	}
}

const ofVec2f& ofxListener::getRotateCenter() const {
	return rotateCenter;
}

void ofxListener::setKeepSameDistance(bool sameDistance) {
	bKeepSameDistance = sameDistance;
}

void ofxListener::updateOldAngle() {
	ofVec3f vec = *this - rotateCenter;
	oldAngle = ofRadToDeg(atan2(vec.x,vec.y));
}

void ofxListener::startListeningTo(ofxTransmitter & transmitter, tangibleEventType type) {
	startListeningTo(transmitter.getId(), type);
}

void ofxListener::startListeningTo(ofxTransmitter * transmitter, tangibleEventType type) {
	startListeningTo(transmitter->getId(), type);
}

void ofxListener::startListeningTo(const int id, tangibleEventType type) {
	if (type == TANGIBLE_MOVE) {
		moveTransmitters.push_back(id);
		if (!moveTransmitters.empty() && !bListeningToMove) {
			bListeningToMove = true;
			ofAddListener(ofxTangibleMoveEvent::events, this, &ofxListener::handleMoveEvent);
		}
	} else if (type == TANGIBLE_MOVE_VERTICAL) {
		moveVerTransmitters.push_back(id);
		if ( !bListeningToMove) {
			bListeningToMove = true;
			ofAddListener(ofxTangibleMoveEvent::events, this, &ofxListener::handleMoveEvent);
		}
	} else if (type == TANGIBLE_MOVE_HORIZONTAL) {
		moveHorTransmitters.push_back(id);
		if ( !bListeningToMove) {
			bListeningToMove = true;
			ofAddListener(ofxTangibleMoveEvent::events, this, &ofxListener::handleMoveEvent);
		}
	}else if (type == TANGIBLE_ROTATE) {
		rotateTransmitters.push_back(id);
		if (!rotateTransmitters.empty() && !bListeningToRotate) {
			bListeningToRotate = true;
			ofAddListener(ofxTangibleRotateEvent::events, this, &ofxListener::handleRotateEvent);
		}
	}
}

void ofxListener::stopListeningTo(ofxTransmitter & transmitter, tangibleEventType type) {
	stopListeningTo(transmitter.getId(), type);
}

void ofxListener::stopListeningTo(ofxTransmitter * transmitter, tangibleEventType type) {
	stopListeningTo(transmitter->getId(), type);
}

void ofxListener::stopListeningTo(const int id, tangibleEventType type) {
	if (type == TANGIBLE_MOVE) {
		moveTransmitters.remove(id);
	} else 	if (type == TANGIBLE_MOVE_VERTICAL) {
		moveVerTransmitters.remove(id);
	} else  if (type == TANGIBLE_MOVE_HORIZONTAL) {
		moveHorTransmitters.remove(id);
	}else if (type == TANGIBLE_ROTATE) {
		rotateTransmitters.remove(id);
		if (rotateTransmitters.empty() && bListeningToRotate) {
			bListeningToRotate = false;
			ofRemoveListener(ofxTangibleRotateEvent::events, this, &ofxListener::handleRotateEvent);
		}
	}
	if (moveTransmitters.empty() && moveVerTransmitters.empty() && moveHorTransmitters.empty() && bListeningToMove) {
		bListeningToMove = false;
		ofRemoveListener(ofxTangibleMoveEvent::events, this, &ofxListener::handleMoveEvent);
	}
}

void ofxListener::listenToEachOther(ofxListener & l1,ofxListener & l2,tangibleEventType type){
	l1.startListeningTo(l2,type);
	l2.startListeningTo(l1,type);
}

void ofxListener::handleMoveEvent(ofxTangibleMoveEvent & e) {
	list<int>::iterator it = find(moveTransmitters.begin(),moveTransmitters.end(),e.id);
	if (it != moveTransmitters.end()) {
		moveExternal(e.dx, e.dy);
	}
	list<int>::iterator itV = find(moveVerTransmitters.begin(),moveVerTransmitters.end(),e.id);
	if (itV != moveVerTransmitters.end()) {
		moveExternal(0, e.dy);
	}
	list<int>::iterator itH = find(moveHorTransmitters.begin(),moveHorTransmitters.end(),e.id);
	if (itH != moveHorTransmitters.end()) {
		moveExternal(e.dx, 0);
	}
}

void ofxListener::handleRotateEvent(ofxTangibleRotateEvent & e) {
	int size = *rotateTransmitters.begin();
	list<int>::iterator it = find(rotateTransmitters.begin(),rotateTransmitters.end(),e.id);
	if (it != rotateTransmitters.end()) {
		rotateExternal(e.angle, e.distance);
	}
}

void ofxListener::moveExternal(float dx,float dy){
	moveBy(dx,dy);
}

void ofxListener::rotateExternal(float angle,float distance){
	rotateBy(angle,distance);
}

void ofxListener::moveBy(float dx, float dy) {
	if (bLocked)
		return;
	bLocked = true;

	//moveBy
	x += dx;
	y += dy;

	moveListeners(dx * moveListenersSpeed.x, dy * moveListenersSpeed.y);

	//rotateBy
	ofVec3f vec = *this - rotateCenter;
	float newAngle = ofRadToDeg(atan2(vec.x,vec.y));

	float angleDiff = newAngle - oldAngle;
	oldAngle = newAngle;
	if(abs(angleDiff) > 0.0001)
		rotateListeners(-angleDiff, this->distance(rotateCenter));

	bLocked = false;
}

void ofxListener::rotateBy(float angle, float distance) {
	if (bLocked)
		return;
	bLocked = true;

	ofVec3f vec = *this - rotateCenter;
	vec.rotate(0, 0, angle);

	if (bKeepSameDistance && distance > 0.f) {
		vec.normalize();
		vec.scale(distance);
	}

	vec = rotateCenter + vec;
	x = vec.x;
	y = vec.y;

	rotateListeners(angle, distance);
	oldAngle += angle;

	rotateInner(angle); //REVISIT perhaps use a boolean to control whether rotateInner should get called or not

	bLocked = false;
}

void ofxListener::rotateInner(float degree){
	innerRotate += degree;
//	rotateListeners(degree,0); //override it like this, if you want to listen to inner rotation
}
