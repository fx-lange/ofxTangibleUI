#include "testApp.h"


ofxTangibleHandle handle;
ofPoint old;
ofPoint center;
ofPoint follower;
ofVec3f vec;
float oldAngle;
float angleDiff;

ofxTangibleBezierHelper rotateHandle;
ofxTangibleHandle r1, r2;

ofxTangibleBezierControl bC,bC2,bC3;

ofPolyline line;

//--------------------------------------------------------------
void tangibleUiExample::setup(){
	ofSetLogLevel(OF_LOG_NOTICE);
	ofBackground(0);

	bC.setup(500,300,10,10);
	bC2.setup(100,100,10,10);
	bC3.setup(500,500,10,10);
}

//--------------------------------------------------------------
void tangibleUiExample::update(){
	line.clear();
	line.addVertex(bC2);
	line.bezierTo(bC2.r2,bC.r1,bC);
	line.bezierTo(bC.r2,bC3.r1,bC3);
}

//--------------------------------------------------------------
void tangibleUiExample::draw(){
	ofSetColor(255,255,255);
	line.draw();
	bC.draw();
	bC2.draw();
	bC3.draw();
//	handle.draw();
//	ofEllipse(center,10,10);
//	ofEllipse(old,10,10);
//	ofEllipse(follower,10,10);
//	float currentAngle = (handle-center).angle(old-center);
//
//	float angle = oldAngle - currentAngle;
////
////	angle = 0.1;
//		vec = follower-center;
//		vec.rotate(0,0,angle);
//		follower = center + vec;
////	follower.rotate(0,0,angle);
//
//	ofDrawBitmapString(ofToString(angle),handle);
//	oldAngle = currentAngle;
}

//--------------------------------------------------------------
void tangibleUiExample::keyPressed(int key){

}

//--------------------------------------------------------------
void tangibleUiExample::keyReleased(int key){

}

//--------------------------------------------------------------
void tangibleUiExample::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void tangibleUiExample::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void tangibleUiExample::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void tangibleUiExample::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void tangibleUiExample::windowResized(int w, int h){

}

//--------------------------------------------------------------
void tangibleUiExample::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void tangibleUiExample::dragEvent(ofDragInfo dragInfo){

}
