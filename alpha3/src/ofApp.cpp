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
	positionJoueurX = 384;
	positionJoueurY = 384;


	// initialisation des classes ( pour passer les valeurs par pointeur surtout )
	// map
	gestionMap.init(&positionJoueurX,&positionJoueurY,&widthScreen,&heightScreen, tabContentCase, tabContentTerrain);
	// animation personnage
	movePersonnage.init(&positionJoueurX, &positionJoueurY,&widthScreen, &heightScreen, &playerCurrentAction, tabContentCase, tabContentTerrain, tabContentRessourcePlayer, &gestionMap, &barreDeVie);
	movePersonnage.setTimerStart();
	// inventaire
	inventaire.init(tabContentRessourcePlayer, &widthScreen, &heightScreen);
	// zombis
	for (int i=0; i<maxZombi; i++){
		zombis[i].init(&positionJoueurX, &positionJoueurY, &widthScreen, &heightScreen, tabContentCase, tabContentTerrain, &playerCurrentAction, zombis, &maxZombi, &barreDeVie);
	}

	// init gestion des barre
	barreDeVie.init(&widthScreen, &heightScreen);
	font.load("arialR.ttf", 15);

	//init gestion des méteo
	for (int i = 0; i <= 49; i++) {
		Sleep(1);
		lancementMeteo[i].initMeteo(&positionJoueurX, &positionJoueurY, &widthScreen, &heightScreen);
	}
	lancementPluie.initPluie();
	font.load("arialR.ttf", 15);
	// init projectile
	for (int i = 0; i<5; i++) {
		projectile[i].init(&positionJoueurX, &positionJoueurY, &widthScreen, &heightScreen, tabContentRessourcePlayer);
	}
}


//--------------------------------------------------------------
void ofApp::update() {

	if (affInventaire) {
		inventaire.affichage();
	}
	else {

		// si le joueur a bougé, on met à jour l'info
		if (playerHasMove) {
			// Gestion des colisions INTEGRE avec les objets présent et les cases d'eau
			movePersonnage.updatePositionJoueur();

			// Le quadrillage Horizontal
			pathLineHorizontal.clear();
			pathLineHorizontal.moveTo(movePersonnage.midX(), movePersonnage.midY());
			pathLineHorizontal.lineTo(movePersonnage.midX() + 64, movePersonnage.midY());
			pathLineHorizontal.lineTo(movePersonnage.midX() + 64, movePersonnage.midY() + 64);
			pathLineHorizontal.lineTo(movePersonnage.midX(), movePersonnage.midY() + 64);
			pathLineHorizontal.lineTo(movePersonnage.midX(), movePersonnage.midY());

			pathLineHorizontal.close();
			pathLineHorizontal.setStrokeColor(ofColor::red);
			pathLineHorizontal.setFilled(false);
			pathLineHorizontal.setStrokeWidth(1);


		}

		// Si une récolte est en cours
		if (actionRecolteActive) {
			actionRecolteActive = movePersonnage.actionRecolteEnd();
		}

		// fait spawn du zombis toutes les 15 sec
		if (tpsSpawnZombi - ofGetElapsedTimeMillis() > timerSpawnZombi) {
			for (int i = 0; i < maxZombi; i++) {
				// si cette unité n'est pas affecté
				if (!zombis[i].isSpawnZombi) {
					zombis[i].spawnZombi();
				}
			}
		}

		// effectue les traitements sur les zombis
		for (int i = 0; i < maxZombi; i++) {
			// si cette unité n'est pas affecté
			if (zombis[i].isSpawnZombi) {
				zombis[i].moveZombi();
			}
			// si un zombi est a distance action joueur = attaqué
			if (playerCurrentAction != "degat" && zombis[i].distanceBetweenPLayerAndZombi() <= 32 && zombis[i].isSpawnZombi){
				// metes l'action joueur en degat s'il n'y est pas.
				playerCurrentAction = "degat";
			}
		}
	}
	//mouvements des nuages
	for (int i = 0; i <= 49; i++) {
		
		lancementMeteo[i].majNuage();
	}
	//mouvement de la pluie
	lancementPluie.MajPluie();
	

	


		// gestion des projectiles
		for(int i = 0; i<5; i++) {
			if (projectile[i].isActive) {
				printf("Projectile[%d] (Active)\n", i);
				projectile[i].updatePosition();
			}
		}

}

//--------------------------------------------------------------
void ofApp::draw(){

	// affiche a l'écran
	gestionMap.displayMap();
	
	if (affInventaire) {
		inventaire.affichage();
		font.drawString(strSurvolInventaire, inventaire.returnPosXWindow() + 225, inventaire.returnPosYWindow()+290);
	} else {

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

		for (int i = 0; i<maxZombi; i++) {
			// si cette unité n'est pas affecté
			if (zombis[i].isSpawnZombi) {
				if(zombis[i].getAnimMort()==false)
				zombis[i].displayZombi();
			}
		}
		//Meteo
		//nuage
		for (int i = 0; i <= 49; i++)
		{
			lancementMeteo[i].dessineNuage();
		}
		//orage
		
			lancementPluie.TombePluie();
		
		// barre de vie, sprint et energie
		barreDeVie.displayBarreVie();

		// gestion des projectiles
		for (int i = 0; i<5; i++) {
			if (projectile[i].isActive) {
				projectile[i].displayProjectile();
			}
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
	
	// affiche les message d'aide au survol de l'intaire
	if (affInventaire && x>inventaire.returnPosXWindow() && x<inventaire.returnPosXWindow() + 1024 && y>inventaire.returnPosYWindow() && y<inventaire.returnPosYWindow() + 642) {
		
		if (x>inventaire.returnPosXWindow() + 225 && x<inventaire.returnPosXWindow() + 280 &&
			y>inventaire.returnPosYWindow() + 325 && y<inventaire.returnPosYWindow() + 380) {
			strSurvolInventaire = "Votre stock de bois";
		} else if (x>inventaire.returnPosXWindow() + 298 && x<inventaire.returnPosXWindow() + 353 &&
			y>inventaire.returnPosYWindow() + 325 && y<inventaire.returnPosYWindow() + 380) {
			strSurvolInventaire = "Votre stock de roche";
		} else if (x>inventaire.returnPosXWindow() + 371 && x<inventaire.returnPosXWindow() + 426 &&
			y>inventaire.returnPosYWindow() + 325 && y<inventaire.returnPosYWindow() + 380) {
			strSurvolInventaire = "Balancez les sur les zombies !";
		} else if (x>inventaire.returnPosXWindow() + 444 && x<inventaire.returnPosXWindow() + 499 &&
			y>inventaire.returnPosYWindow() + 325 && y<inventaire.returnPosYWindow() + 380) {
			strSurvolInventaire = "Balancez les sur les zombies !";
		} else if (x>inventaire.returnPosXWindow() + 517 && x<inventaire.returnPosXWindow() + 572 &&
			y>inventaire.returnPosYWindow() + 325 && y<inventaire.returnPosYWindow() + 380) {
			strSurvolInventaire = "Balancez les sur les zombies !";
		} else if (x>inventaire.returnPosXWindow() + 590 && x<inventaire.returnPosXWindow() + 645 &&
			y>inventaire.returnPosYWindow() + 325 && y<inventaire.returnPosYWindow() + 380) {
			strSurvolInventaire = "5 Pierres pour 1 roche, cliquez pour construire";
		} else if (x>inventaire.returnPosXWindow() + 663 && x<inventaire.returnPosXWindow() + 718 &&
			y>inventaire.returnPosYWindow() + 325 && y<inventaire.returnPosYWindow() + 380) {
			strSurvolInventaire = "5 Lances pour 1 bois, cliquez pour construire";
		} else {
			strSurvolInventaire="";
		}

	}

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
	if (affInventaire && ( x<inventaire.returnPosXWindow() || x>inventaire.returnPosXWindow()+1024 || y<inventaire.returnPosYWindow() || y>inventaire.returnPosYWindow()+642) ){
		affInventaire = false;
	// clic dans l'inventaire pour la construction
	} else if (affInventaire && x>inventaire.returnPosXWindow() && x<inventaire.returnPosXWindow() + 1024 && y>inventaire.returnPosYWindow() && y<inventaire.returnPosYWindow() + 642 ) {
		
		if ( x>inventaire.returnPosXWindow() + 590 && x<inventaire.returnPosXWindow() + 648 &&
		     y>inventaire.returnPosYWindow() + 325 && y<inventaire.returnPosYWindow() + 380 ){
			inventaire.fabriqueRoche();
		} else if (x>inventaire.returnPosXWindow() + 663 && x<inventaire.returnPosXWindow() + 718 &&
			y>inventaire.returnPosYWindow() + 325 && y<inventaire.returnPosYWindow() + 380) {
			inventaire.fabriqueLance();
		}

	} else {
	
		// init projectile
		for (int i = 0; i<5; i++) {

			string retour = "[";
			retour += i;
			(projectile[i].isActive)?retour+="] Active\n" : retour+=" ] NON actif\n";
			//printf("%s",retour);
			if (!projectile[i].isActive){
				projectile[i].initDirectionProjectile(x,y);
				break;
			}
		}

	
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
