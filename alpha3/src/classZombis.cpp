#pragma once
#include "classZombis.h"


ClassZombi::ClassZombi(){
	zombiMarche.load("animmarchezombi.png");
	zombiAttaque.load("animattaquezombi.png");
}

void ClassZombi::init(int *ptrPositionJoueurX, int *ptrPositionJoueurY, int *ptrWidthScreen, int *ptrHeightScreen, int *ptrTabContentCase, int *ptrTabContentTerrain, string *ptrPlayerCurrentAction){

	this->ptrPositionJoueurX = ptrPositionJoueurX;
	this->ptrPositionJoueurY = ptrPositionJoueurY;
	this->ptrWidthScreen = ptrWidthScreen;
	this->ptrHeightScreen = ptrHeightScreen;
	this->ptrTabContentCase = ptrTabContentCase;
	this->ptrTabContentTerrain = ptrTabContentTerrain;
	this->ptrPlayerCurrentAction = ptrPlayerCurrentAction;

}

void ClassZombi::displayZombi() {

	// rectangle autour du joueur
	ofSetColor(255,0,0);
	ofDrawRectangle(posAffichageX(),posAffichageY(),64,64);
	ofNoFill();
	ofSetColor(255, 255, 255);
		

	// *positionJoueurX, *positionJoueurY affiche le coin haut gauche de la caméra
	// Bizarrement le joueur est affiché à la moitié de l'écran +32 pixel ?
	// en dehors de la caméra, on affiche pas
	
	
	
	if ( posAffichageX() != -1 && posAffichageY() != -1 && distanceBetweenPLayerAndZombi() > 32){

		// Right and left prioritaire !
		if (boolMoveZombiLeft == true) {

			zombiMarche.drawSubsection(posAffichageX(), posAffichageY(), 64, 64, 64 * startCycleAnimationLeft, 0, 64, 64);
			if (getDiffTime() > speedAnim) {
				startCycleAnimationLeft++;
				setTimerStart();
			}
			if (startCycleAnimationLeft == 64) { startCycleAnimationLeft = 48; }

		}else if (boolMoveZombiRight == true) {

			zombiMarche.drawSubsection(posAffichageX(), posAffichageY(), 64, 64, 64 * startCycleAnimationRight, 0, 64, 64);
			if (getDiffTime() > speedAnim) {
				startCycleAnimationRight++;
				setTimerStart();
			}
			if (startCycleAnimationRight == 32) { startCycleAnimationRight = 16; }


		}else if (boolMoveZombiTop == true) {

			zombiMarche.drawSubsection(posAffichageX(), posAffichageY(), 64, 64, 64 * startCycleAnimationTop, 0, 64, 64);
			if (getDiffTime() > speedAnim) {
				startCycleAnimationTop++;
				setTimerStart();
			}
			if (startCycleAnimationTop == 16) { startCycleAnimationTop = 0; }

		}else if (boolMoveZombiDown == true) {

			zombiMarche.drawSubsection(posAffichageX(), posAffichageY(), 64, 64, 64 * startCycleAnimationDown, 0, 64, 64);
			if (getDiffTime() > speedAnim) {
				startCycleAnimationDown++;
				setTimerStart();
			}
			if (startCycleAnimationDown == 48) { startCycleAnimationDown = 32; }
			//Animation repos
		}

	} else if (distanceBetweenPLayerAndZombi() <= 32) {
		displayAttackZombi();
	}
}
// Gère les animations du personnage au repos.
void ClassZombi::displayAttackZombi() {
		
	// Right and left prioritaire !
	if (lastmoveRight == true) {
		zombiAttaque.drawSubsection(posAffichageX(), posAffichageY(), 64, 64, 64 * startCycleAnimationRight, 0, 64, 64);

		if (getDiffTime() > speedAnim) {
			startCycleAnimationRight++;
			setTimerStart();
		}
		if (startCycleAnimationRight == 32) { startCycleAnimationRight = 16; }


	}else if (lastmoveLeft == true) {
		zombiAttaque.drawSubsection(posAffichageX(), posAffichageY(), 64, 64, 64 * startCycleAnimationLeft, 0, 64, 64);
		if (getDiffTime() > speedAnim) {
			startCycleAnimationLeft++;
			setTimerStart();
		}
		if (startCycleAnimationLeft == 64) { startCycleAnimationLeft = 48; }


	}else if (lastmoveTop == true) {
		zombiAttaque.drawSubsection(posAffichageX(), posAffichageY(), 64, 64, 64 * startCycleAnimationTop, 0, 64, 64);
		if (getDiffTime() > speedAnim) {
			startCycleAnimationTop++;
			setTimerStart();
		}
		if (startCycleAnimationTop == 16) { startCycleAnimationTop = 0; }

		// position repos de base, face vers l'utilisateur pardi !
	}else {
		zombiAttaque.drawSubsection(posAffichageX(), posAffichageY(), 64, 64, 64 * startCycleAnimationDown, 0, 64, 64);
		if (getDiffTime() > speedAnim) {
			startCycleAnimationDown++;
			setTimerStart();
		}
		if (startCycleAnimationDown == 48) { startCycleAnimationDown = 32; }

	}

}
void ClassZombi::moveZombi(){
	
	// s'il est a portée, attaque, donc plus de déplacement.
	if (distanceBetweenPLayerAndZombi() > 32){
		/************************* AXE Y *************************/
		if (*ptrPositionJoueurY > posYZombi) {

			posYZombi += speedZombi;

			boolMoveZombiDown = true;
			boolMoveZombiLeft = false;
			boolMoveZombiRight = false;
			boolMoveZombiTop = false;

			lastmoveRight = true;
			lastmoveLeft = false;
			lastmoveTop = false;
			lastmoveDown = false;


		} else if (*ptrPositionJoueurY < posYZombi) {

			posYZombi -= speedZombi;

			boolMoveZombiDown = false;
			boolMoveZombiLeft = false;
			boolMoveZombiRight = false;
			boolMoveZombiTop = true;

			lastmoveRight = false;
			lastmoveLeft = false;
			lastmoveTop = true;
			lastmoveDown = false;


		}

		/************************* AXE X *************************/
		// après pour écraser les booléen si nécessaire
		if (*ptrPositionJoueurX > posXZombi) {

			posXZombi += speedZombi;

			boolMoveZombiDown = false;
			boolMoveZombiLeft = false;
			boolMoveZombiRight = true;
			boolMoveZombiTop = false;

			lastmoveRight = true;
			lastmoveLeft = false;
			lastmoveTop = false;
			lastmoveDown = false;


		}else if (*ptrPositionJoueurX < posXZombi) {

			posXZombi -= speedZombi;

			boolMoveZombiDown = false;
			boolMoveZombiLeft = true;
			boolMoveZombiRight = false;
			boolMoveZombiTop = false;

			lastmoveRight = false;
			lastmoveLeft = true;
			lastmoveTop = false;
			lastmoveDown = false;


		}
	}
}
void ClassZombi::setTimerStart() {
	tpsStart = ofGetElapsedTimeMillis();
}
int ClassZombi::getDiffTime() {
	return ofGetElapsedTimeMillis() - tpsStart;
}
int ClassZombi::posAffichageX() {

	//position par défaut de la caméra : *ptrPositionJoueurX + 32 - *ptrWidthScreen / 2;
	int posXcamera = *ptrPositionJoueurX + 32 - *ptrWidthScreen / 2;
	if (posXcamera<1) {
		posXcamera= 0;
	} else if (posXcamera> 7680 - *ptrWidthScreen) {
		posXcamera = 7680 - *ptrWidthScreen;
	}


	if ( posXZombi > posXcamera && posXZombi < posXcamera +*ptrWidthScreen ){

		// par defaut posZombi - cote gauche de l'affichage
		return posXZombi - posXcamera;

	} else {
		// donc on affiche pas
		return -1;
	}

}
int ClassZombi::posAffichageY() {

	int posYcamera = *ptrPositionJoueurY + 32 - *ptrHeightScreen / 2;
	if (posYcamera<1) {
		posYcamera = 0;
	}
	else if (posYcamera> 5120 - *ptrHeightScreen) {
		posYcamera = 5120 - *ptrHeightScreen;
	}


	if (posYZombi > posYcamera && posYZombi < posYcamera+*ptrHeightScreen) {

		// par defaut posZombi - cote haut de l'affichage
		return posYZombi-posYcamera;

	} else {
		// donc on affiche pas
		return -1;
	}

}
void ClassZombi::spawnZombi(){

	int x = ofRandom(1000);
	int y = ofRandom(1000);
	// on fait spawn en dehors de la carte
	posXZombi = 7680+x;
	posYZombi = 5120+y;
	posXZombi = 1250;
	posYZombi = 1250;
	isSpawnZombi = true;
}
int ClassZombi::distanceBetweenPLayerAndZombi(){
	
	int ecartX,ecartY;

	if (*ptrPositionJoueurX < posXZombi){
		ecartX = posXZombi - *ptrPositionJoueurX;
	} else {
		ecartX = *ptrPositionJoueurX - posXZombi;
	}

	if (*ptrPositionJoueurY < posYZombi) {
		ecartY = posYZombi - *ptrPositionJoueurY;
	} else {
		ecartY = *ptrPositionJoueurY - posYZombi;
	}

	return ecartX+ecartY; 

}