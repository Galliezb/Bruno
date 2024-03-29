#pragma once
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
	//initialisation du menu et du logo
	lancementChargement.initiation();

	soundMenu.loadSound("musiqueMenu.mp3");
	soundMenu.setLoop("true");
	font2.load("arialR.ttf", 15);
	// r�glage du framerate
	ofSetFrameRate(30);

	// J'veux tout savoir sur les logs ! Oui on est fou et on aime �a :D
	ofSetLogLevel(OF_LOG_VERBOSE);

	// taille de l'�cran client
	widthScreen = ofGetWindowWidth();
	heightScreen = ofGetWindowHeight();


	// C'est la position actuel de l'origin 0 - 0 = haut coin haut gauche.
	positionJoueurX = 384;
	positionJoueurY = 384;


	// initialisation des classes ( pour passer les valeurs par pointeur surtout )
	// map
	gestionMap.init(&positionJoueurX,&positionJoueurY,&widthScreen,&heightScreen, tabContentCase, tabContentTerrain);
	// animation personnage
	movePersonnage.init(&positionJoueurX, &positionJoueurY,&widthScreen, &heightScreen, &playerCurrentAction, tabContentCase, tabContentTerrain, tabContentRessourcePlayer, &gestionMap, &barreDeVie, &hautFait);
	movePersonnage.setTimerStart();
	// inventaire
	inventaire.init(tabContentRessourcePlayer, &widthScreen, &heightScreen);
	// zombis
	for (int i=0; i<maxZombi; i++){
		zombis[i].init(&positionJoueurX, &positionJoueurY, &widthScreen, &heightScreen, tabContentCase, tabContentTerrain, &playerCurrentAction, zombis, &maxZombi, &barreDeVie, &hautFait, tabContentRessourcePlayer);
	}

	// init gestion des barre
	barreDeVie.init(&widthScreen, &heightScreen, &playerCurrentAction);
	font.load("arialR.ttf", 15);

	//init gestion des m�teo
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

	// lancement des haut faits
	hautFait.init();
	popup.initPopUp();
	hautFait.theGameHasStarted();
	// lancement du "menu" dans stat � la fin du jeu pour rejouer ou quitter
	lancementRejouerQuitter.initBoutonStatistique();
	
	setTimerStart();
}



//--------------------------------------------------------------
void ofApp::update() {
	//lancement du logo vers le menu
	lancementChargement.maj();
	if (lancementMenu.leJeuSeLance == false) {
		if (playerCurrentAction == "mort") {
			playerHasMove = false;
			playerMoveDown = false;
			playerMoveRight = false;
			playerMoveLeft = false;
			playerMoveTop = false;
		}
		if (speedTest == true) {
			barreDeVie.modifiePointDeSprint(-2);
		}
		else if (ofGetElapsedTimeMillis() - tpsTimerRechargeSprint > 1000) {
			barreDeVie.modifiePointDeSprint(10);
			tpsTimerRechargeSprint = ofGetElapsedTimeMillis();

		}
		
		
		// si le joueur est pas mort
		if (hautFait.getDrawStats() == false) {

			//Musique
			musique.changeVolume(LancementMenuInGame.volA);
			if (affInventaire) {
				inventaire.affichage();
			}
			else {

				// si le joueur a boug�, on met � jour l'info
				if (playerHasMove) {
					// Gestion des colisions INTEGRE avec les objets pr�sent et les cases d'eau
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

				// Si une r�colte est en cours
				if (actionRecolteActive) {
					actionRecolteActive = movePersonnage.actionRecolteEnd();
				}

				// fait spawn du zombis toutes les 15 sec
				if (ofGetElapsedTimeMillis() - tpsSpawnZombi  > timerSpawnZombi) {
					for (int i = 0; i < maxZombi; i++) {
						// si cette unit� n'est pas affect�
						if (!zombis[i].isSpawnZombi) {
						printf("\n\n\n\nSpawnZombie\n\n\n\n\n");
							zombis[i].spawnZombi();
							tpsSpawnZombi = ofGetElapsedTimeMillis();
							break;
						}
					}
				}

				// effectue les traitements sur les zombis
				for (int i = 0; i < maxZombi; i++) {
					// si cette unit� n'est pas affect�
					if (zombis[i].isSpawnZombi) {
						zombis[i].moveZombi();
					}
					// si un zombi est a distance action joueur = attaqu�
					if (barreDeVie.pointDeVie > 1 && playerCurrentAction != "degat" && zombis[i].distanceBetweenPLayerAndZombi() <= 32 && zombis[i].isSpawnZombi) {
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
			for (int i = 0; i < 5; i++) {
				if (projectile[i].isActive) {

					if (!projectile[i].isHitZombie) {
						projectile[i].updatePosition();
					}

					// g�re les collisions avec les zombis
					if (projectile[i].isActive) {
						for (int j = 0; j < maxZombi; j++) {
							// collision Zombie
							if (zombis[j].isSpawnZombi && !projectile[i].isHitZombie && zombis[j].pointDeVie > 1 && abs(zombis[j].posXZombi - projectile[i].positionXOnTheMap) < 24 && abs(zombis[j].posYZombi - projectile[i].positionYOnTheMap) < 24) {
								//printf("collision zombie \n");
								projectile[i].isHitZombie = true;
								projectile[i].posXZombieHit = zombis[j].posXZombi;
								projectile[i].posYZombieHit = zombis[j].posYZombi;

								// envoi les d�g�ts vers le zombi ( si pdv < 1 animation mort en cours )
								if (zombis[j].pointDeVie > 1) {
									zombis[j].receiveDamage(5);
								}

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

			//Tout �a g�re le fait que quand il pleut : musique d'horreur!

			if (lancementPluie.pleutIl() == true) {
				musique.setStoppedForRain(true);
				if (musique.getStoppedForRain() == true && cptmusique == 0) {
					musique.setMusicOff();
					cptmusique = 1;
				}
			}
			else if (lancementPluie.pleutIl() == false) {
				musique.setStoppedForRain(false);
				musique.setMusicOff();
				cptmusique = 0;
			}

			//update du menu dans le jeu
			LancementMenuInGame.MenuMajInGame();
			//update de la barre de Musique et ambiance dans le menu jeu
			LancementMenuInGame.majBarreMusique();
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	//Draw     utiliser pour le chargement des menus et du logo Ohm Game ainsi que le son du lancement dans logo
	lancementChargement.chargement();
	if (lancementChargement.goMenu == 2) {
		lancementMenu.testAffichage();
		/*if (lancementMenu.son == false)
		{
			soundMenu.stop();
			sonMenuPrincipallancer = true;
		}
		if (sonMenuPrincipallancer || lancementMenu.leJeuSeLance == false) {
			soundMenu.play();
			sonMenuPrincipallancer = false;
		}*/
	}
	//Ecrit au survol dans le menu touche
	if (lancementMenu.lanceOptionTouche == false)
	{
		font2.drawString(strSurvolTouche, ofGetWindowWidth() / 2 - 200, ofGetWindowHeight() / 2 - 120);
	}

	if (lancementMenu.leJeuSeLance == false) {
		lancementMenu.menuPrincipal = false;
		// affiche a l'�cran
		// si le joueur est pas mort
		//if (hautFait.drawStats){printf("drawstat => true\n");} else { printf("drawstat => false\n"); }
		if (hautFait.drawStats == false) {
			gestionMap.displayMap();

			if (affInventaire && affMenuInGame == false) {
				inventaire.affichage();
				font.drawString(strSurvolInventaire, inventaire.returnPosXWindow() + 225, inventaire.returnPosYWindow() + 290);
			}
			else if (affInventaire == false && affMenuInGame == true) {
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
					// si cette unit� n'est pas affect�
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
						if (projectile[i].isHitZombie) {
							projectile[i].drawHitSangZombie();
						}

					}
				}
			}
			//Ceci permet que lorsqu'on clique sur retour Jeu le menu s'arr�te bien et le menu ne fait pas laguer
			if (affMenuInGame == true)
			{
				if (LancementMenuInGame.retourJeu == false)
				{
					affMenuInGame = false;
				}
			}
			if (LancementMenuInGame.clavierlancer)
			{
				font.drawString(strSurvolTouche, ofGetWindowWidth() / 2 - 200, ofGetWindowHeight() / 2 - 120);
			}

			// lance le popup et affichage d'un haut fait
			if (hautFait.returnTest() == true) {
				popup.majPopUp(hautFait.displayTitle(), hautFait.displayDescription());
				popup.drawPopUp();
			}
			if (ofGetElapsedTimeMillis() - hautFait.tpsEntreDeuxHautFait > 3000) {
				hautFait.setBoolTest(false);
			}

			// le joueur est mort on affiche les stats
		}
		else {
			hautFait.drawStatistics();
			
			//dessine les boutons pour le click rejouer ou quitter � la fin du jeu
			lancementRejouerQuitter.ajoutBoutonStatistique();
		}
		if (LancementMenuInGame.statMenuLancer)
		{
			tpsStart = tpsStart / 1000;
			hautFait.howLongTheGameLast(tpsStart);
			hautFait.drawStatistics();
		}
	}

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	// deplacement position joueur + personnage
	ofLogVerbose() << "playercurrentAction => "<< ofToString(playerCurrentAction);
	if ( (key == OF_KEY_UP || key == 'z') && playerCurrentAction!="mort") {
		if ( !playerMoveTop ) { playerMoveTop = true; }
		if ( !playerHasMove ) { playerHasMove = true; }
		if (!movePersonnage.getBoolMovePlayerTop()) { movePersonnage.setBoolMovePlayerTop(true); }
	}
	if ( (key == OF_KEY_RIGHT || key == 'd') && playerCurrentAction != "mort") {
		playerMoveRight = true;
		if (!playerMoveRight) { playerMoveRight = true; }
		if (!playerHasMove) { playerHasMove = true; }
		if (!movePersonnage.getBoolMovePlayerRight()) { movePersonnage.setBoolMovePlayerRight(true); }
	}
	if ( (key == OF_KEY_DOWN || key == 's') && playerCurrentAction != "mort") {
		playerMoveDown = true;
		if (!playerMoveDown) { playerMoveDown = true; }
		if (!playerHasMove) { playerHasMove = true; }
		if (!movePersonnage.getBoolMovePlayerDown()) { movePersonnage.setBoolMovePlayerDown(true); }
	}
	if ( (key == OF_KEY_LEFT || key == 'q') && playerCurrentAction != "mort") {
		playerMoveLeft = true;
		if (!playerMoveLeft) { playerMoveLeft = true; }
		if (!playerHasMove) { playerHasMove = true; }
		if (!movePersonnage.getBoolMovePlayerLeft()) { movePersonnage.setBoolMovePlayerLeft(true); }
	}
	if ( key== OF_KEY_SHIFT){
		
			if (barreDeVie.pointDeSprint > 1) {
				
				movePersonnage.scrollingSpeed = 6;
				barreDeVie.modifiePointDeSprint(-5);
				speedTest = true;
			}
		
	}
	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

	// deplacement position joueur + animation
	if (key == OF_KEY_UP || key == 'z') {
		playerMoveTop = false;
		if (movePersonnage.getBoolMovePlayerTop()) { movePersonnage.setBoolMovePlayerTop(false); }
		if (playerCurrentAction != "mort") {
			playerCurrentAction = "repos";
		}
	}
	if (key == OF_KEY_RIGHT || key == 'd') {
		playerMoveRight = false;
		if (movePersonnage.getBoolMovePlayerRight()) { movePersonnage.setBoolMovePlayerRight(false); }
		if (playerCurrentAction != "mort") {
			playerCurrentAction = "repos";
		}
	}
	if (key == OF_KEY_DOWN || key == 's') {
		playerMoveDown = false;
		if (movePersonnage.getBoolMovePlayerDown()) { movePersonnage.setBoolMovePlayerDown(false); }
		if (playerCurrentAction != "mort") {
			playerCurrentAction = "repos";
		}
	}
	if (key == OF_KEY_LEFT || key == 'q') {
		playerMoveLeft = false;
		if (movePersonnage.getBoolMovePlayerLeft()) { movePersonnage.setBoolMovePlayerLeft(false); }
		if (playerCurrentAction != "mort") {
			playerCurrentAction = "repos";
		}
	}
	if (key == OF_KEY_SHIFT) {
		
			speedTest = false;
		movePersonnage.scrollingSpeed = 1;
		
		
	}
	// si aucun mouvement en cours, on repasse a false pour �viter les traitements.
	if (!playerMoveTop && !playerMoveRight && !playerMoveDown && !playerMoveLeft) { playerHasMove = false; }
	
	switch (key){
		case 'e':
			movePersonnage.actionRecolteStart();
			actionRecolteActive = true;
			break;
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
		if (x > ofGetWindowWidth() / 2  -640+169 && x<ofGetWindowWidth() / 2 - 640 + 169+55 && y > ofGetWindowHeight() / 2 - 360+246 && y<ofGetWindowHeight() / 2 - 360 + 246+29)
		{
			strSurvolTouche = "Quitter le menu";
		}
		else if (x > ofGetWindowWidth() / 2 +283 && x<ofGetWindowWidth() / 2 +338 && y > ofGetWindowHeight() / 2 +188 && y < ofGetWindowHeight() / 2 +243)
		{
			strSurvolTouche = "Gauche";
		}
		else if (x > ofGetWindowWidth() / 2 +416 && x<ofGetWindowWidth() / 2 +471 && y > ofGetWindowHeight() / 2 +189 && y < ofGetWindowHeight() / 2 +244)
		{
			strSurvolTouche = "Droite";
		}
		else if (x > ofGetWindowWidth() / 2 +350 && x<ofGetWindowWidth() / 2+406 && y > ofGetWindowHeight() / 2 +188 && y < ofGetWindowHeight() / 2 -360+ 548+27)
		{
			strSurvolTouche = "Avancer";
		}
		else if (x > ofGetWindowWidth() / 2 - 640 + 990 && x<ofGetWindowWidth() / 2 - 640 + 990+56 && y > ofGetWindowHeight() / 2 - 360 + 577 && y < ofGetWindowHeight() / 2 -360+ 577 + 27)
		{
			strSurvolTouche = "Reculer";
		}
		else if (x > ofGetWindowWidth() / 2 - 640 + 709 && x<ofGetWindowWidth() / 2 - 640 + 709 + 55 && y > ofGetWindowHeight() / 2 - 360 + 349 && y < ofGetWindowHeight() / 2 - 360 + 349 + 55)
		{
			strSurvolTouche = "Inventaire";
		}
		else if (x > ofGetWindowWidth() / 2 - 640 + 1133 && x<ofGetWindowWidth() / 2 - 640 + 1133 + 87 && y > ofGetWindowHeight() / 2 - 360 + 213 && y < ofGetWindowHeight() / 2 - 360 + 213 + 113)
		{
			strSurvolTouche = "lancer de projectile";
		}
		else if (x > ofGetWindowWidth() / 2 - 640 + 312 && x<ofGetWindowWidth() / 2 - 640 + 312 + 55 && y > ofGetWindowHeight() / 2 - 360 + 351 && y < ofGetWindowHeight() / 2 - 360 + 351 + 55)
		{
			strSurvolTouche = "Avancer";
		}
		else if (x > ofGetWindowWidth() / 2 - 640 + 259 && x<ofGetWindowWidth() / 2 - 640 + 259 + 55 && y > ofGetWindowHeight() / 2 - 360 + 417 && y < ofGetWindowHeight() / 2 - 360 + 417 + 55)
		{
			strSurvolTouche = "Gauche";
		}
		else if (x > ofGetWindowWidth() / 2 - 640 + 325 && x<ofGetWindowWidth() / 2 - 640 + 325 + 55 && y > ofGetWindowHeight() / 2 - 360 + 417 && y < ofGetWindowHeight() / 2 - 360 + 417 + 55)
		{
			strSurvolTouche = "Reculer";
		}
		else if (x > ofGetWindowWidth() / 2 - 640 + 389 && x<ofGetWindowWidth() / 2 - 640 + 389 + 55 && y > ofGetWindowHeight() / 2 - 360 + 417 && y < ofGetWindowHeight() / 2 - 360 + 417 + 55)
		{
			strSurvolTouche = "Droite";
		}
		else if (x > ofGetWindowWidth() / 2 - 640 + 379 && x<ofGetWindowWidth() / 2 - 640 + 379 + 55 && y > ofGetWindowHeight() / 2 - 360 + 351 && y < ofGetWindowHeight() / 2 - 360 + 351 + 55)
		{
			strSurvolTouche = "Couper/Miner";
		}
		else if (x > ofGetWindowWidth() / 2 - 640 + 455 && x<ofGetWindowWidth() / 2 - 640 + 455 + 55 && y > ofGetWindowHeight() / 2 - 360 + 417 && y < ofGetWindowHeight() / 2 - 360 + 417 + 55)
		{
			strSurvolTouche = "Plein Ecran";
		}
		
		else 
		{
			strSurvolTouche = "";
		}
	}
	//Permet de donner une valeur strSurvolTouche en fonction de la position ou pointe la souris dans le menu Principal
	if (lancementMenu.lanceOptionTouche == false)
	{
		if (x > ofGetWindowWidth() / 2 - 640 + 169 && x<ofGetWindowWidth() / 2 - 640 + 169 + 55 && y > ofGetWindowHeight() / 2 - 360 + 246 && y<ofGetWindowHeight() / 2 - 360 + 246 + 29)
		{
			strSurvolTouche = "Quitter le menu";
		}
		else if (x > ofGetWindowWidth() / 2 + 283 && x<ofGetWindowWidth() / 2 + 338 && y > ofGetWindowHeight() / 2 + 188 && y < ofGetWindowHeight() / 2 + 243)
		{
			strSurvolTouche = "Gauche";
		}
		else if (x > ofGetWindowWidth() / 2 + 416 && x<ofGetWindowWidth() / 2 + 471 && y > ofGetWindowHeight() / 2 + 189 && y < ofGetWindowHeight() / 2 + 244)
		{
			strSurvolTouche = "Droite";
		}
		else if (x > ofGetWindowWidth() / 2 + 350 && x<ofGetWindowWidth() / 2 + 406 && y > ofGetWindowHeight() / 2 + 188 && y < ofGetWindowHeight() / 2 - 360 + 548 + 27)
		{
			strSurvolTouche = "Avancer";
		}
		else if (x > ofGetWindowWidth() / 2 - 640 + 990 && x<ofGetWindowWidth() / 2 - 640 + 990 + 56 && y > ofGetWindowHeight() / 2 - 360 + 577 && y < ofGetWindowHeight() / 2 - 360 + 577 + 27)
		{
			strSurvolTouche = "Reculer";
		}
		else if (x > ofGetWindowWidth() / 2 - 640 + 709 && x<ofGetWindowWidth() / 2 - 640 + 709 + 55 && y > ofGetWindowHeight() / 2 - 360 + 349 && y < ofGetWindowHeight() / 2 - 360 + 349 + 55)
		{
			strSurvolTouche = "Inventaire";
		}
		else if (x > ofGetWindowWidth() / 2 - 640 + 1133 && x<ofGetWindowWidth() / 2 - 640 + 1133 + 87 && y > ofGetWindowHeight() / 2 - 360 + 213 && y < ofGetWindowHeight() / 2 - 360 + 213 + 113)
		{
			strSurvolTouche = "lancer de projectile";
		}
		else if (x > ofGetWindowWidth() / 2 - 640 + 312 && x<ofGetWindowWidth() / 2 - 640 + 312 + 55 && y > ofGetWindowHeight() / 2 - 360 + 351 && y < ofGetWindowHeight() / 2 - 360 + 351 + 55)
		{
			strSurvolTouche = "Avancer";
		}
		else if (x > ofGetWindowWidth() / 2 - 640 + 259 && x<ofGetWindowWidth() / 2 - 640 + 259 + 55 && y > ofGetWindowHeight() / 2 - 360 + 417 && y < ofGetWindowHeight() / 2 - 360 + 417 + 55)
		{
			strSurvolTouche = "Gauche";
		}
		else if (x > ofGetWindowWidth() / 2 - 640 + 325 && x<ofGetWindowWidth() / 2 - 640 + 325 + 55 && y > ofGetWindowHeight() / 2 - 360 + 417 && y < ofGetWindowHeight() / 2 - 360 + 417 + 55)
		{
			strSurvolTouche = "Reculer";
		}
		else if (x > ofGetWindowWidth() / 2 - 640 + 389 && x<ofGetWindowWidth() / 2 - 640 + 389 + 55 && y > ofGetWindowHeight() / 2 - 360 + 417 && y < ofGetWindowHeight() / 2 - 360 + 417 + 55)
		{
			strSurvolTouche = "Droite";
		}
		else if (x > ofGetWindowWidth() / 2 - 640 + 379 && x<ofGetWindowWidth() / 2 - 640 + 379 + 55 && y > ofGetWindowHeight() / 2 - 360 + 351 && y < ofGetWindowHeight() / 2 - 360 + 351 + 55)
		{
			strSurvolTouche = "Couper/Miner";
		}
		else if (x > ofGetWindowWidth() / 2 - 640 + 455 && x<ofGetWindowWidth() / 2 - 640 + 455 + 55 && y > ofGetWindowHeight() / 2 - 360 + 417 && y < ofGetWindowHeight() / 2 - 360 + 417 + 55)
		{
			strSurvolTouche = "Plein Ecran";
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

	if (ofGetMousePressed()) {
		//Classe MenuMain Touche et Cr�dit pour le retour vers le menu principal
		if (lancementMenu.lanceCredit == false) {
			lancementMenu.lanceCredit = true;
		}
		if (lancementMenu.lanceOptionTouche == false)
		{
			lancementMenu.lanceOptionTouche = true;
		}
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	// inventaire affich�, si clique en dehors, on stop l'affichage
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
		// si le joueur a des ressources � lancer
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

void ofApp::setTimerStart() {
	tpsStart = ofGetElapsedTimeMillis();
}