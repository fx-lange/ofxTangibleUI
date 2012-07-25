#include "testApp.h"


float x,y;

//--------------------------------------------------------------
void tangibleUiExample::setup(){
	ofSetLogLevel(OF_LOG_NOTICE);
	ofBackground(0);

	//test handles
	handle.setup(40,40,20,20);
	yfixed.setup(40,20,20,10);
	xfixed.setup(20,40,10,20);

	//test listening concept
	xfixed.startListeningTo(handle);
	yfixed.startListeningTo(handle);

	//test mutual listening
	handle.startListeningTo(yfixed);
	handle.startListeningTo(xfixed);

	//test toggle
	toggle.setup(65,40,20,20);
	toggle.startListeningTo(handle);

	//test destructor and copy constructor
	ofxTangibleHandle tempHandle;
	tempHandle.setup(80,80,10,10);
	tempHandle.fillMe = true;
	tempHandle.disableGrabbing();
	tempHandle.startListeningTo(handle);
	handles.push_back(tempHandle);

	//test moveListenerSpeed
	xSpeed3.setup(70,100,30,30);
	xSpeed3.setMoveListenersSpeed(3.f,1.f);
	xSpeed3.color.set(60,170,20);
	handles[0].startListeningTo(xSpeed3);

	//test timeline
	timeline.setup(0,0,ofGetWidth(),ofGetHeight()/3);

	//test control examples
	//pos and scale
	pAndS.setup(400,400,20,40);

	//rotation
	x = 600;
	y = 300;
	r1.setup(x+1,y,10,10,x,y);
	r2.setup(x-15,y,10,10,x,y);
	r1.drawType = r2.drawType = TANGIBLE_DRAW_AS_CIRCLE;

	r1.addRotateListener(&r2);
	r2.addRotateListener(&r1);
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
	pAndS.draw();
	r1.draw();
	r2.draw();
	ofSetColor(255,255,255);
	ofEllipse(x,y,5,5);
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
