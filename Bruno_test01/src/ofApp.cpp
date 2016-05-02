#include "ofApp.h"
#include <math.h>

// Déclaration des variables GLOBALES
int tabAnimPersoDroiteGauche[20][2] = { {0,0},{60,0},{120,0},{180,0} };
int tabAnimPersoRepos[20][2] = { {0,72},{ 60,72 },{ 120,72 },{ 0,72 },{ 0,72 },{ 0,72 },{ 0,72 },{ 0,72 },{ 0,72 },{ 0,72 },{ 0,72 },{ 0,72 },{ 0,72 },{ 0,72 },{ 0,72 },{ 0,72 },{ 0,72 },{ 0,72 },{ 0,72 },{ 0,72 } };
int i = 0;
int j = 0;
int a = 100;
bool goDroite = false;
bool goGauche = false;
bool lastmoveGauche = false;
bool lastmoveDroite = true;
string str = "";
bool affichage = true;
bool adroite = false, agauche = false, enhaut = false, enbas = false;
int x=0, y=0;



//--------------------------------------------------------------
void ofApp::setup(){
	// répertoire de base = bin/data
	image.load("img/personnage.png");

	// limite le framerate
	ofSetFrameRate(10);
	ofSetVerticalSync(true);

	
}

//--------------------------------------------------------------
void ofApp::update(){
	if (adroite) { x += 5; } else if (agauche) { x -= 5; }
	if (agauche) { x -= 5; } else if (adroite) { x += 5; }
	if (enhaut) { y -= 5; }
	if (enbas) { y += 5; }
}

//--------------------------------------------------------------
void ofApp::draw(){

	/*
	//ofDrawRectRounded(x, y, width, height, radius);
	ofSetColor(255, 0, 255);
	ofDrawRectRounded(round(ofGetWindowWidth()/2-75), round(ofGetWindowHeight() / 2)-26, 150, 50, 5);

	ofSetColor(255, 0, 255);
	ofDrawRectRounded(round(ofGetWindowWidth() / 2-75), round(ofGetWindowHeight() / 2)+26, 150, 50, 5);

	// ecrire à l'écran ( affichage du FPS )
	string fpsStr = "frame rate: " + ofToString(ofGetFrameRate(), 2);
	ofDrawBitmapString(fpsStr, 100, 100);
	*/

	// affiche l'image ( x, y, width, height );
	//image.draw(100, 100,250,250);
	// FPS
	string fpsStr = "frame rate: " + ofToString(ofGetFrameRate(), 2);
	ofDrawBitmapString(fpsStr, 100, 50);

	if (affichage) {
		fpsStr = "Affichage => TRUE";
	} else {
		fpsStr = "Affichage => FALSE";
	}
	ofDrawBitmapString(fpsStr, 100, 25);

	if (affichage) {
		// AIDE TEXTE VARIABLE
		if (goDroite || goGauche) {
			(goDroite) ? str = "Va a droite" : str = "Va a gauche";
		}
		else {
			(lastmoveDroite) ? str = "lastMoveDroite" : str = "lastMoveGauche";
		}
		ofDrawBitmapString(str, 100, 75);

		// drawSubsection ( posX,posY,Width,Height,posXsprite,posYsprite,widthSprite,HeightSprite);
		if (goDroite) {
			image.drawSubsection(x, y, 60, 72, tabAnimPersoDroiteGauche[i][0], tabAnimPersoDroiteGauche[i][1], 60, 72);
			i++;
			if (i > 3) { i = 0; }

		}
		else if (goGauche) {
			// +144 sur la sprite pour atteindre la 3e ligne
			image.drawSubsection(x, y, 60, 72, tabAnimPersoDroiteGauche[i][0], tabAnimPersoDroiteGauche[i][1] + 144, 60, 72);
			i++;
			if (i > 3) { i = 0; }
		}
		else {
			if (lastmoveDroite) {
				image.drawSubsection(x, y, 60, 72, tabAnimPersoRepos[j][0], tabAnimPersoRepos[j][1], 60, 72);
				j++;
				if (j > 19) { j = 0; }
			}
			else {
				// le meme mais +180 pour le décalage a droite sur la sprite
				image.drawSubsection(x, y, 60, 72, tabAnimPersoRepos[j][0] + 180, tabAnimPersoRepos[j][1], 60, 72);
				j++;
				if (j > 19) { j = 0; }
			}
		}
	}

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key)
	{
	case 'a':
		(affichage == true) ? affichage = false : affichage = true;
		break;
	case 'q':
		a -= 5;
		goGauche = true;
		break;
	case OF_KEY_LEFT:
		a -= 5;
		goGauche = true;
		agauche = true;
		break;
	case 'd':
		a += 5;
		goDroite = true;
		break;
	case OF_KEY_RIGHT:
		a += 5;
		goDroite = true;
		adroite = true;
		break;
	case OF_KEY_UP:
		enhaut = true;
		break;
	case OF_KEY_DOWN:
		enbas = true;
		break;
	}
	if (goDroite == true) {
		lastmoveDroite = true;
		lastmoveGauche = false;
	} else {
		lastmoveDroite = false;
		lastmoveGauche = true;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	switch (key)
	{
	case 'q':
		goGauche = false;
		break;
	case OF_KEY_LEFT:
		goGauche = false;
		agauche = false;
		break;
	case 'd':
		goDroite = false;
		break;
	case OF_KEY_RIGHT:
		goDroite = false;
		adroite = false;
		break;
	case OF_KEY_UP:
		enhaut = false;
		break;
	case OF_KEY_DOWN:
		enbas = false;
		break;
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
