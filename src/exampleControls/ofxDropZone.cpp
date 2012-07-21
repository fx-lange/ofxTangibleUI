#include "ofxDropZone.h"

void ofxDropZone::setup(float x,float y,float w,float h){
	this->x = x;
	this->y = y;
	internalRect.width = w;
	internalRect.height = h;
}

ofxDropZone::operator ofRectangle & (){
	internalRect.x = x;
	internalRect.y = y;
	internalRect.width = width;
	internalRect.height = height;
	return internalRect;
}

ofRectangle ofxDropZone::operator=(ofRectangle _rect){
	internalRect = _rect;
	x = internalRect.x;
	y = internalRect.y;
	width = internalRect.width;
	height = internalRect.height;
	return internalRect;
}