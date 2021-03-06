#include "testApp.h"

bool ePrintPoints = false;

//--------------------------------------------------------------
void bezierExample::setup(){
	ofSetLogLevel(OF_LOG_VERBOSE);
	ofBackground(0);

	bezier.setup();
}

//--------------------------------------------------------------
void bezierExample::update(){
	if(ePrintPoints){
		bezier.printLinePoints();
		ePrintPoints = false;
	}
}

//--------------------------------------------------------------
void bezierExample::draw(){
	ofSetColor(255,255,255);
	bezier.draw();
}

//--------------------------------------------------------------
void bezierExample::keyPressed(int key){
	if(key == 'd'){
		bezier.toggleDrawing();
	}
	if(key == 'c'){
		bezier.clear();
	}
	if(key == 'p'){
		ePrintPoints = true;
	}
}

//--------------------------------------------------------------
void bezierExample::keyReleased(int key){

}

//--------------------------------------------------------------
void bezierExample::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void bezierExample::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void bezierExample::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void bezierExample::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void bezierExample::windowResized(int w, int h){

}

//--------------------------------------------------------------
void bezierExample::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void bezierExample::dragEvent(ofDragInfo dragInfo){

}
