#include "tuioExample.h"

ofxTangibleBase base;
ofxTangibleToggle toggle;
ofxTangibleButton button;

//--------------------------------------------------------------
void tuioExample::setup(){
	ofBackground(200, 200, 200);
	ofSetVerticalSync(true);
	
	//Connect to Port
	myTuio.connect(3333);
	
	//Assign Global TUIO Callback Functions
	ofAddListener(ofEvents().touchDown,this,&tuioExample::touchDown);
	ofAddListener(ofEvents().touchUp,this,&tuioExample::touchUp);
	ofAddListener(ofEvents().touchMoved,this,&tuioExample::touchMoved);

	//TangibleUI
	base.setup(200,400,300,300);
	toggle.setup(300,150,100,100);
	button.setup(500,150,100,100);
	button.addEventListener(&toggle,&ofxTangibleToggle::activateByEvent);
}

//--------------------------------------------------------------
void tuioExample::update(){

}

//--------------------------------------------------------------
void tuioExample::draw(){
	
	//render TUIO Cursors and Objects
	myTuio.drawCursors();
	myTuio.drawObjects();

	base.draw();
	toggle.draw();
	button.draw();
}

//--------------------------------------------------------------
void tuioExample::keyPressed(int key){
	switch(key){
	case 'r':
		base.rotateInner(5);
		break;
	}
}

//--------------------------------------------------------------
void tuioExample::keyReleased(int key){

}

//--------------------------------------------------------------
void tuioExample::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void tuioExample::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void tuioExample::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void tuioExample::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void tuioExample::windowResized(int w, int h){

}


void tuioExample::touchDown(ofTouchEventArgs & touch){
	cout << " cursor added: " + ofToString(touch.id)+
	" X: "+ofToString(touch.x)+
	" Y: "+ofToString(touch.y)
	<< endl;

	
}

void tuioExample::touchUp(ofTouchEventArgs & touch){
	cout << " cursor removed: " + ofToString(touch.id)+
	 " X: "+ofToString(touch.x)+
	 " Y: "+ofToString(touch.y)
	 << endl;
	
}

void tuioExample::touchMoved(ofTouchEventArgs & touch){
	cout << " cursor updated: " + ofToString(touch.id)+
	 " X: "+ofToString(touch.x)+
	 " Y: "+ofToString(touch.y)
	 << endl;
}

