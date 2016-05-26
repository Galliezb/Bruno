#pragma once#include "ofMain.h"
#include "ofApp.h"



//========================================================================
int main( ){
	ofSetupOpenGL(1920,1080,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:

	// fixe
	//ofSetWindowPosition(2150,50);
	// portable
	//ofSetWindowPosition(1600-ofGetWindowWidth(),25);
	

	ofRunApp(new ofApp());

}
