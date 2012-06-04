#include "testApp.h"

ofxTangibleHandle handle;
ofxTangibleXFixedHandle xfixed;
ofxTangibleYFixedHandle yfixed;
ofxTangibleToggle toggle;
vector<ofxTangibleHandle> handles;
ofxTangibleYFixedHandle xSpeed3;
ofxTimeline timeline;

//--------------------------------------------------------------
void tangibleUiExample::setup(){
	ofSetLogLevel(OF_LOG_NOTICE);
	ofBackground(0);

	//test handles
	handle.setup(40,40,20,20);
	yfixed.setup(40,20,20,10);
	xfixed.setup(20,40,10,20);

	//test listening concept
	handle.addListener(&xfixed);
	handle.addListener(&yfixed);

	//test mutual listening
	yfixed.addListener(&handle);
	xfixed.addListener(&handle);

	//test toggle
	toggle.setup(65,40,20,20);
	handle.addListener(&toggle);

	//test destructor and copy constructor
	ofxTangibleHandle tempHandle;
	tempHandle.setup(80,80,10,10);
	tempHandle.fillMe = true;
	tempHandle.disableGrabbing();
	handle.addListener(&tempHandle);
	handles.push_back(tempHandle);

	//test moveListenerSpeed
	xSpeed3.setup(70,100,30,30);
	xSpeed3.setMoveListenersSpeed(3.f,1.f);
	xSpeed3.color.set(60,170,20);
	xSpeed3.addListener(&handles[0]);

	//test timeline
	timeline.setup(0,0,ofGetWidth(),ofGetHeight()/3);
}

//--------------------------------------------------------------
void tangibleUiExample::update(){
	if(toggle.hasChanged()){
		handle.setGrabbing(!toggle.isActive());
		handle.fillMe = toggle.isActive();
		toggle.resetChanged();
	}
}

//--------------------------------------------------------------
void tangibleUiExample::draw(){
	handle.draw();
	toggle.draw();
	xfixed.draw();
	yfixed.draw();
	handles[0].draw();
	xSpeed3.draw();
	timeline.draw();
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
