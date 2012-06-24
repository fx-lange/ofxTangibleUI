/*
 * ofxTangiblePolyline.h
 *
 *  Created on: May 7, 2012
 *      Author: spta
 */


#ifndef OFXTANGIBLEPOLYLINE_H_
#define OFXTANGIBLEPOLYLINE_H_

#include "ofMain.h"
#include "ofxTangibleHandle.h"

/**
 * its not possible to extend ofPolyline the way I want :(
 * but to use polylines intern and add wrapper functions should work
 */

class ofxTangiblePolyline {
public:
	ofxTangiblePolyline();
	virtual ~ofxTangiblePolyline();

};

#endif /* OFXTANGIBLEPOLYLINE_H_ */
