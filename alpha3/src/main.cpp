#pragma once#include "ofMain.h"
#include "ofApp.h"



//========================================================================
int main( ){
	ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:

	// fixe
	//ofSetWindowPosition(2300,50);
	// portable
	ofSetWindowPosition(1600-ofGetWindowWidth(),0);

	ofRunApp(new ofApp());

}
