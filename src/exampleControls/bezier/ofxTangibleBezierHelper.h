#ifndef OFXROTATETMP_H_
#define OFXROTATETMP_H_

#include "ofxTangibleHandle.h"

class ofxTangibleBezierHelper: public ofxTangibleHandle {
public:

	//default constructor and so an

	virtual void setup(float _x, float _y, float _w, float _h, float centerX = 0, float centerY = 0);

	virtual void moveInner(float dx, float dy);

	virtual void moveBy(float dx, float dy);
};

#endif /* OFXROTATETMP_H_ */
