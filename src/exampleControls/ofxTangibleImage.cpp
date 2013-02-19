#include "ofxTangibleImage.h"

void ofxTangibleImage::setup(float x, float y,string imageName, float w, float h){
	image.loadImage(imageName);

	w = w!=0 ? w : image.getWidth();
	h = h!=0 ? h : image.getHeight();

	ofxTangibleHandle::setup(x+w/2.f,y+h/2.f,w,h);
}

void ofxTangibleImage::draw(){
	ofPushMatrix();
	ofTranslate(x,y);
	ofRotate(innerRotate);
	image.draw(-width/2, -height/2, width, height);
	ofPopMatrix();
}
