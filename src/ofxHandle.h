/*
 * ofxHandle.h
 *
 *  Created on: May 3, 2012
 *      Author: spta
 */

#ifndef OFXHANDLE_H_
#define OFXHANDLE_H_

class ofxHandle : public ofxTangibleCore{
public:
	ofColor color;
	bool fillMe;

	void enableGrabbing() {
		setGrabbing(true);
	}

	void disableGrabbing() {
		setGrabbing(false);
	}

	virtual void setGrabbing(bool bGrabbing){
		bGrabbingEnabled = bGrabbing;
	}

	void toggleGrabbing(){
		setGrabbing(!bGrabbingEnabled);
	}



protected:
	float pX, pY;
	bool bGrabbingEnabled;
	bool bPressed;
};

#endif /* OFXHANDLE_H_ */
