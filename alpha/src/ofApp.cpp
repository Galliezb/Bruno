#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	// réglage du framerate
	ofSetFrameRate(30);

	// J'veux tout savoir sur les logs ! Oui on est fou et on aime ça :D
	ofSetLogLevel(OF_LOG_VERBOSE);

	// taille de l'écran client
	widthScreen = ofGetWindowWidth();
	heightScreen = ofGetWindowHeight();
	//widthScreen = ofGetScreenWidth();
	//heightScreen = ofGetScreenHeight();


	// C'est la position actuel de l'origin 0 - 0 = haut coin haut gauche.
	originX = 0;
	originY = 0;


	// initialisation des classes ( pour passer les valeurs par pointeur surtout )
	// map
	gestionMap.init(&originX,&originY,&widthScreen,&heightScreen);
	// animation personnage
	movePersonnage.init(&originX, &originY,&widthScreen, &heightScreen);

	 

}

//--------------------------------------------------------------
void ofApp::update(){

	// si le joueur a bougé, on met à jour l'info
	if(playerHasMove){
		if (playerMoveTop)   { originY -= scrollingSpeed; }
		if (playerMoveRight) { originX += scrollingSpeed; }
		if (playerMoveDown)  { originY += scrollingSpeed; }
		if (playerMoveLeft)  { originX -= scrollingSpeed; }
		// verification des nons dépassement de limite
		ofLogVerbose() << "originY : " << originY;
		ofLogVerbose() << "originX : " << originX;
		// limite les déplacement dans la carte ( et pas en dehors des limites )
		movePersonnage.limitMovePlayer();

	}

}

//--------------------------------------------------------------
void ofApp::draw(){

	// affiche a l'écran
	gestionMap.displayMap();
	// affichage du personnage
	movePersonnage.movePlayer();


}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	// deplacement position joueur + personnage
	if (key == OF_KEY_UP) {
		if ( !playerMoveTop ) { playerMoveTop = true; }
		if ( !playerHasMove ) { playerHasMove = true; }
		if (!movePersonnage.getBoolMovePlayerTop()) { movePersonnage.setBoolMovePlayerTop(true); }
	}
	if (key == OF_KEY_RIGHT) {
		playerMoveRight = true;
		if (!playerMoveRight) { playerMoveRight = true; }
		if (!playerHasMove) { playerHasMove = true; }
		if (!movePersonnage.getBoolMovePlayerRight()) { movePersonnage.setBoolMovePlayerRight(true); }
	}
	if (key == OF_KEY_DOWN) {
		playerMoveDown = true;
		if (!playerMoveDown) { playerMoveDown = true; }
		if (!playerHasMove) { playerHasMove = true; }
		if (!movePersonnage.getBoolMovePlayerDown()) { movePersonnage.setBoolMovePlayerDown(true); }
	}
	if (key == OF_KEY_LEFT) {
		playerMoveLeft = true;
		if (!playerMoveLeft) { playerMoveLeft = true; }
		if (!playerHasMove) { playerHasMove = true; }
		if (!movePersonnage.getBoolMovePlayerLeft()) { movePersonnage.setBoolMovePlayerLeft(true); }
	}

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

	switch (key) {
		// Fullscreen touche F
		case 'f':
			printf("AVANT changement d ecran : \n");
			ofLogVerbose() << "widthScreen : " << widthScreen;
			ofLogVerbose() << "heightScreen : " << heightScreen;

			ofToggleFullscreen();
			widthScreen = ofGetScreenWidth();
			heightScreen = ofGetScreenHeight();

			printf("APPRES changement d ecran : \n");
			ofLogVerbose() << "widthScreen : " << widthScreen;
			ofLogVerbose() << "heightScreen : " << heightScreen;

			break;


	}

	// deplacement position joueur + animation
	if (key == OF_KEY_UP) {
		playerMoveTop = false;
		if ( movePersonnage.getBoolMovePlayerTop() ){ movePersonnage.setBoolMovePlayerTop(false); }
	}
	if (key == OF_KEY_RIGHT) {
		playerMoveRight = false;
		if (movePersonnage.getBoolMovePlayerRight()) { movePersonnage.setBoolMovePlayerRight(false); }
	}
	if (key == OF_KEY_DOWN) {
		playerMoveDown = false;
		if (movePersonnage.getBoolMovePlayerDown()) { movePersonnage.setBoolMovePlayerDown(false); }
	}
	if (key == OF_KEY_LEFT) {
		playerMoveLeft = false;
		if (movePersonnage.getBoolMovePlayerLeft()) { movePersonnage.setBoolMovePlayerLeft(false); }
	}
	// si aucun mouvement en cours, on repasse a false pour éviter les traitements.
	if (!playerMoveTop && !playerMoveRight && !playerMoveDown && !playerMoveLeft) { playerHasMove = false; }

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
	gestionMap.changeCase(x,y);
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
