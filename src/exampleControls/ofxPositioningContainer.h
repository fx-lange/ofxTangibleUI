#pragma once

#include "ofMain.h"
#include "ofxTangibleHandle.h"

class ofxPositioningContainer {

public:

	ofxPositioningContainer();

	void enablePositioning();
	void disablePositioning();
	void togglePositioning();

	void push_back(ofxTangibleCore * obj);

protected:

	vector<ofxTangibleHandle> mover;
	vector<ofxTangibleCore *> objects;

	bool bPositioningActive;
};
