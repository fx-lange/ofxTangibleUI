/*
 * ofxTangiblePolyline.h
 *
 *  Created on: May 7, 2012
 *      Author: spta
 */


#ifndef OFXTANGIBLEPOLYLINE_H_
#define OFXTANGIBLEPOLYLINE_H_

#include "ofMain.h"
#include "ofxHandle.h"

class ofxTangiblePolyline : public ofPolyline {
public:
	ofxTangiblePolyline();
	virtual ~ofxTangiblePolyline();

	void addVertex(ofPoint & p){
		addVertex(p.x,p.y);
	}

	void addVertex(float x,float y){
		ofxHandle h;
		h.setup(x,y,10,10);
		points.push_back(h);
	}

	virtual void draw(){
		ofPolyline::draw();

		for(int i=0;i<points.size();++i){
			//not possible
		}
	}

//private:
//	vector<ofxHandle> points;
};

#endif /* OFXTANGIBLEPOLYLINE_H_ */
