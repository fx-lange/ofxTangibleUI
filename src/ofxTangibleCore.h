/*
 * ofxTangibleCore.h
 *
 *  Created on: May 3, 2012
 *      Author: spta
 */

#ifndef OFXTANGIBLECORE_H_
#define OFXTANGIBLECORE_H_

class ofxTangibleCore: public ofxListener {
public:
	float width, height;

	ofxTangibleCore(float _x, float _y, float _width, float _height);
	virtual ~ofxTangibleCore();

	//TODO copyconstructor and destrcutor - see ofxGrabbablePolyLine
	virtual void registerMouse();
	virtual void unregisterMouse();

	virtual void mousePressed(ofMouseEventArgs &e) = 0; //REVISIT perhaps use wrapper functions like in simpleguitoo
	virtual void mouseDragged(ofMouseEventArgs &e) = 0;
	virtual void mouseReleased(ofMouseEventArgs &e) = 0;

protected:
	float pX, pY;

	virtual bool isOver(float px, float py);
};

#endif OFXTANGIBLECORE_H_
