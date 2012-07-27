#include "ofxTangibleBezierHelper.h"

void ofxTangibleBezierHelper::setup(float _x, float _y, float _w, float _h, float centerX, float centerY) {
	ofxTangibleHandle::setup(_x, _y, _w, _h);
	setRotateCenter(centerX,centerY);
}

void ofxTangibleBezierHelper::moveInner(float dx, float dy) {
	ofxTangibleHandle::moveBy(dx, dy);
}

void ofxTangibleBezierHelper::moveBy(float dx, float dy) {
	moveRotateCenter(dx,dy);
	ofxTangibleHandle::moveBy(dx, dy);
}
