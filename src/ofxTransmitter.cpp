/*
 * ofxTransmitter.cpp
 */

#include "ofxTransmitter.h"

int ofxTransmitter::generatedId = 0;
ofEvent <ofxTangibleMoveEvent> ofxTangibleMoveEvent::events;
ofEvent <ofxTangibleRotateEvent> ofxTangibleRotateEvent::events;

ofxTransmitter::ofxTransmitter()
	:id(generateId()) {}

ofxTransmitter::ofxTransmitter(const ofxTransmitter & other){
	id = other.id;
}

ofxTransmitter& ofxTransmitter::operator=(const ofxTransmitter& other){
	id = other.id;
	return *this;
}

void ofxTransmitter::moveListeners(float dx, float dy) {
	//send ofEvent
	ofxTangibleMoveEvent moveEvent;
	moveEvent.id = getId();
	moveEvent.dx = dx;
	moveEvent.dy = dy;

	ofNotifyEvent(ofxTangibleMoveEvent::events,moveEvent);
}

void ofxTransmitter::rotateListeners(float angle, float distance) {
	//send ofEvent
	ofxTangibleRotateEvent rotateEvent;
	rotateEvent.id = getId();
	rotateEvent.angle = angle;
	rotateEvent.distance = distance;

	ofNotifyEvent(ofxTangibleRotateEvent::events,rotateEvent);
}

