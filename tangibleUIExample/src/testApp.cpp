#include "testApp.h"

ofxHandle handle;
ofxHandleXFixed xfixed;
ofxHandleYFixed yfixed;
ofxToggle toggle;
vector<ofxHandle> handles;

ofxTangiblePolyline line;

//--------------------------------------------------------------
void tangibleUiExample::setup(){
	ofSetLogLevel(OF_LOG_NOTICE);

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
	ofxHandle tempHandle;
	tempHandle.setup(80,80,10,10);
	tempHandle.fillMe = true;
	tempHandle.disableGrabbing();
	handle.addListener(&tempHandle);
	handles.push_back(tempHandle);

	//test tangiblePolyline
	line.addVertex(200,200);
	line.addVertex(200,210);
	line.addVertex(200,220);
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
	line.draw();
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
