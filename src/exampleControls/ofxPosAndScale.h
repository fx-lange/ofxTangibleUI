#ifndef OFXPOSANDSCALE_H_
#define OFXPOSANDSCALE_H_

#include "ofxTangibleHandle.h"

class ofxRange : public ofxListener{
public:
	float range;

	virtual void draw(){
		ofLine(x,y,x,y+range);
	}

	float getMin(){
		return y;
	}

	float getMax(){
		return y+range;
	}

	//TODO getter setter
};

class ofxTangibleSlider : public ofxTangibleHandle{
public:
	ofxRange range;

	virtual void setup(float x,float y, float w, float h){
		ofxTangibleHandle::setup(x,y+h/2,w/3,h/10);
		range.x = x;
		range.y = y;
		range.range = h;
	}

	virtual void moveInner(float dx,float dy){
		moveBy(0,dy);
		y = y < range.getMin() ? range.getMin() : y;
		y = y > range.getMax() ? range.getMax() : y;
	}
};

class ofxPosAndScale : public ofxListener{
public:
	virtual void setup(float x, float y, float w, float h){
		handle.setup(x,y,w,h);
		slider.setup(x+w+5,y,w,h);
		handle.addListener(&(slider.range));
		handle.addListener(&slider);

	}

	virtual void draw(){
		handle.draw();
		slider.draw();
		ofSetColor(255);
		slider.range.draw();
	}
protected:
	ofxTangibleHandle handle;
	ofxTangibleSlider slider;
};

#endif /* OFXPOSANDSCALE_H_ */
