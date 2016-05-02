#include "ofApp.h"


// taille carte
const int maxCaseX = 10000;
const int maxCaseY = 10000;

// Tableau contenant chaque cellule de la map
int affichageTabMap[maxCaseX][maxCaseY] = { 0 };
int cheminCaseTabMap[50] = {};
// variable pour la caméra
int positionCameraX = 0;
int positionCameraY = 0;


// Mouvement camera
bool moveCameraLeft = false;
bool moveCameraRight = false;
bool moveCameraUp = false;
bool moveCameraDown = false;
// Affichage du quadrillage de la carte
bool toggleDrawLine = true;
// vitesse scrolling
short int vitesseScrolling = 15;
// Nombre de case affiché chez l'utilisateur selon la taille ecran
int nbrCaseX = 0;
int nbrCaseY = 0;

int widthScreenUser = 0;
int heightScreenUser = 0;

int test = 0;
int nbrSave = 0;

bool imgReady = false;

//--------------------------------------------------------------
void ofApp::setup(){


	// Max info dans les logs
	ofSetLogLevel(OF_LOG_VERBOSE);

	widthScreenUser = ofGetScreenWidth();
	heightScreenUser = ofGetScreenHeight();

	// mise a jour donnée selon taille ecran utilisateur
	nbrCaseX = widthScreenUser / 32 + 1;
	nbrCaseY = heightScreenUser / 32 + 1;

	// mise à jour des données d'emplacement caméra
	positionCameraX = maxCaseX * 32 / 2 - widthScreenUser / 2;
	positionCameraY = maxCaseY * 32 / 2 - heightScreenUser / 2;

	positionCameraX = 0;
	positionCameraY = 0;

	// limite le framerate
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	// définition de la fenetre
	ofSetWindowTitle("Deadly Utility");
	ofSetWindowShape(800, 600);
	ofBackground(ofColor::black);

	// test generation map
	testGeneration.genereMapLayer1();

}

//--------------------------------------------------------------
void ofApp::update(){

	// mouvement camera DOWN
	if (moveCameraDown) {
		positionCameraY += vitesseScrolling;
		if (positionCameraY > ceil(maxCaseY * 32 - widthScreenUser / 2)) {
			positionCameraY = ceil(maxCaseY * 32 - widthScreenUser / 2);
		}
	}
	// mouvement camera UP
	if (moveCameraUp) {
		positionCameraY -= vitesseScrolling;
		if (positionCameraY < 0) {
			positionCameraY = 0;
		}
	}
	// mouvement camera LEFT
	if (moveCameraLeft) {
		positionCameraX -= vitesseScrolling;
		if (positionCameraX < 0) {
			positionCameraX = 0;
		}
	}
	// mouvement camera RIGHT
	if (moveCameraRight) {
		positionCameraX += vitesseScrolling;
		if (positionCameraX > floor(maxCaseX * 32 - (widthScreenUser / 2))) {
			positionCameraX = floor(maxCaseX * 32 - (widthScreenUser / 2));
		}
	}

	// Le quadrillage vertical
	pathLineVertical.clear();
	pathLineVertical.moveTo(32 - positionCameraX % 32, 0);
	for (int i = 0; i < widthScreenUser / 32; i++) {
		pathLineVertical.moveTo(32 - positionCameraX % 32 + i * 32, 0);
		pathLineVertical.lineTo(32 - positionCameraX % 32 + i * 32, positionCameraX % 32 + heightScreenUser);
	}
	pathLineVertical.close();
	pathLineVertical.setStrokeColor(ofColor::white);
	pathLineVertical.setFilled(false);
	pathLineVertical.setStrokeWidth(1);

	// Le quadrillage Horizontal
	pathLineHorizontal.clear();
	pathLineHorizontal.moveTo(0, 32 - positionCameraY % 32);
	for (int i = 0; i < heightScreenUser / 32; i++) {
		pathLineHorizontal.moveTo(0, 32 - positionCameraY % 32 + i * 32);
		pathLineHorizontal.lineTo(widthScreenUser, 32 - positionCameraY % 32 + i * 32);
	}
	pathLineHorizontal.close();
	pathLineHorizontal.setStrokeColor(ofColor::white);
	pathLineHorizontal.setFilled(false);
	pathLineHorizontal.setStrokeWidth(1);


}

//--------------------------------------------------------------
void ofApp::draw(){

	//img.drawSubsection(0,0,widthScreenUser,heightScreenUser,positionCameraX, positionCameraY, widthScreenUser, heightScreenUser);

	testGeneration.afficheCarte(positionCameraX,positionCameraY);

	if (toggleDrawLine) {
		pathLineVertical.draw();
		pathLineHorizontal.draw();
	}
	


	string fpsStr = "frame rate: " + ofToString(ofGetFrameRate(), 2);
	ofDrawBitmapString(fpsStr, 100, 50);
	
	fpsStr = "positionCameraX%32: " + ofToString(positionCameraX);
	ofDrawBitmapString(fpsStr, 100, 75);

	fpsStr = "positionCameraY: " + ofToString(positionCameraY);
	ofDrawBitmapString(fpsStr, 100, 100);

	fpsStr = "vitesseScrolling: " + ofToString(vitesseScrolling);
	ofDrawBitmapString(fpsStr, 100, 125);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	if (key == OF_KEY_LEFT) {
		moveCameraLeft = true;
	}
	if (key == OF_KEY_RIGHT) {
		moveCameraRight = true;
	}
	if (key == OF_KEY_UP) {
		moveCameraUp = true;
	}
	if (key == OF_KEY_DOWN) {
		moveCameraDown = true;
	}

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	switch (key)
	{
	case 'f' :
		ofToggleFullscreen();
		break;
	case 'l':
		(toggleDrawLine) ? toggleDrawLine = false : toggleDrawLine = true;
		break;
	}
	if (key == OF_KEY_LEFT) {
		moveCameraLeft = false;
	}
	if (key == OF_KEY_RIGHT) {
		moveCameraRight = false;
	}
	if (key == OF_KEY_UP) {
		moveCameraUp = false;
	}
	if (key == OF_KEY_DOWN) {
		moveCameraDown = false;
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
