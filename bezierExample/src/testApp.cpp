#include "testApp.h"



ofxTangibleBezierControl bC,bC2,bC3;
ofPolyline line;
ofxTangibleBezier bezier;

//--------------------------------------------------------------
void tangibleUiExample::setup(){
	ofSetLogLevel(OF_LOG_NOTICE);
	ofBackground(0);

	bC.setup(500,300,10,10);
	bC2.setup(100,100,10,10);
	bC3.setup(500,500,10,10);

	bezier.setup();
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
//	line.draw();
//	bC.draw();
//	bC2.draw();
//	bC3.draw();

	bezier.draw();
}

//--------------------------------------------------------------
void tangibleUiExample::keyPressed(int key){
	if(key == 'd'){
		bezier.bGrabbingEnabled = !bezier.bGrabbingEnabled;
	}
	if(key == 'c'){
		bezier.controls.clear();
	}
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
