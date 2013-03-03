/*
 * ofxTangibleBezierControl.h
 *
 *  Created on: Jun 24, 2012
 *      Author: spta32
 */

#ifndef OFXTANGIBLEBEZIERCONTROL_H_
#define OFXTANGIBLEBEZIERCONTROL_H_

#include "ofxTangibleHandle.h"
#include "ofxTangibleBezierHelper.h"

class ofxTangibleBezierControl : public ofxTangibleHandle{
public:
	ofxTangibleBezierHelper r1,r2;

	//default constructor and destrcutor

	//TODO copy and assignment constructor!!! important!!
	ofxTangibleBezierControl():
		ofxTangibleHandle(){};
	ofxTangibleBezierControl(const ofxTangibleBezierControl& other);

	virtual void setup(float _x,float _y, float _w, float _h);

	virtual void moveInternal(float dx, float dy);

	virtual void draw();
};

#endif /* OFXTANGIBLEBEZIERCONTROL_H_ */
