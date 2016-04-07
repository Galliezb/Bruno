#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){


	// J'veux tout savoir sur les logs ! Oui on est fou et on aime ça :D
	ofSetLogLevel(OF_LOG_VERBOSE);

	widthScreen = ofGetScreenWidth();
	heightScreen = ofGetScreenHeight();

	test1.init(widthScreen, heightScreen);

	bool succes = false;

	succes = test1.remplirHerbe();
	ofLogVerbose() << "remplirHerbe => "<< succes;
	succes = test1.ajoutLac(10,10);
	ofLogVerbose() << "ajoutLac(10,10) => "<< succes;
	
	// test ajoute des arbres de manière aleatoire
	succes = test1.addTreeRandom();
	ofLogVerbose() << "ajoutLactreeRandom => " << succes;
	// test joute un arbre a une position
	succes = test1.addTree(5,5);
	ofLogVerbose() << "ajouter 1 arbre => " << succes;

	// test ajoute des rochers de manière aleatoire
	succes = test1.addStoneRandom();
	ofLogVerbose() << "ajouter random rocher => " << succes;
	// test joute un rocher a une position
	succes = test1.addStone(6, 5);
	ofLogVerbose() << "ajouter 1 rocher => " << succes;

	//save
	test1.saveMap();
	 

}

//--------------------------------------------------------------
void ofApp::update(){
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	test1.displayMap();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	if (key == OF_KEY_LEFT && !test1.getBoolMoveCameraLeft()) {
		test1.setBoolMoveCameraLeft();
	}
	if (key == OF_KEY_RIGHT && !test1.getBoolMoveCameraRight()) {
		test1.setBoolMoveCameraRight();
	}
	if (key == OF_KEY_UP && !test1.getBoolMoveCameraUp()) {
		test1.setBoolMoveCameraUp();
	}
	if (key == OF_KEY_DOWN && !test1.getBoolMoveCameraDown()) {
		test1.setBoolMoveCameraDown();
	}

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	bool succes = false;

	switch (key) {
	case 'd':
		for (int x = 0; x<10; x++) {
			for (int y = 0; y<10; y++) {
				succes = test1.removeTree(x, y);
				succes = test1.removeStone(x, y);
			}
		}
		ofLogVerbose() << "Suppression effectuée";
		break;
	case 'a':
		for (int x = 0; x<10; x++) {
			for (int y = 0; y<10; y++) {
				succes = test1.addTree(x, y);
				succes = test1.addStone(x, y);
			}
		}
		ofLogVerbose() << "Ajout effectuée";
		break;
	case 's':
		test1.saveMap();
		break;
	case 'u':
		test1.updateMapScreen();
		break;
	}
	if (key == OF_KEY_LEFT && test1.getBoolMoveCameraLeft() ){
		test1.setBoolMoveCameraLeft();
	}
	if (key == OF_KEY_RIGHT && test1.getBoolMoveCameraRight()){
		test1.setBoolMoveCameraRight();
	}
	if (key == OF_KEY_UP && test1.getBoolMoveCameraUp() ){
		test1.setBoolMoveCameraUp();
	}
	if (key == OF_KEY_DOWN && test1.getBoolMoveCameraDown()){
		test1.setBoolMoveCameraDown();
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
