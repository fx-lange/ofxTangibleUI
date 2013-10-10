#include "testApp.h"


float x,y;

//--------------------------------------------------------------
void tangibleUiExample::setup(){
	ofSetLogLevel(OF_LOG_VERBOSE);
	ofBackground(0);
	ofEnableAlphaBlending();

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
	toggle.addEventListener(this,&tangibleUiExample::toggleHasChanged);

	//test button
	button.setup(90,40,20,20);
	button.startListeningTo(toggle);
	button.addEventListener(this,&tangibleUiExample::buttonHasChanged);

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


	// ----- test control examples ----- //
	//pos and scale
	pAndS.setup(200,300,40,80);

	//timeline
	timeline.setup(0,0,ofGetWidth(),ofGetHeight()/4);

	//rotation
	x = 600;
	y = 300;
	r1.setup(x+15,y,10,10,x,y);
	r2.setup(x-15,y,10,10,x,y);
	r1.drawType = r2.drawType = TANGIBLE_DRAW_AS_CIRCLE;

	r1.startListeningTo(r2,TANGIBLE_ROTATE);
	r2.startListeningTo(r1,TANGIBLE_ROTATE);

	ofxTangibleBezierHelper h1,h2;

	h1.setup(x+50,y,50,50,x,y);
	h2.setup(x-50,y,10,10,x,y);
	h1.color.set(0,255,100);
	h1.drawType = h2.drawType = TANGIBLE_DRAW_AS_CIRCLE;

	h1.startListeningTo(h2,TANGIBLE_ROTATE);
	h2.setKeepSameDistance(true);
	h1.setKeepSameDistance(true);
	h2.startListeningTo(h1,TANGIBLE_ROTATE);
	r1.startListeningTo(h1,TANGIBLE_ROTATE);
	helpers.push_back(h1);
	helpers.push_back(h2);

	//images
	imageHandle.setup(500,100,"transparency.png");
	imageHandle.bDrawDebug = true;

	//tangible value
	tangibleValue.setup(200,500,100,100);

	//rotary knob
	knob.setup(500,500,100,100);
}

void tangibleUiExample::toggleHasChanged(bool & active){
	cout << "has changed: "+ofToString(active) << endl;
	handle.setGrabbing(!active);
}

void tangibleUiExample::buttonHasChanged(bool & active){
	cout << "has changed: "+ofToString(active) << endl;
	if(toggle.isActive())
		toggle.setActive(false);
}

//--------------------------------------------------------------
void tangibleUiExample::update(){
}

//--------------------------------------------------------------
void tangibleUiExample::draw(){
	handle.draw();
	toggle.draw();
	button.draw();
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

	helpers[0].draw();
	helpers[1].draw();

	imageHandle.draw();
	tangibleValue.draw();
	knob.draw();
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
