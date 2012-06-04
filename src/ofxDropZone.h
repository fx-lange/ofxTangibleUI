#ifndef OFXDROPZONE_H_
#define OFXDROPZONE_H_

#include "ofxListener.h"

class ofxDropZone : public ofxListener {
public:
	float width, height;

	virtual void set(float x,float y,float w,float h){
		setup(x,y,w,h);
	}

	virtual void setup(float x,float y,float w,float h);

	operator ofRectangle & ();

	ofRectangle operator=(ofRectangle _rect);

protected:
	ofRectangle internalRect;

};

#endif /* OFXDROPZONE_H_ */
