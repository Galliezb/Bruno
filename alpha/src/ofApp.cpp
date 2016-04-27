#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	// r�glage du framerate
	ofSetFrameRate(30);

	// J'veux tout savoir sur les logs ! Oui on est fou et on aime �a :D
	ofSetLogLevel(OF_LOG_VERBOSE);

	// taille de l'�cran client
	widthScreen = ofGetWindowWidth();
	heightScreen = ofGetWindowHeight();
	//widthScreen = ofGetScreenWidth();
	//heightScreen = ofGetScreenHeight();


	// C'est la position actuel de l'origin 0 - 0 = haut coin haut gauche.
	originX = 0;
	originY = 0;


	// initialisation des classes ( pour passer les valeurs par pointeur surtout )
	// map
	gestionMap.init(&originX,&originY,&widthScreen,&heightScreen, tabContentCase, tabContentTerrain);
	// animation personnage
	movePersonnage.init(&originX, &originY,&widthScreen, &heightScreen, &playerCurrentAction, tabContentCase, tabContentTerrain);

	movePersonnage.setTimerStart();
	 

}

//--------------------------------------------------------------
void ofApp::update(){

	// si le joueur a boug�, on met � jour l'info
	if(playerHasMove){
		if (playerMoveTop){ 
			originY -= scrollingSpeed; 
			if (originY < 1 - heightScreen/2 - 32 + 64) { 
				originY = 1 - heightScreen/2 - 32 + 64; 
			}
		}
		if (playerMoveRight){ 
			originX += scrollingSpeed; 
			if (originX > 7679-widthScreen / 2) { 
				originX = 7680 - widthScreen / 2; 
			}
		}
		if (playerMoveDown){ 
			originY += scrollingSpeed; 
			if (originY > 5119-heightScreen/2) { 
				originY = 5120 - heightScreen/2; 
			}
		}
		if (playerMoveLeft){ 
			originX -= scrollingSpeed; 
			if (originX < 1 - widthScreen / 2 - 32 + 64) { 
				originX = 1 - widthScreen / 2 - 32 + 64;
			}
		}
		// limite les d�placement dans la carte ( et pas en dehors des limites )
		//movePersonnage.limitMovePlayer();
	}

	movePersonnage.setTimerEnd();

}

//--------------------------------------------------------------
void ofApp::draw(){

	// affiche a l'�cran
	gestionMap.displayMap();
	// affichage du personnage
	movePersonnage.movePlayer();

	string fpsStr = "start => " + ofToString(movePersonnage.getTimerStart());
	ofDrawBitmapString(fpsStr, 10, 100);
	fpsStr = "end => " + ofToString(movePersonnage.getTimerEnd());
	ofDrawBitmapString(fpsStr, 20, 125);
	fpsStr = "Diff => " + ofToString(movePersonnage.getDiffTime());
	ofDrawBitmapString(fpsStr, 20, 150);

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
	// si aucun mouvement en cours, on repasse a false pour �viter les traitements.
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
	gestionMap.returnPosCase(x,y);
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
