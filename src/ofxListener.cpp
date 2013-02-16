/*
 * ofxListener.cpp
 */

#include "ofxListener.h"

ofxListener::ofxListener() :
		base(0, -1), zeroBaseCheck(1, 0) {
	bLocked = false;
	bListeningToMove = bListeningToRotate = false;
	bKeepSameDistance = false;
	moveListenersSpeed.set(1.f, 1.f);
	rotateCenter.set(0.f, 0.f); //TODO should be init as center?
	oldAngle = 0;
}

ofxListener::~ofxListener() {
	if (bListeningToMove) {
		moveTransmitters.clear();
		bListeningToMove = false;
		ofRemoveListener(ofxTangibleMoveEvent::events, this, &ofxListener::moveEvent);
	}
	if (bListeningToRotate) {
		bListeningToRotate = false;
		ofRemoveListener(ofxTangibleRotateEvent::events, this, &ofxListener::rotateEvent);
	}
}

ofxListener::ofxListener(const ofxListener& other) :
		ofxTransmitter(other), base(0, -1), zeroBaseCheck(1, 0) {
	init(other);
	ofLog(OF_LOG_VERBOSE, "ofxListener COPY");
}

ofxListener& ofxListener::operator=(const ofxListener& other) {
	init(other);
	return *this;
}

void ofxListener::init(const ofxListener& other) {
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
		ofAddListener(ofxTangibleMoveEvent::events, this, &ofxListener::moveEvent);
		moveTransmitters = other.moveTransmitters;
	}
	if (bListeningToRotate) {
		ofAddListener(ofxTangibleRotateEvent::events, this, &ofxListener::rotateEvent);
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
	oldAngle = (*this - rotateCenter).angle(base);
	if ((*this - rotateCenter).angle(zeroBaseCheck) > 90.f) {
		oldAngle *= -1.f;
	}
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
			ofAddListener(ofxTangibleMoveEvent::events, this, &ofxListener::moveEvent);
		}
	} else if (type == TANGIBLE_ROTATE) {
		rotateTransmitters.push_back(id);
		if (!rotateTransmitters.empty() && !bListeningToRotate) {
			bListeningToRotate = true;
			ofAddListener(ofxTangibleRotateEvent::events, this, &ofxListener::rotateEvent);
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
		if (moveTransmitters.empty() && bListeningToMove) {
			bListeningToMove = false;
			ofRemoveListener(ofxTangibleMoveEvent::events, this, &ofxListener::moveEvent);
		}
	} else if (type == TANGIBLE_ROTATE) {
		rotateTransmitters.remove(id);
		if (rotateTransmitters.empty() && bListeningToRotate) {
			bListeningToRotate = false;
			ofRemoveListener(ofxTangibleRotateEvent::events, this, &ofxListener::rotateEvent);
		}
	}
}

void ofxListener::moveEvent(ofxTangibleMoveEvent & e) {
	list<int>::iterator it = find(moveTransmitters.begin(),moveTransmitters.end(),e.id);
	if (it != moveTransmitters.end()) {
		moveBy(e.dx, e.dy);
	}
}

void ofxListener::rotateEvent(ofxTangibleRotateEvent & e) {
	list<int>::iterator it = find(rotateTransmitters.begin(),rotateTransmitters.end(),e.id);
	if (it != rotateTransmitters.end()) {
		rotateBy(e.angle, e.distance);
	}
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
	float newAngle = (*this - rotateCenter).angle(base);
	if ((*this - rotateCenter).angle(zeroBaseCheck) > 90.f) {
		newAngle *= -1.f;
	}
	float angleDiff = newAngle - oldAngle;
	oldAngle = newAngle;
	rotateListeners(angleDiff, this->distance(rotateCenter));

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
	updateOldAngle();

//	rotateInner(angle);
	innerRotate += angle;

	bLocked = false;
}

void ofxListener::rotateInner(float degree){
	innerRotate += degree;
}

