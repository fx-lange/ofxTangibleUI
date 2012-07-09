#ifndef OFXTANGIBLEBEZIER_H_
#define OFXTANGIBLEBEZIER_H_

#include "ofMain.h"
#include "ofxTangibleBezierControl.h"

class ofxTangibleBezier : public ofxTangibleCore{
public:

	vector<ofxTangibleBezierControl> controls;
	ofPolyline line;
	bool bPressed;
	bool bGrabbingEnabled;

	ofxTangibleBezier();
	virtual ~ofxTangibleBezier();

	virtual void setup(){
		ofxTangibleCore::setup(0,0,0,0);
		registerMouse();
		bPressed = false;
		controls.reserve(100);
	}

	virtual void mousePressed(ofMouseEventArgs &e){
		if(bPressed || !bGrabbingEnabled){
			return;
		}
		bPressed = true;

		if(controls.size()!=0){
			return;
		}

		pX = e.x;
		pY = e.y;

		ofxTangibleBezierControl control;
		controls.push_back(control);
		controls.back().setup(e.x,e.y,10,10);
	}

	virtual void mouseMoved(ofMouseEventArgs &e){
		if(controls.size()==0 || bPressed || !bGrabbingEnabled){
			return;
		}
		controls.back().moveBy(e.x-pX,e.y-pY);
		pX = e.x;
		pY = e.y;
	}

	virtual void mouseDragged(ofMouseEventArgs &e){
		pX = e.x;
		pY = e.y;
	}

	virtual void mouseReleased(ofMouseEventArgs &e){
		bPressed = false;
		if(!bGrabbingEnabled){
			return;
		}

		controls.back().enableGrabbing();
		controls.back().r2.enableGrabbing();

		ofxTangibleBezierControl control;
		controls.push_back(control);
		controls.back().setup(e.x,e.y,10,10);
	}

	virtual void draw(){
		if(controls.size()==0)
			return;
		line.clear();
		line.addVertex(controls[0]);
		controls[0].draw();
		for(int i=1;i<controls.size();++i){
			line.bezierTo(controls[i-1].r2,controls[i].r1,controls[i]);
			controls[i].draw();
		}
		line.draw();
	}

};

#endif /* OFXTANGIBLEBEZIER_H_ */
