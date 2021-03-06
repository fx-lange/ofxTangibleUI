#pragma once

#include "ofMain.h"
#include "ofxTangibleHandle.h"
#include "ofxTangibleToggle.h"
#include "ofxTangibleButton.h"
#include "ofxTangiblePolyline.h"
#include "ofxTimeline.h"
#include "ofxTangibleSlider.h"
#include "ofxTangibleBezier.h"
#include "ofxTangibleImage.h"
#include "ofxTangibleValue.h"
#include "ofxRotaryKnob.h"

class tangibleUiExample : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		void toggleHasChanged(bool & active);
		void buttonHasChanged(bool & active);

		ofxTangibleXFixedHandle xfixed;
		ofxTangibleHandle handle;
		ofxTangibleYFixedHandle yfixed;
		vector<ofxTangibleHandle> handles;
		ofxTangibleYFixedHandle xSpeed3;

		ofxTangibleToggle toggle;
		ofxTangibleButton button;

		ofxTimeline timeline;
		ofxTangibleSlider pAndS;
		ofxTangibleBezierHelper r1,r2,r3;
		vector<ofxTangibleBezierHelper> helpers;
		ofxTangibleImage imageHandle;
		ofxTangibleValue tangibleValue;
		ofxRotaryKnob knob;
};
