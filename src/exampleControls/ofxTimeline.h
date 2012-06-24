/*
 * ofxTimeLine.h
 *
 *  Created on: Jun 4, 2012
 *      Author: spta
 */

#ifndef OFXTIMELINE_H_
#define OFXTIMELINE_H_

#include "ofMain.h"
#include "ofxTangibleHandle.h"
#include "ofxDropZone.h"

class ofxTimeline : public ofxTangibleYFixedHandle {
public:
	virtual void setup(float x,float y,float w,float h,int range = 300);

	virtual void draw();
protected:
	ofxDropZone dropZone;
	float lineHeight;
	float lineCount;
	int timerange;
};

#endif /* OFXTIMELINE_H_ */
