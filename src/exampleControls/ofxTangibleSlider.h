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

class ofxTangibleMarker : public ofxTangibleHandle{
public:
	ofxRange range;

	virtual void setup(float x,float y, float w, float h){
		ofxTangibleHandle::setup(x,y+h/2.f,w,h/5);
		range.setup(x,y-h/2.f);
		range.range = h;
	}

	virtual void moveInternal(float dx,float dy){
		ofxTangibleHandle::moveInternal(0,dy);
		y = y < range.getMin() ? range.getMin() : y;
		y = y > range.getMax() ? range.getMax() : y;
	}

	virtual void draw(){
		ofSetColor(255);
		range.draw();
		ofxTangibleHandle::draw();
	}
};

class ofxTangibleSlider : public ofxTangibleHandle{
public:
	virtual void setup(float x, float y, float w, float h){
		ofxTangibleHandle::setup(x,y,w,h);
		slider.setup(x,y,w*0.8,h*0.8);
		slider.range.startListeningTo(this);
		slider.startListeningTo(this);
	}

	virtual void draw(){
		ofxTangibleHandle::draw();
		slider.draw();
	}

	virtual void moveInternal(float dx, float dy){
		if(slider.isPressed())
			return;

		moveRotateCenter(dx,dy);
		ofxTangibleCore::moveInternal(dx,dy);
	}

	virtual bool isHovered(){
		return bHovered && !slider.isHovered();
	}
protected:
	ofxTangibleMarker slider;
};

#endif /* OFXPOSANDSCALE_H_ */
