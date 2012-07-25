/*
 * ofxTransmitter.cpp
 */

#include "ofxTransmitter.h"

int ofxTransmitter::generatedId = 0;
ofEvent <ofxTangibleMoveEvent> ofxTangibleMoveEvent::events;

ofxTransmitter::ofxTransmitter()
	:id(generateId())
{

}

ofxTransmitter::~ofxTransmitter() {
	// TODO Auto-generated destructor stub
}

void ofxTransmitter::moveListeners(float dx, float dy) {

	//send ofEvent
	ofxTangibleMoveEvent moveEvent;
	moveEvent.id = getId();
	moveEvent.dx = dx;
	moveEvent.dy = dy;

	ofNotifyEvent(ofxTangibleMoveEvent::events,moveEvent);
}

