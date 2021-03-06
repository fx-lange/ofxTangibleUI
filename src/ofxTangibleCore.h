#ifndef OFXTANGIBLECORE_H_
#define OFXTANGIBLECORE_H_

#include "ofxListener.h"

class ofxXmlSettings;

/*TODO
 * save and load to and from xml
 */

enum tangibleDrawType{
	TANGIBLE_DRAW_AS_CIRCLE, //draw object as a circle (not as an ellipse) -> width = diameter, height is ignored
	TANGIBLE_DRAW_AS_CENTERED_RECT //draw object as a rectangle using OF_RECTMODE_CENTER (centered at x,y)
};

/* ofxTangibleCore
 * tangible interactive base class (by default via mouse or touch)
 * also movable by listening (ofxListener)
 */
class ofxTangibleCore: public ofxListener {
public:
	float width, height;
	tangibleDrawType drawType; //draw as circle or centered rectangle, also affects the hit test isOver(x,y)

	static bool bScaleTouchEvent;
	bool bDrawDebug;

	ofxTangibleCore();
	virtual ~ofxTangibleCore();

	ofxTangibleCore(const ofxTangibleCore& other);
	ofxTangibleCore& operator=(const ofxTangibleCore& other);

	virtual void setup(const ofRectangle & rect){
		setup(rect.x,rect.y,rect.width,rect.height);
	}
	virtual void setup(const ofPoint &center,float w, float h){
		setup(center.x,center.y,w,h);
	}
	virtual void setup(float _x,float _y, float _w, float _h);

	virtual void setColor(const ofColor & color);
	virtual ofColor & getColor();
	virtual void setHoverColor(const ofColor & color);
	virtual ofColor & getHoverColor();

	//mouse interaction
	virtual void registerMouse();
	virtual void unregisterMouse();
	virtual void mouseMoved(ofMouseEventArgs &e){}
	virtual void mousePressed(ofMouseEventArgs &e){}
	virtual void mouseDragged(ofMouseEventArgs &e){}
	virtual void mouseReleased(ofMouseEventArgs &e){}

	//touch interaction
	virtual void registerTouch();
	virtual void unregisterTouch();
	virtual void touchDoubleTap(ofTouchEventArgs &e){}
	virtual void touchDown(ofTouchEventArgs &e){}
	virtual void touchMoved(ofTouchEventArgs &e){}
	virtual void touchUp(ofTouchEventArgs &e){}
	virtual void touchCancelled(ofTouchEventArgs &e){}

	/* draw method which centers the coordinate system at x,y and rotates by innerRotate
	 * before calling drawInner()
	 * for styling your subclass you should override drawInner() not draw() */
	virtual void draw();

	virtual void saveToXml(ofxXmlSettings & xml);
	virtual void loadFromXml(ofxXmlSettings & xml);

	virtual bool isPressed(){
		return bPressed || bPressedByTouch;
	}
	virtual bool isHovered(){
		return bHovered;
	}
protected:
	ofPoint pastPos;
	int touchId;
	bool bPressed; 			//pressed by mouse
	bool bPressedByTouch;	//pressed by touch
	bool bHovered;

	ofColor color, hoverColor;

	//hit test
	//REVISIT needed as public?!
	virtual bool isOver(float px, float py);

	/* method to move the object only called internal by mouse or touch interaction methods
	 * forwards movement direction to moveBy(dx,dy) by default
	 * encapsulated for the case that the behavior should differ depending on whether
	 * 		movement is called from inside(moveInternal->moveBy) or outside (moveEvent->moveBy)*/
	virtual void moveInternal(float dx, float dy);

	/* is called by draw()
	 * coordinate system is centered at x,y and rotated by innerRotate
	 * you should override this function to style your own class */
	virtual void drawInner();

	//for debugging, once you start designing your own classes - called by draw() same as drawInner()
	virtual void drawDebug();
private:
	bool bMouseRegistered, bTouchRegistered;
	void init(const ofxTangibleCore& other);
};

#endif /* OFXTANGIBLECORE_H_*/
