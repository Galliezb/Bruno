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


	// C'est la position actuel de l'origin 0 - 0 = haut coin haut gauche.
	positionJoueurX = 450;
	positionJoueurY = 450;


	// initialisation des classes ( pour passer les valeurs par pointeur surtout )
	// map
	gestionMap.init(&positionJoueurX,&positionJoueurY,&widthScreen,&heightScreen, tabContentCase, tabContentTerrain);
	// animation personnage
	movePersonnage.init(&positionJoueurX, &positionJoueurY,&widthScreen, &heightScreen, &playerCurrentAction, tabContentCase, tabContentTerrain);

	movePersonnage.setTimerStart();

}

//--------------------------------------------------------------
void ofApp::update(){

	// si le joueur a bougé, on met à jour l'info
	if(playerHasMove){
		// Gestion des colisions INTEGRE avec les objets présent et les cases d'eau
		movePersonnage.updatePositionJoueur();

		// Le quadrillage Horizontal
		pathLineHorizontal.clear();
		pathLineHorizontal.moveTo(movePersonnage.midX(), movePersonnage.midY());
		pathLineHorizontal.lineTo(movePersonnage.midX()+64, movePersonnage.midY());
		pathLineHorizontal.lineTo(movePersonnage.midX()+64, movePersonnage.midY() + 64);
		pathLineHorizontal.lineTo(movePersonnage.midX(), movePersonnage.midY()+64);
		pathLineHorizontal.lineTo(movePersonnage.midX(), movePersonnage.midY());

		pathLineHorizontal.close();
		pathLineHorizontal.setStrokeColor(ofColor::red);
		pathLineHorizontal.setFilled(false);
		pathLineHorizontal.setStrokeWidth(1);


	}
}

//--------------------------------------------------------------
void ofApp::draw(){


	// affiche a l'écran
	gestionMap.displayMap();
	// affichage du personnage
	movePersonnage.movePlayer();


	string fpsStr = "positionJoueurX => " + ofToString(positionJoueurX);
	ofDrawBitmapString(fpsStr, 20, 100);
	fpsStr = "positionJoueurY => " + ofToString(positionJoueurY);
	ofDrawBitmapString(fpsStr, 20, 125);
	fpsStr = "positionCameraX => " + ofToString(positionJoueurX-widthScreen/2);
	ofDrawBitmapString(fpsStr, 20, 150);
	fpsStr = "positionCameraY => " + ofToString(positionJoueurY-heightScreen/2);
	ofDrawBitmapString(fpsStr, 20, 175);
	fpsStr = "Origin: " + ofToString(positionJoueurX/64)+";"+ofToString(positionJoueurY/64);
	ofDrawBitmapString(fpsStr, 20, 200);
	fpsStr = "Origin(pied): " + ofToString((positionJoueurX+32) / 64) + ";" + ofToString((positionJoueurY+60) / 64);
	ofDrawBitmapString(fpsStr, 20, 225);
	pathLineHorizontal.draw();

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
		case 'g':

			ofToggleFullscreen();
			widthScreen = ofGetWindowWidth();
			heightScreen = ofGetWindowHeight();
			break;

		case 'a': playerCurrentAction = "construire"; break;
		case 'z': playerCurrentAction = "courir"; break;
		case 'e': playerCurrentAction = "degat"; break;
		case 'r': playerCurrentAction = "hacher"; break;
		case 't': playerCurrentAction = "miner"; break;
		case 'y': playerCurrentAction = "mort"; break;
		case 'u': playerCurrentAction = "attaquer"; break;
		case 'i': playerCurrentAction = "repos"; break;
		case 'q': 
			for (int x = 0; x<15; x++) {
				for (int y = 0; y<15; y++) {
					gestionMap.restoreGrass(x, y);
				}
			}
			break;
		case 's':
			for (int x=0;x<15;x++){
				for(int y=0; y<15;y++){
					gestionMap.addRessource(x, y,true,false);
				}
			}
			break;
		case 'd':
			for (int x = 0; x<15; x++) {
				for (int y = 0; y<15; y++) {
					gestionMap.addRessource(x, y, false, true);
				}
			}
			break;
		case 'f':
			for (int x = 0; x<15; x++) {
				for (int y = 0; y<15; y++) {
					gestionMap.changeCaseWater(x, y);
				}
			}
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
	printf("X => %d\tY=>%d\n",movePersonnage.returnPosCaseX("center"), movePersonnage.returnPosCaseY("top"));
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
	widthScreen = ofGetWindowWidth();
	heightScreen = ofGetWindowHeight();
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
