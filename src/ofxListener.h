/*
 * ofxListener.h
 *
 *  Created on: May 3, 2012
 *      Author: spta
 */

#ifndef OFXLISTENER_H_
#define OFXLISTENER_H_

#include "ofMain.h"


class ofxListener : public ofPoint{
public:

	//REVISIT public vs protected
//	void moveTo(float x, float y);
	void moveBy(float dx, float dy);

protected:
	void moveListener(float dx, float dy);

	std::list<ofxListener*> listeners;
};


#endif OFXLISTENER_H_
