#ifndef OFXTANGIBLEIMAGE_H_
#define OFXTANGIBLEIMAGE_H_

#include "ofxTangibleHandle.h"

class ofxTangibleImage : public ofxTangibleHandle{
public:
	virtual void setup(float x, float y,string imageName, float w = 0, float h = 0);
	virtual void drawInner();
protected:
	ofImage image;
};

#endif /* OFXTANGIBLEIMAGE_H_ */
