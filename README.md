ofxTangibleUI
=============

Abstract core for tangible/movable/dynamic user interfaces - easy to extend and implement in your own projects.

Under construction - feedback is welcome!
Send me a message if you have a question or need help.

Motivation
----------

This is the first attempt to clean up the whole mess in ofxSPTAUtils. 
There are many well done GUI addons for openFrameworks out but most of them are panel based and we don't only use the interface to set up the application - more often it is part of the application. In many projects we need UI elements which we can drag around, drop here and there and create or delete on the fly. So the requirements for the UI change from project to project and instead of starting the next attempt to build THE GUI ofxTangibleUI is meant to be an abstract core for dynamic GUIs. 

Features
--------
*	dynamic UI objects
*	dependent movement between objects
	
	each object can listen to other objects movements and move in the same, oppesite, or otherwise modified direction
*	easy to extend and implement
*	style and modify (by overriding functions)

Dependencies
------------
*	openFrameworks 0.07

TODO
----
*	save and load from/to XML
*	more basic UI elements
*	examples and tutorials
