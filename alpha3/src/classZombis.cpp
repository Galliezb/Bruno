#pragma once
#include "classZombis.h"

ClassZombi::ClassZombi(){
	zombiMarche.load("animmarchezombi.png");
	zombiAttaque.load("animattaquezombi.png");
}

void ClassZombi::init(int *ptrPositionJoueurX, int *ptrPositionJoueurY, int *ptrWidthScreen, int *ptrHeightScreen, int *ptrTabContentCase, int *ptrTabContentTerrain){

	this->ptrPositionJoueurX = ptrPositionJoueurX;
	this->ptrPositionJoueurY = ptrPositionJoueurY;
	this->ptrWidthScreen = ptrWidthScreen;
	this->ptrHeightScreen = ptrHeightScreen;
	this->ptrTabContentCase = ptrTabContentCase;
	this->ptrTabContentTerrain = ptrTabContentTerrain;

}

void ClassZombi::displayZombi() {

	// *positionJoueurX, *positionJoueurY affiche le coin haut gauche de la caméra
	// Bizarrement le joueur est affiché à la moitié de l'écran +32 pixel ?

	// en dehors de la caméra, on affiche pas
	if ( posAffichageX() != -1 && posAffichageY() != -1 ){

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
		} else {
			displayAttackZombi();
		}
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
	
	/************************* AXE Y *************************/
	if (*ptrPositionJoueurY > posYZombi) {
		posYZombi += speedZombi;
		boolMoveZombiDown = true;
		boolMoveZombiLeft = false;
		boolMoveZombiRight = false;
		boolMoveZombiTop = false;
	} else if (*ptrPositionJoueurY < posYZombi) {
		posYZombi -= speedZombi;
		boolMoveZombiDown = false;
		boolMoveZombiLeft = false;
		boolMoveZombiRight = false;
		boolMoveZombiTop = true;
	}

	/************************* AXE X *************************/
	// après pour écraser les booléen si nécessaire
	if (*ptrPositionJoueurX > posXZombi) {
		posXZombi += speedZombi;
		boolMoveZombiDown = false;
		boolMoveZombiLeft = false;
		boolMoveZombiRight = true;
		boolMoveZombiTop = false;
	}
	else if (*ptrPositionJoueurX < posXZombi) {
		posXZombi -= speedZombi;
		boolMoveZombiDown = false;
		boolMoveZombiLeft = true;
		boolMoveZombiRight = false;
		boolMoveZombiTop = false;
	}

}
void ClassZombi::setTimerStart() {
	tpsStart = ofGetElapsedTimeMillis();
}
int ClassZombi::getDiffTime() {
	return ofGetElapsedTimeMillis() - tpsStart;
}
int ClassZombi::posAffichageX() {

	// si la position X du zombi est supérieur a la caméra
	// et la position du zombi inférieur à la camera + widthscree
	// alors on l'affiche a l'écran
	if ( posXZombi > *ptrPositionJoueurX && posXZombi < *ptrPositionJoueurX ){
		return *ptrPositionJoueurX - posXZombi;
	} else {
		// donc on affiche pas
		return -1;
	}

}
int ClassZombi::posAffichageY() {

	if (posYZombi > *ptrPositionJoueurY && posYZombi < *ptrPositionJoueurY) {
		return *ptrPositionJoueurY - posYZombi;
	}
	else {
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
	isSpawnZombi = true;
}
