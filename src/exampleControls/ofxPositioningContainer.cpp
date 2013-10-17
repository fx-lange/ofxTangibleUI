#include "ofxPositioningContainer.h"

ofxPositioningContainer::ofxPositioningContainer(){
	bPositioningActive = false;
}

void ofxPositioningContainer::push_back(ofxTangibleCore * obj){
	ofxTangibleHandle positioner;
	positioner.setup(obj->x,obj->y,obj->width,obj->height);
	positioner.unregisterMouse();
	positioner.unregisterTouch();

	positioner.startListeningTo(obj);
	obj->startListeningTo(positioner);

	mover.push_back(positioner);
	objects.push_back(obj);
}

void ofxPositioningContainer::enablePositioning(){
	for(int i=0; i<objects.size(); ++i){
		objects[i]->unregisterMouse();
		objects[i]->unregisterTouch();
		mover[i].registerMouse();
		mover[i].registerTouch();
		mover[i].x = objects[i]->x;
		mover[i].y = objects[i]->y;
	}
	bPositioningActive = true;
}

void ofxPositioningContainer::disablePositioning(){
	for(int i=0; i<objects.size(); ++i){
		objects[i]->registerMouse();
		objects[i]->registerTouch();
		mover[i].unregisterMouse();
		mover[i].unregisterTouch();
	}
	bPositioningActive = false;
}

void ofxPositioningContainer::togglePositioning(){
	if(bPositioningActive){
		disablePositioning();
	}else{
		enablePositioning();
	}
}


