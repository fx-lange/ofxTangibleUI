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
	//TODO copy constructor!!! important!!

	virtual void setup(float _x,float _y, float _w, float _h){
		ofxTangibleHandle::setup(_x,_y,_w,_h);
		drawType = TANGIBLE_DRAW_AS_CENTER_RECT;
		r1.setup(x+1,y,width,height,x,y);
		r2.setup(x-15,y,width,height,x,y);
		r1.drawType = r2.drawType = TANGIBLE_DRAW_AS_CIRCLE;

		r1.startListeningTo(this,TANGIBLE_MOVE);
		r2.startListeningTo(this,TANGIBLE_MOVE);

		r1.startListeningTo(r2,TANGIBLE_ROTATE);
		r2.startListeningTo(r1,TANGIBLE_ROTATE);

		r2.disableGrabbing();
		disableGrabbing();
	}

	virtual void draw(){
		ofPushStyle();
		ofSetColor(color,100);
		ofxTangibleHandle::draw();
		ofLine(r1,r2);
		r1.draw();
		r2.draw();
		ofPopStyle();
	}
};

#endif /* OFXTANGIBLEBEZIERCONTROL_H_ */
