#pragma once
#include "ofApp.h"
#include "classeMoving.h"

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
	positionJoueurX = 1000;
	positionJoueurY = 1000;


	// initialisation des classes ( pour passer les valeurs par pointeur surtout )
	// map
	gestionMap.init(&positionJoueurX,&positionJoueurY,&widthScreen,&heightScreen, tabContentCase, tabContentTerrain);
	// animation personnage
	movePersonnage.init(&positionJoueurX, &positionJoueurY,&widthScreen, &heightScreen, &playerCurrentAction, tabContentCase, tabContentTerrain, tabContentRessourcePlayer, &gestionMap);
	movePersonnage.setTimerStart();
	// inventaire
	inventaire.init(tabContentRessourcePlayer, &widthScreen, &heightScreen);
	// zombis
	for (int i=0; i<maxZombi; i++){
		zombis[i].init(&positionJoueurX, &positionJoueurY, &widthScreen, &heightScreen, tabContentCase, tabContentTerrain, &playerCurrentAction);
	}
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

	// Si une récolte est en cours
	if (actionRecolteActive){
		actionRecolteActive = movePersonnage.actionRecolteEnd();
	}

	// fait spawn du zombis toutes les 15 sec
	if ( tpsSpawnZombi - ofGetElapsedTimeMillis() > 15000 ){
		for(int i=0; i<maxZombi; i++){
			// si cette unité n'est pas affecté
			if ( !zombis[i].isSpawnZombi ){
				zombis[i].spawnZombi();
			}
		}
	}

	// effectue les traitements sur les zombis
	for (int i = 0; i<maxZombi; i++) {
		// si cette unité n'est pas affecté
		if (zombis[i].isSpawnZombi) {
			zombis[i].moveZombi();
		}
		// si un zombi est a distance action joueur = attaqué
		if (playerCurrentAction != "degat" && zombis[i].distanceBetweenPLayerAndZombi() <= 32){
			// metes l'action joueur en degat s'il n'y est pas.
			printf("%d => degats", ofGetElapsedTimeMillis());
			playerCurrentAction = "degat";
		}
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

	if (affInventaire){
		inventaire.affichage();
	}

	for (int i = 0; i<maxZombi; i++) {
		// si cette unité n'est pas affecté
		if (zombis[i].isSpawnZombi) {
			zombis[i].displayZombi();
		}
	}
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

			ofToggleFullscreen();
			widthScreen = ofGetWindowWidth();
			heightScreen = ofGetWindowHeight();
			break;
		case 'e':
			movePersonnage.actionRecolteStart();
			actionRecolteActive = true;
			break;
		case 'i':
			(affInventaire)? affInventaire=false: affInventaire=true;
			break;
	}

	// deplacement position joueur + animation
	if (key == OF_KEY_UP) {
		playerMoveTop = false;
		if ( movePersonnage.getBoolMovePlayerTop() ){ movePersonnage.setBoolMovePlayerTop(false); }
		playerCurrentAction = "repos";
	}
	if (key == OF_KEY_RIGHT) {
		playerMoveRight = false;
		if (movePersonnage.getBoolMovePlayerRight()) { movePersonnage.setBoolMovePlayerRight(false); }
		playerCurrentAction = "repos";
	}
	if (key == OF_KEY_DOWN) {
		playerMoveDown = false;
		if (movePersonnage.getBoolMovePlayerDown()) { movePersonnage.setBoolMovePlayerDown(false); }
		playerCurrentAction = "repos";
	}
	if (key == OF_KEY_LEFT) {
		playerMoveLeft = false;
		if (movePersonnage.getBoolMovePlayerLeft()) { movePersonnage.setBoolMovePlayerLeft(false); }
		playerCurrentAction = "repos";
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
	// inventaire affiché, si clique en dehors, on stop l'affichage
	printf("%d < %d || %d > %d || %d < %d || %d > %d\n", x,inventaire.returnPosXWindow(),x,inventaire.returnPosXWindow()+1024,y,inventaire.returnPosYWindow(),y,inventaire.returnPosYWindow()+642);
	if (affInventaire && ( x<inventaire.returnPosXWindow() || x>inventaire.returnPosXWindow()+1024 || y<inventaire.returnPosYWindow() || y>inventaire.returnPosYWindow()+642) ){
		affInventaire = false;
	} else {
		printf("X => %d\tY=>%d\n", movePersonnage.returnPosCaseX("center"), movePersonnage.returnPosCaseY("top"));
	}
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
