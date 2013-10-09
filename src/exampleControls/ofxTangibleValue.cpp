#include "ofxTangibleValue.h"

ofxTangibleValue::ofxTangibleValue()
	:ofxTangibleHandle(){
	bUpdateValueAfterRelease = false;
	value = 0;
	tmpValue = 0;
	calcValueMode = TANGIBLE_VALUE_MODE_BOTH;
}

float ofxTangibleValue::getValue(){
	if(bUpdateValueAfterRelease){
		return value;
	}else{
		return value+tmpValue;
	}
}

void ofxTangibleValue::calcValueByPos(const ofVec2f & first,const ofVec2f & now){
	switch(calcValueMode){
	case TANGIBLE_VALUE_MODE_VERTICAL:
		tmpValue = ( now.x - first.x );
		break;
	case TANGIBLE_VALUE_MODE_HORIZONTAL:
		tmpValue = -1 * ( now.y - first.y );
		break;
	case TANGIBLE_VALUE_MODE_BOTH:
		tmpValue = ( now.x - first.x ) - ( now.y - first.y );
		break;
	}
//	if(!bUpdateValueAfterRelease){
//		value += tmpValue;
//	}
}

void ofxTangibleValue::toggleUpdateAfterRelease(){
	bUpdateValueAfterRelease = !bUpdateValueAfterRelease;
}

void ofxTangibleValue::mousePressed(ofMouseEventArgs &e) {
	if (!bGrabbingEnabled || !isOver(e.x, e.y))
		return;
	pX = e.x;
	pY = e.y;

	bPressed = true;

}

void ofxTangibleValue::mouseDragged(ofMouseEventArgs &e) {
	if (!bGrabbingEnabled || !bPressed)
		return;

	calcValueByPos(ofPoint(pX,pY),e);
}

void ofxTangibleValue::mouseReleased(ofMouseEventArgs &e) {
	if (!bPressed)
		return;

	value += tmpValue;
	tmpValue = 0;
	bPressed = false;
}

void ofxTangibleValue::touchDown(ofTouchEventArgs &e) {
	if(!bGrabbingEnabled || bPressedByTouch)
		return;

	float touchX = e.x;
	float touchY = e.y;

	if(bScaleTouchEvent){
		touchX *= ofGetWidth();
		touchY *= ofGetHeight();
	}

	if (!isOver(touchX, touchY))
		return;

	touchs.push_back(e);
	touchs.back().x = touchX;
	touchs.back().y = touchY;

	bPressedByTouch = true;
}

void ofxTangibleValue::touchMoved(ofTouchEventArgs &e) {
	if (!bGrabbingEnabled || !bPressedByTouch)
		return;

	float touchX = e.x;
	float touchY = e.y;

	if(bScaleTouchEvent){
		touchX *= ofGetWidth();
		touchY *= ofGetHeight();
	}

	touchCursor & te = touchs[0];
	if(e.id == te.id){
		calcValueByPos(te,ofVec2f(touchX,touchY));
	}
}

void ofxTangibleValue::touchUp(ofTouchEventArgs &e) {
	if (!bGrabbingEnabled || !bPressedByTouch)
		return;

	touchCursor & te = touchs[0];
	if(e.id == te.id){
		touchs.clear();
		value += tmpValue;
		bPressedByTouch = false;
	}
}

void ofxTangibleValue::drawInner(){
	ofxTangibleHandle::drawInner();
	ofDrawBitmapString(ofToString(tmpValue+value),0,0);
}
