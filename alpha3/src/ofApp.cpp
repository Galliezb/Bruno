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

	
	//lancement initiation Menu dans le jeu
	LancementMenuInGame.InitInGameMenu();
	//lancement initiation De la barre de musique du menu dans le jeu
	LancementMenuInGame.initBarreMusique();
}


//--------------------------------------------------------------
void ofApp::update() {
	//Musique
	musique.changeVolume(LancementMenuInGame.volA);
	if (affInventaire) {
		inventaire.affichage();
	}
	else {

		// si le joueur a bougé, on met à jour l'info
		if (playerHasMove) {
			// Gestion des colisions INTEGRE avec les objets présent et les cases d'eau
			movePersonnage.updatePositionJoueur();

			// Le quadrillage Horizontal
			/*
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
			*/

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
				
				if ( !projectile[i].isHitZombie ){
					projectile[i].updatePosition();
				}

				// gère les collisions avec les zombis
				if (projectile[i].isActive){
					for (int j = 0; j < maxZombi; j++) {
						// collision Zombie
						if (zombis[j].isSpawnZombi && !projectile[i].isHitZombie && abs( zombis[j].posXZombi - projectile[i].positionXOnTheMap ) < 24 && abs(zombis[j].posYZombi - projectile[i].positionYOnTheMap) < 24) {
							//printf("collision zombie \n");
							projectile[i].isHitZombie = true;
							projectile[i].posXZombieHit = zombis[j].posXZombi;
							projectile[i].posYZombieHit = zombis[j].posYZombi;
						// collision Roche ou arbre
						// une fonction de classe qui retourne l'index voulu, c'est cool non ?
					}
					else if (tabContentCase[projectile[i].returnIndexOfCase()] == 1 || tabContentCase[projectile[i].returnIndexOfCase()] == 2) {
						projectile[i].isActive = false;
					}
				}
			}

		}
	}

		//Tout ça gère le fait que quand il pleut : musique d'horreur!
		
	if (lancementPluie.pleutIl() == true) {
		musique.setStoppedForRain(true);
		if (musique.getStoppedForRain() == true && cptmusique==0) {
			musique.setMusicOff();
			cptmusique = 1;
		}
	}
	else if (lancementPluie.pleutIl()==false){
		musique.setStoppedForRain(false);
		musique.setMusicOff();
		cptmusique = 0;
	}

	//update du menu dans le jeu
	LancementMenuInGame.MenuMajInGame();
	//update de la barre de Musique et ambiance dans le menu jeu
	LancementMenuInGame.majBarreMusique();


}

//--------------------------------------------------------------
void ofApp::draw(){

	// affiche a l'écran
	gestionMap.displayMap();
	
	if (affInventaire && affMenuInGame==false) {
		inventaire.affichage();
		font.drawString(strSurvolInventaire, inventaire.returnPosXWindow() + 225, inventaire.returnPosYWindow()+290);
	}
	else if(affInventaire == false && affMenuInGame == true) {
		//dessine le menu dans le jeu
		LancementMenuInGame.inGame();
		//dessine les barre dans le menu dans le jeu
		LancementMenuInGame.dessineBarreMusique();
	}
	else {

		// affichage du personnage
		movePersonnage.movePlayer();
		/*
		string fpsStr = "positionJoueurX => " + ofToString(positionJoueurX);
		ofDrawBitmapString(fpsStr, 20, 100);
		fpsStr = "positionJoueurY => " + ofToString(positionJoueurY);
		ofDrawBitmapString(fpsStr, 20, 125);
		fpsStr = "positionCameraX => " + ofToString(positionJoueurX - widthScreen / 2);
		ofDrawBitmapString(fpsStr, 20, 150);
		fpsStr = "positionCameraY => " + ofToString(positionJoueurY - heightScreen / 2);
		ofDrawBitmapString(fpsStr, 20, 175);
		fpsStr = "Origin: " + ofToString(positionJoueurX / 64) + ";" + ofToString(positionJoueurY / 64);
		ofDrawBitmapString(fpsStr, 20, 200);
		fpsStr = "Origin(pied): " + ofToString((positionJoueurX + 32) / 64) + ";" + ofToString((positionJoueurY + 60) / 64);
		ofDrawBitmapString(fpsStr, 20, 225);
		pathLineHorizontal.draw();
		*/

		for (int i = 0; i < maxZombi; i++) {
			// si cette unité n'est pas affecté
			if (zombis[i].isSpawnZombi) {
				if (zombis[i].getAnimMort() == false)
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
		for (int i = 0; i < 5; i++) {
			if (projectile[i].isActive) {

				projectile[i].displayProjectile();

				//Affichage HIT ZOMBIE ! DANS TA ***BIP*** LE ZOMBIE !
				if ( projectile[i].isHitZombie ){
					projectile[i].drawHitSangZombie();
				}

			}
		}
	}
	//Ceci permet que lorsqu'on clique sur retour Jeu le menu s'arrête bien et le menu ne fait pas laguer
	if (affMenuInGame == true)
	{
		if (LancementMenuInGame.retourJeu == false)
		{
			affMenuInGame = false;
		}
	}
	if (LancementMenuInGame.clavierlancer)
	{
		font.drawString(strSurvolTouche,ofGetWindowWidth()/2-200,ofGetWindowHeight()/2-120);
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
	
	switch (key){
		case 'g':
			musique.nextMusic("Ambient");
			break;
		case 'h':
			musique.nextMusic("Horror");
			break;
		case 'j':
			musique.nextMusic("ZA");
			break;
		case 'i':
			if (affMenuInGame == false) {
				inventaire.affichage();
				affInventaire = !affInventaire;
			}
			break;
		case 'f':
			ofToggleFullscreen();
			break;
			//menu dans le jeu
		case 'n':
			if (affInventaire == false) {
				//dessine le menu dans le jeu
				LancementMenuInGame.inGame();
				//dessine les barre dans le menu dans le jeu
				LancementMenuInGame.dessineBarreMusique();
				affMenuInGame = !affMenuInGame;
				LancementMenuInGame.retourJeu = true;
				if (LancementMenuInGame.clavierlancer)
				{
					LancementMenuInGame.clavierlancer = false;
					LancementMenuInGame.goMenuJeu = true;
					LancementMenuInGame.retourJeu = true;
				}
				if (LancementMenuInGame.statMenuLancer)
				{
					LancementMenuInGame.statMenuLancer = false;
					LancementMenuInGame.goMenuJeu = true;
					LancementMenuInGame.retourJeu = true;
				}
			}
			break;
	}
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
	if (LancementMenuInGame.clavierlancer)
	{
		if (x > ofGetWindowWidth() / 2  -640+170 && x<ofGetWindowWidth() / 2 - 640 + 220 && y > ofGetWindowHeight() / 2 - 360+280 && y<ofGetWindowHeight() / 2 - 360 + 330)
		{
			strSurvolTouche = "Quitter le menu";
		}
		else if (x > ofGetWindowWidth() / 2 - 640 + 770 && x<ofGetWindowWidth() / 2 - 640 + 840 && y > ofGetWindowHeight() / 2 - 360 + 540 && y < ofGetWindowHeight() / 2 - 360 + 585)
		{
			strSurvolTouche = "Aller a gauche";
		}
		else if (x > ofGetWindowWidth() / 2 - 640 + 860 && x<ofGetWindowWidth() / 2 - 640 + 930 && y > ofGetWindowHeight() / 2 - 360 + 540 && y < ofGetWindowHeight() / 2 - 360 + 585)
		{
			strSurvolTouche = "Aller en haut";
		}
		else if (x > ofGetWindowWidth() / 2 - 640 + 950 && x<ofGetWindowWidth() / 2 - 640 + 1020&& y > ofGetWindowHeight() / 2 - 360 + 540 && y < ofGetWindowHeight() / 2 - 360 + 585)
		{
			strSurvolTouche = "Aller en bas";
		}
		else if (x > ofGetWindowWidth() / 2 - 640 + 1040 && x<ofGetWindowWidth() / 2 - 640 + 1110 && y > ofGetWindowHeight() / 2 - 360 + 540 && y < ofGetWindowHeight() / 2 - 360 + 585)
		{
			strSurvolTouche = "Aller a droite";
		}
		else 
		{
			strSurvolTouche = "";
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
		// si le joueur a des ressources à lancer
		if ( projectile[0].playerHaveEnoughRessource() ){
			// init projectile
			for (int i = 0; i<5; i++) {
				/*
				string retour = "[";
				retour += i;
				(projectile[i].isActive)?retour+="] Active\n" : retour+=" ] NON actif\n";
				printf("%s",retour);
				*/
				if (!projectile[i].isActive){
					projectile[i].initDirectionProjectile(x,y);
					break;
				}
			}
		} else {
			projectile[0].needAmmoSound();
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
