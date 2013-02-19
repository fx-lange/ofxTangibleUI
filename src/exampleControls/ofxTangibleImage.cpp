#include "ofxTangibleImage.h"

void ofxTangibleImage::setup(float x, float y,string imageName, float w, float h){
	image.loadImage(imageName);

	w = w!=0 ? w : image.getWidth();
	h = h!=0 ? h : image.getHeight();

	ofxTangibleHandle::setup(x+w/2.f,y+h/2.f,w,h);
}

void ofxTangibleImage::drawInner(){
	image.draw(0,0, width, height);
}
