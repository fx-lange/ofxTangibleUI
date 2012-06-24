/*
 * ofxRotateTmp.h
 *
 *  Created on: Jun 23, 2012
 *      Author: spta32
 */

#ifndef OFXROTATETMP_H_
#define OFXROTATETMP_H_

#include "ofxTangibleHandle.h"

class ofxTangibleBezierHelper : public ofxTangibleHandle{
public:



	ofxTangibleBezierHelper();
	virtual ~ofxTangibleBezierHelper();

	virtual void setup(float _x,float _y, float _w, float _h, float centerX = 0, float centerY = 0){
		ofxTangibleHandle::setup(_x,_y,_w,_h);

		rotateCenter.set(centerX,centerY);
		updateOldAngle();
	}

	virtual void moveInner(float dx, float dy){
		ofxTangibleHandle::moveBy(dx,dy);
	}

	virtual void moveBy(float dx, float dy){
		rotateCenter.x += dx;
		rotateCenter.y += dy;

		ofxTangibleHandle::moveBy(dx,dy);
	}
};

#endif /* OFXROTATETMP_H_ */
