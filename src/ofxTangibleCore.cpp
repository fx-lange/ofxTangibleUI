#include "ofxTangibleCore.h"
#include "ofxXmlSettings.h"

bool ofxTangibleCore::bScaleTouchEvent = true;

ofxTangibleCore::ofxTangibleCore(){
	bMouseRegistered = false;
	bTouchRegistered = false;
	drawType = TANGIBLE_DRAW_AS_CENTERED_RECT;
	touchId = -1;
	innerRotate = 0.f;
	bPressed = false;
	bPressedByTouch = false;
	bDrawDebug = false;
}

ofxTangibleCore::~ofxTangibleCore() {
	unregisterMouse();
	unregisterTouch();
}

ofxTangibleCore::ofxTangibleCore(const ofxTangibleCore& other)
	:ofxListener(other)
	//isn't this default behaviour? no it's not!!
	//non default copy constructors construct the base via the default constructor
	//not via the copy constructor like default copy constructors do.
{
	init(other);
	//REVISIT call init before body is not possible so this is not the best solution
	//because members get initalized twice!!!

	ofLog(OF_LOG_VERBOSE,"ofxTangibleCore COPY");
}

ofxTangibleCore& ofxTangibleCore::operator= (const ofxTangibleCore& other){
	ofxListener::operator=(other);
	init(other);
	return *this;
}

void ofxTangibleCore::init(const ofxTangibleCore& other){
	drawType = other.drawType;
	touchId = other.touchId;
	width = other.width;
	height = other.height;
	bPressed = other.bPressed;
	bPressedByTouch = other.bPressedByTouch;
	bScaleTouchEvent = other.bScaleTouchEvent;
	color = other.color;

	pX = other.pX;
	pY = other.pY;

	/* very tricky ... took me long time to debug
	 * because of (random) default initialization of bMouseRegistered
	 * registerMouse() wasn't working in about 50%
	 */
	bMouseRegistered = false;
	if(other.bMouseRegistered){
		registerMouse();
	}

	bTouchRegistered = false;
	if(other.bTouchRegistered){
		registerTouch();
	}
}

void ofxTangibleCore::setup(float _x,float _y, float _w, float _h){
	ofxListener::setup(_x,_y);
	width = _w;
	height = _h;

	setRotateCenter(x,y);
}

bool ofxTangibleCore::isOver(float px, float py) {
	if(drawType == TANGIBLE_DRAW_AS_CIRCLE){
//		if( fabs(px-x)<width/2.f && fabs(py-y)<width/2.f){ //TODO seems to be a bug here
		if( this->distance(ofVec3f(px,py)) < width/2.f){
			return true;
		}else{
			return false;
		}
	}else{
		ofVec2f mouse(px-x,py-y);

		mouse.rotate(-innerRotate);

		if ( fabs(mouse.x)<width/2.f && fabs(mouse.y)<height/2.f ){
			return true;
		}else {
			return false;
		}
	}
}

void ofxTangibleCore::moveInternal(float dx, float dy) {
	moveBy(dx, dy);
}

void ofxTangibleCore::draw() {
	ofPushStyle();
	ofPushMatrix();

	if (drawType == TANGIBLE_DRAW_AS_CENTERED_RECT) {
		ofTranslate(x,y);
		ofRotate(innerRotate);
		ofSetRectMode(OF_RECTMODE_CENTER);
	} else {
		ofTranslate(x,y);
		ofRotate(innerRotate);
	}

	drawInner();
	if(bDrawDebug){
		drawDebug();
	}

	ofPopMatrix();
	ofPopStyle();
}

void ofxTangibleCore::drawInner(){
	ofPushStyle();
	ofSetColor(color);
	if(drawType == TANGIBLE_DRAW_AS_CENTERED_RECT){
		ofRect(0,0,width,height);
	}else{
		ofCircle(0,0,width/2.f); //radius = width, ignore height
	}
	ofPopStyle();
}

void ofxTangibleCore::drawDebug(){
	ofPushStyle();
	ofNoFill();
	ofSetColor(color);
	if(drawType == TANGIBLE_DRAW_AS_CENTERED_RECT){
		ofRect(0,0,width,height);
	}else{
		ofEllipse(0,0,width,height);
	}
	ofPopStyle();
}

void ofxTangibleCore::registerMouse() {
	if(bMouseRegistered){
		ofLog(OF_LOG_VERBOSE,"mouse already registered");
		return;
	}
	ofRegisterMouseEvents(this);
	bMouseRegistered = true;
}

void ofxTangibleCore::unregisterMouse(){
	if(!bMouseRegistered)
		return;
	ofUnregisterMouseEvents(this);
	bMouseRegistered = false;
}

void ofxTangibleCore::registerTouch() {
	if(bTouchRegistered)
		return;
	ofRegisterTouchEvents(this);
	bTouchRegistered = true;
}

void ofxTangibleCore::unregisterTouch(){
	if(!bTouchRegistered)
		return;
	ofUnregisterTouchEvents(this);
	bTouchRegistered = false;
}

void ofxTangibleCore::saveToXml(ofxXmlSettings & xml){
	xml.setValue("x",x);
	xml.setValue("y",y);
	xml.setValue("width",width);
	xml.setValue("height",height);
}

void ofxTangibleCore::loadFromXml(ofxXmlSettings & xml){
	float x = xml.getValue("x",0);
	float y = xml.getValue("y",0);
	float w = xml.getValue("width",20);
	float h = xml.getValue("height",20);
	setup(x,y,w,h);
}

