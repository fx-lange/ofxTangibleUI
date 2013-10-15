#pragma once

#include "ofMain.h"
#include "ofxTangibleHandle.h"

class ofxPositioningContainer {

public:

	void enablePositioning();
	void disablePositioning();
	void push_back(ofxTangibleCore * obj);

protected:

	vector<ofxTangibleHandle> mover;
	vector<ofxTangibleCore *> objects;
};
