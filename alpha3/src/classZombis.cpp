#pragma once
#include "classZombis.h"


ClassZombi::ClassZombi(){
	zombiMarche.load("animmarchezombi.png");
	zombiAttaque.load("animattaquezombi.png");
	zombiMort.load("animmortzombi.png");

	pointDeVie=25;
}

void ClassZombi::init(int *ptrPositionJoueurX, int *ptrPositionJoueurY, int *ptrWidthScreen, int *ptrHeightScreen, int *ptrTabContentCase, int *ptrTabContentTerrain, string *ptrPlayerCurrentAction, ClassZombi *ptrTabZombis, int *ptrMaxIndexPtrTabZombis, BarreDeVie *ptrInstancebarreDeVie, Stats *ptrInstanceStats, int *ptrTabContentRessourcePlayer){

	this->ptrPositionJoueurX = ptrPositionJoueurX;
	this->ptrPositionJoueurY = ptrPositionJoueurY;
	this->ptrWidthScreen = ptrWidthScreen;
	this->ptrHeightScreen = ptrHeightScreen;
	this->ptrTabContentCase = ptrTabContentCase;
	this->ptrTabContentTerrain = ptrTabContentTerrain;
	this->ptrPlayerCurrentAction = ptrPlayerCurrentAction;
	this->ptrTabZombis = ptrTabZombis;
	this->ptrMaxIndexPtrTabZombis = ptrMaxIndexPtrTabZombis;
	this->ptrInstanceStats = ptrInstanceStats;
	// instance barre de vie
	this->ptrInstancebarreDeVie = ptrInstancebarreDeVie;
	this->ptrTabContentRessourcePlayer = ptrTabContentRessourcePlayer;
}

void ClassZombi::displayZombi() {

	// rectangle autour du zombie
	/*
	ofSetColor(255,0,0);
	ofDrawRectangle(posAffichageX(),posAffichageY(),64,64);
	ofNoFill();
	ofSetColor(255, 255, 255);
	*/
		

	// *positionJoueurX, *positionJoueurY affiche le coin haut gauche de la caméra
	// Bizarrement le joueur est affiché à la moitié de l'écran +32 pixel ?
	// en dehors de la caméra, on affiche pas
	
	if (AnimMortEnCours) {
		AnimDeathZombie();
	}
	else if ( posAffichageX() != -1 && posAffichageY() != -1 && distanceBetweenPLayerAndZombi() > 32){
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

			if (startCycleAnimationRight == 17) {
				ptrInstancebarreDeVie->modifiePointDeVie(damage);
			}

		}
		if (startCycleAnimationRight == 32) { startCycleAnimationRight = 16; }


	}else if (lastmoveLeft == true) {
		zombiAttaque.drawSubsection(posAffichageX(), posAffichageY(), 64, 64, 64 * startCycleAnimationLeft, 0, 64, 64);
		if (getDiffTime() > speedAnim) {
			startCycleAnimationLeft++;
			setTimerStart();

			if (startCycleAnimationLeft == 49) {
				ptrInstancebarreDeVie->modifiePointDeVie(damage);
			}

		}
		if (startCycleAnimationLeft == 64) { startCycleAnimationLeft = 48; }


	}else if (lastmoveTop == true) {
		zombiAttaque.drawSubsection(posAffichageX(), posAffichageY(), 64, 64, 64 * startCycleAnimationTop, 0, 64, 64);
		if (getDiffTime() > speedAnim) {
			startCycleAnimationTop++;
			setTimerStart();

			if (startCycleAnimationTop == 1) {
				ptrInstancebarreDeVie->modifiePointDeVie(damage);
			}

		}
		if (startCycleAnimationTop == 16) { startCycleAnimationTop = 0; }

		// position repos de base, face vers l'utilisateur pardi !
	}else {
		zombiAttaque.drawSubsection(posAffichageX(), posAffichageY(), 64, 64, 64 * startCycleAnimationDown, 0, 64, 64);
		if (getDiffTime() > speedAnim) {
			startCycleAnimationDown++;
			setTimerStart();

			if (startCycleAnimationDown == 33) {
				ptrInstancebarreDeVie->modifiePointDeVie(damage);
			}

		}
		if (startCycleAnimationDown == 48) { startCycleAnimationDown = 32; }

	}

}

void ClassZombi::moveZombi(){
	
	// s'il est a portée, attaque, donc plus de déplacement.
	if (distanceBetweenPLayerAndZombi() > 32 && pointDeVie > 1 ){
		/************************* AXE Y *************************/
		if (*ptrPositionJoueurY > posYZombi) {

			posYZombi += speedZombi;

			// collision zombi ?
			if ( !returnZombiCollisionProximity(false,false,true,false) ){

				// collision haut vers bas
				// arbre ou rocher
				if (*(ptrTabContentCase + returnIndexCaseZombi() -1) == 1 || *(ptrTabContentCase + returnIndexCaseZombi() - 1) == 2){
					// si on est assez centré sur la sprite pour gérer le colision
					if ( returnPosOnTheCaseX() > 12 && returnPosOnTheCaseX() < 52 && returnPosOnTheCaseY() < 5 ){
						posYZombi = returnPositionCaseZombiY()*64-60;
					}

				// case pleine
				} else if (*(ptrTabContentTerrain + returnIndexCaseZombi() - 1) == 1 && returnPosOnTheCaseY() < 5) {
					posYZombi = returnPositionCaseZombiY() * 64-60;
				}

			} else {
				posYZombi -= speedZombi;
			}

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

			// collision zombi ?
			if ( !returnZombiCollisionProximity(true, false, false, false)) {

				// collision bas vers le haut
				// arbre ou rocher
				if (*(ptrTabContentCase + returnIndexCaseZombi() - 1) == 1 || *(ptrTabContentCase + returnIndexCaseZombi() - 1) == 2 && returnPosOnTheCaseX() > 60) {
					// si on est assez centré sur la sprite pour gérer le colision
					if (returnPosOnTheCaseX() > 12 && returnPosOnTheCaseX() < 52 && returnPosOnTheCaseY() > 60) {
						posYZombi = returnPositionCaseZombiY() * 64 + 4;
					}

				// case pleine
				}else if (*(ptrTabContentTerrain + returnIndexCaseZombi() - 1) == 1) {
					posYZombi = returnPositionCaseZombiY() * 64+4;
				}

			} else {
				posYZombi += speedZombi;
			}


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
		// va vers la droite
		if (*ptrPositionJoueurX > posXZombi) {

			posXZombi += speedZombi;

			// collision zombi ?
			if (!returnZombiCollisionProximity(false, true, false, false)) {

				// colision
				// hit arbre
				if ( *(ptrTabContentCase + returnIndexCaseZombi() -1) == 1 || *(ptrTabContentCase + returnIndexCaseZombi() - 1) == 2){
					if ( posXZombi > returnPositionCaseZombiX()*64-17 && returnPosOnTheCaseX() < 32 && returnPosOnTheCaseY() > 10 && returnPosOnTheCaseY() < 55 ){
						posXZombi = returnPositionCaseZombiX()*64-17;
					}
				// hit case pleine
				} else if (*(ptrTabContentTerrain + returnIndexCaseZombi() - 1) == 1 && returnPosOnTheCaseX()<5 && returnPosOnTheCaseY()>3 ) {
					if (posXZombi > returnPositionCaseZombiX()*64-32) {
						posXZombi = returnPositionCaseZombiX()*64-32;
					}
				}

			} else {
				posXZombi -= speedZombi;
			}

			boolMoveZombiDown = false;
			boolMoveZombiLeft = false;
			boolMoveZombiRight = true;
			boolMoveZombiTop = false;

			lastmoveRight = true;
			lastmoveLeft = false;
			lastmoveTop = false;
			lastmoveDown = false;

		// va vers la gauche
		}else if (*ptrPositionJoueurX < posXZombi) {

			posXZombi -= speedZombi;

			// collision zombi ?
			if (!returnZombiCollisionProximity(false, false, false, true)) {

				// colision
				// hit arbre
				if (*(ptrTabContentCase + returnIndexCaseZombi() - 1) == 1 || *(ptrTabContentCase + returnIndexCaseZombi() - 1) == 2) {
					if (posXZombi < returnPositionCaseZombiX() * 64 + 18 && returnPosOnTheCaseX() > 32 && returnPosOnTheCaseY() > 10 && returnPosOnTheCaseY() < 55) {
						posXZombi = returnPositionCaseZombiX() * 64 + 18;
					}
				}
				else if (*(ptrTabContentTerrain + returnIndexCaseZombi() - 1) == 1 && returnPosOnTheCaseX() > 59) {
					if (posXZombi < returnPositionCaseZombiX() * 64 + 32) {
						posXZombi = returnPositionCaseZombiX() * 64 + 32;
					}
				}
			} else {
				posXZombi += speedZombi;
			}

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
// renvoi l'index de la case ou se trouve le zombie par rapport aux pieds du zombie
int ClassZombi::returnIndexCaseZombi(){
	return ((posXZombi + 32)/64) + ((posYZombi + 60)/64)*120;
}
// renvoi la case X ou se trouve le zombie
int ClassZombi::returnPositionCaseZombiX(){
	return ( posXZombi + 32 ) / 64; 
}
// renvoi la case Y ou se trouve le zombie
int ClassZombi::returnPositionCaseZombiY(){
	return (posYZombi + 60) / 64;
}
// renvoi la position X du zombie par rapport à sa case en cours
int ClassZombi::returnPosOnTheCaseX(){
	return (posXZombi + 32) - returnPositionCaseZombiX()*64;
}
// renvoi la position Y du zombie par rapport à sa case Y en cours
// et ce par rapport a ses pieds
int ClassZombi::returnPosOnTheCaseY(){
	return (posYZombi + 60) - returnPositionCaseZombiY() * 64;
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
		// donc on affiche pas le zombi
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

	int x = ofRandom(500,750);
	int y = ofRandom(500, 750);
	// on fait spawn en dehors de la carte
	posXZombi = *ptrPositionJoueurX+x;
	posYZombi = *ptrPositionJoueurY+y;

	bool verification = false;
	// pour éviter les zombis buggé l'un sur l'autre, on spawn pas sur un autre zombi SVP !!!
	for (int i = 0; i<*ptrMaxIndexPtrTabZombis; i++) {

		int minYcol = (ptrTabZombis + i)->posYZombi - ecartDeCollision;
		int maxYcol = (ptrTabZombis + i)->posYZombi + ecartDeCollision;
		int minXcol = (ptrTabZombis + i)->posXZombi - ecartDeCollision;
		int maxXcol = (ptrTabZombis + i)->posXZombi + ecartDeCollision;

		if ((ptrTabZombis + i)->posYZombi != posYZombi && (ptrTabZombis + i)->posYZombi != posYZombi &&
			posYZombi > minYcol && posYZombi < minYcol &&
			posXZombi > minXcol && posXZombi < maxXcol) {
			verification = true;
			break;
		}

	}

	if(verification){ spawnZombi();}

	// donne un différence de vitesse au zombie
	// BUG, il faut améliorer la collisions inter-zombis pour pouvoir se le permettre
	//this->speedZombi = ofRandom(1,3);

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

// verification qu'un autre zombi n'est pas à portée pour bloquer le déplacement
bool ClassZombi::returnZombiCollisionProximity(bool top, bool right, bool down, bool left){
	
	int futurPosXZombi = posXZombi;
	int futurPosYZombi = posYZombi;
	int retour = false;

	int minXactiveCol = futurPosXZombi - ecartDeCollision;
	int maxXactiveCol = futurPosXZombi + ecartDeCollision;
	int minYactiveCol = futurPosYZombi - ecartDeCollision;
	int maxYactiveCol = futurPosYZombi + ecartDeCollision;

	if(top){

		futurPosYZombi-=speedZombi;

		for (int i = 0; i<*ptrMaxIndexPtrTabZombis; i++) {

			int minYcol = (ptrTabZombis + i)->posYZombi - ecartDeCollision;
			int maxYcol = (ptrTabZombis + i)->posYZombi + ecartDeCollision;

			if ((ptrTabZombis + i)->posYZombi != posYZombi && (ptrTabZombis + i)->posYZombi != posYZombi &&
				futurPosYZombi - (ptrTabZombis + i)->posYZombi > 0 && futurPosYZombi - (ptrTabZombis + i)->posYZombi < ecartDeCollision &&
				posXZombi > (ptrTabZombis + i)->posXZombi - ecartDeCollision && posXZombi < (ptrTabZombis + i)->posXZombi + ecartDeCollision) {

				retour = true;
				break;
			}

		}
	} else if ( down ){

		futurPosYZombi += speedZombi;

		for (int i = 0; i<*ptrMaxIndexPtrTabZombis; i++) {

			int minYcol = (ptrTabZombis + i)->posYZombi - ecartDeCollision;
			int maxYcol = (ptrTabZombis + i)->posYZombi + ecartDeCollision;

			if ((ptrTabZombis + i)->posYZombi != posYZombi && (ptrTabZombis + i)->posYZombi != posYZombi &&
				(ptrTabZombis + i)->posYZombi - futurPosYZombi  > 0 && (ptrTabZombis + i)->posYZombi - futurPosYZombi  < ecartDeCollision &&
				posXZombi >(ptrTabZombis + i)->posXZombi - ecartDeCollision && posXZombi < (ptrTabZombis + i)->posXZombi + ecartDeCollision) {
				retour = true;
				break;
			}

		}

	} else if (right) {

		futurPosXZombi += speedZombi;


		
		for (int i = 0; i<*ptrMaxIndexPtrTabZombis; i++) {

			int minXcol = (ptrTabZombis + i)->posXZombi - ecartDeCollision;
			int maxXcol = (ptrTabZombis + i)->posXZombi + ecartDeCollision;

			// un zombi aura une zone de 10*10 autour du centre de ses pieds qui gère la collision
			if ((ptrTabZombis + i)->posXZombi != posXZombi && (ptrTabZombis + i)->posXZombi != posXZombi &&
				(ptrTabZombis + i)->posXZombi - futurPosXZombi  > 0 && (ptrTabZombis + i)->posXZombi - futurPosXZombi < ecartDeCollision &&
				posYZombi >(ptrTabZombis + i)->posYZombi - ecartDeCollision && posYZombi < (ptrTabZombis + i)->posYZombi + ecartDeCollision) {
				retour = true;
				break;
			}

		}


	} else if( left ){
	
		futurPosXZombi -= speedZombi;

		for (int i = 0; i<*ptrMaxIndexPtrTabZombis; i++) {

			int minXcol = (ptrTabZombis + i)->posXZombi - ecartDeCollision;
			int maxXcol = (ptrTabZombis + i)->posXZombi + ecartDeCollision;

			// un zombi aura une zone de 10*10 autour du centre de ses pieds qui gère la collision
			if ((ptrTabZombis + i)->posXZombi != posXZombi && (ptrTabZombis + i)->posXZombi != posXZombi &&
				futurPosXZombi - (ptrTabZombis + i)->posXZombi > 0 && futurPosXZombi - (ptrTabZombis + i)->posXZombi < ecartDeCollision &&
				posYZombi >(ptrTabZombis + i)->posYZombi - ecartDeCollision && posYZombi < (ptrTabZombis + i)->posYZombi + ecartDeCollision) {
				retour = true;
				break;
			}

		}

	}


	return retour;

}

void ClassZombi::AnimDeathZombie()
{
	if (pointDeVie <= 0) {

		AnimMortEnCours = true;
		if (lastmoveTop) {
			//cout << "test";
			zombiMort.drawSubsection(posAffichageX(), posAffichageY(), 64, 64, 64 * startCycleAnimationTop, 0, 64, 64);
			if (getDiffTime() > speedAnim) {
				startCycleAnimationTop++;
				setTimerStart();
			}
			if (startCycleAnimationTop == 16) { animDeathZombiDone = true; }
		}
		else if (lastmoveLeft) {
			zombiMort.drawSubsection(posAffichageX(), posAffichageY(), 64, 64, 64 * startCycleAnimationTop, 0, 64, 64);
			if (getDiffTime() > speedAnim) {
				startCycleAnimationTop++;
				setTimerStart();
			}
			if (startCycleAnimationTop == 16) { animDeathZombiDone = true; }
		}
		else if (lastmoveDown) {
			zombiMort.drawSubsection(posAffichageX(), posAffichageY(), 64, 64, 64 * startCycleAnimationDown, 0, 64, 64);
			if (getDiffTime() > speedAnim) {
				startCycleAnimationDown++;
				setTimerStart();
			}
			if (startCycleAnimationDown == 48) { animDeathZombiDone = true; }
		}
		else if (lastmoveRight) {
			zombiMort.drawSubsection(posAffichageX(), posAffichageY(), 64, 64, 64 * startCycleAnimationRight, 0, 64, 64);
			if (getDiffTime() > speedAnim) {
				startCycleAnimationRight++;
				setTimerStart();
			}
			if (startCycleAnimationRight == 32) { animDeathZombiDone = true; }
		}
	}
	if (animDeathZombiDone == true) {
		isSpawnZombi = false;
		ptrInstanceStats->addZombieKilled();
		*(ptrTabContentRessourcePlayer + 2) += 1;
		*(ptrTabContentRessourcePlayer + 3) += 1;
		*(ptrTabContentRessourcePlayer + 4) += 1;
	}
}

void ClassZombi::receiveDamage(int damage)
{
	pointDeVie -= damage;
	if ( pointDeVie < 1 ){
		AnimDeathZombie();
	}
}

int ClassZombi::isZombieDead() {
	return pointDeVie;
}

bool ClassZombi::getAnimMort() {
	return animDeathZombiDone;
}

