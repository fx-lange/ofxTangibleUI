#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "ofxTuioClient.h"

#include "ofxTangibleHandle.h"
#include "ofxTangibleToggle.h"
#include "ofxTangibleButton.h"
#include "ofxTangibleBezierHelper.h"

class ofxTangibleMoon : public ofxTangibleHandle{
public:
	//default constructor and so an

	virtual void setup(float _x, float _y, float _w, float _h, float centerX, float centerY) {
		ofxTangibleHandle::setup(_x, _y, _w, _h);
		setRotateCenter(centerX,centerY);
	}

virtual void moveExternal(float dx, float dy){
		//we assume, that the method is only called from the base's movement
		//therefore the rotationCenter must also be moved
		moveRotateCenter(dx,dy);
		ofxTangibleHandle::moveExternal(dx, dy);
	}
};

class ofxFixedDistanceMoon : public ofxTangibleMoon{
public:
	//keep the distance to the rotationCenter
	virtual void moveInternal(float dx, float dy){
		float distance = this->distance(getRotateCenter());
		ofxTangibleHandle::moveBy(dx, dy);
		ofVec3f vec = *this - getRotateCenter();

		vec.normalize();
		vec.scale(distance);

		vec = getRotateCenter() + vec;
		x = vec.x;
		y = vec.y;
	}
};

class ofxTangibleBase : public ofxTangibleHandle{

public:
	vector<ofxTangibleCore*> buttons;
	virtual void setup(float x,float y,float w,float h){
		ofxTangibleHandle::setup(x,y,w,h);

		setupChilds();
	}

	virtual void setupChilds(){
		child.setup(x+20,y+20,30,30,x,y);
		child.drawType = TANGIBLE_DRAW_AS_CIRCLE;
		addControls(child);

		fixedMoon.setup(x-width/2,y,30,30,x,y);
		fixedMoon.drawType = TANGIBLE_DRAW_AS_CENTERED_RECT;
		addControls(fixedMoon);
	}

	virtual void addControls(ofxTangibleCore & control){
		buttons.push_back(&control);

		control.startListeningTo(this,TANGIBLE_MOVE);
		control.startListeningTo(this,TANGIBLE_ROTATE);
	}

	virtual void moveInternal(float dx, float dy){
		for(int i=0;i<(int)buttons.size();++i){
			if(buttons[i]->isPressed()){
				return;
			}
		}
		moveRotateCenter(dx,dy);
		ofxTangibleCore::moveInternal(dx,dy);
	}

	virtual void rotateInner(float degree){
		for(int i=0;i<(int)buttons.size();++i){
			if(buttons[i]->isPressed()){
				return;
			}
		}
		ofxTangibleHandle::rotateInner(degree);
		rotateListeners(degree, 0);
	}

	virtual void draw(){
		ofxTangibleHandle::draw();
		for(int i=0;i<(int)buttons.size();++i){
			buttons[i]->draw();
		}
	}

	ofxTangibleMoon child;
	ofxFixedDistanceMoon fixedMoon;
};

class tuioExample : public ofBaseApp{
	
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
	
	ofxTuioClient myTuio;
	
	void touchDown(ofTouchEventArgs & touch);
	void touchUp(ofTouchEventArgs & touch);
	void touchMoved(ofTouchEventArgs & touch);
	
};

#endif
