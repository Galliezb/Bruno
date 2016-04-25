/*
Codé par Christophe
But : gérer le personnage
*/
#include "classeMoving.h"
#include "ofMain.h"

moving::moving(){
	marche.loadImage("animmarche.png");
	courir.loadImage("animcourir.png");
	repos.loadImage("animrepos.png");
	construire.loadImage("animconstruire.png");
	degat.loadImage("animdegat.png");
	hacher.loadImage("animhacher.png");
	miner.loadImage("animminer.png");
	mort.loadImage("animmort.png");
	attaquer.loadImage("animattaquer.png");
}
// initialisation de la classe ( OF dispo ici, pas dans le constructeur )
void moving::init(int *ptrOriginX, int *ptrOriginY, int *ptrWidthScreen, int *ptrHeightScreen, string *playerCurrentAction) {

	// ajout des adresses pointeurs vers la position joueur
	this->ptrHeightScreen = ptrHeightScreen;
	this->ptrWidthScreen = ptrWidthScreen;

	this->ptrOriginX = ptrOriginX;
	this->ptrOriginY = ptrOriginY;

	// action en cours du joueur
	this->playerCurrentAction = playerCurrentAction;

}

void moving::movePlayer(){

	// vitesse d'animation
	speedAnim = 50;
	//Animation marche
	// Right and left prioritaire !
	if (goLeft == true) {

		marche.drawSubsection(midX(), midY(), 64, 64, 64 * startCycleAnimationLeft, 0, 64, 64);
		if (getDiffTime() > speedAnim) {
			startCycleAnimationLeft++;
			setTimerStart();
		}
		if (startCycleAnimationLeft == 64) { startCycleAnimationLeft = 48; }
	
	} else if (goRight == true) {

		marche.drawSubsection(midX(), midY(), 64, 64, 64 * startCycleAnimationRight, 0, 64, 64);
		if (getDiffTime() > speedAnim) {
			startCycleAnimationRight++;
			setTimerStart();
		}
		if (startCycleAnimationRight == 32) { startCycleAnimationRight = 16; }


	} else if (goTop == true) {

		marche.drawSubsection(midX(),midY(), 64, 64, 64 * startCycleAnimationTop, 0, 64, 64);
		if (getDiffTime() > speedAnim) {
			startCycleAnimationTop++;
			setTimerStart();
		}
		if (startCycleAnimationTop == 16) { startCycleAnimationTop = 0; }

	} else if (goDown == true) {

		marche.drawSubsection(midX(),midY(), 64, 64, 64 * startCycleAnimationDown, 0, 64, 64);
		if (getDiffTime() > speedAnim) {
			startCycleAnimationDown++;
			setTimerStart();
		}
		if (startCycleAnimationDown == 48) { startCycleAnimationDown = 32; }
	//Animation repos
	} else {
		playerAction();
	}
}

// Gère les animations du personnage au repos.
void moving::playerAction(){

	if ( *playerCurrentAction == "construire" ){
		action = construire;
		speedAnim = 50;
	} else if (*playerCurrentAction == "courir") {
		action = courir;
		speedAnim = 75;
	} else if(*playerCurrentAction == "degat") {
		action = degat;
		speedAnim = 90;
	} else if (*playerCurrentAction == "hacher") {
		action = hacher;
		speedAnim = 80;
	} else if (*playerCurrentAction == "miner") {
		action = miner;
		speedAnim = 80;
	} else if (*playerCurrentAction == "mort") {
		action = mort;
		speedAnim = 100;
	}
	else if (*playerCurrentAction == "attaquer") {
		action = attaquer;
		speedAnim = 50;
	}
	else {
		action = repos;
		speedAnim = 50;
	}

	// Right and left prioritaire !
	if (lastmoveRight == true) {

		action.drawSubsection(midX(),midY(), 64, 64, 64 * startCycleAnimationRight, 0, 64, 64);
		
		if (getDiffTime() > speedAnim) {
			startCycleAnimationRight++;
			setTimerStart();
		}
		if (startCycleAnimationRight == 32) { startCycleAnimationRight = 16; }


	} else if (lastmoveLeft == true) {

		action.drawSubsection(midX(),midY(), 64, 64, 64 * startCycleAnimationLeft, 0, 64, 64);
		if (getDiffTime() > speedAnim) {
			startCycleAnimationLeft++;
			setTimerStart();
		}
		if (startCycleAnimationLeft == 64) { startCycleAnimationLeft = 48; }


	} else if (lastmoveTop == true) {

		action.drawSubsection(midX(), midY(), 64, 64, 64 * startCycleAnimationTop, 0, 64, 64);
		if (getDiffTime() > speedAnim) {
			startCycleAnimationTop++;
			setTimerStart();
		}
		if (startCycleAnimationTop == 16) { startCycleAnimationTop = 0; }

	// position repos de base, face vers l'utilisateur pardi !
	} else {

		action.drawSubsection(midX(),midY(), 64, 64, 64 * startCycleAnimationDown, 0, 64, 64);
		if (getDiffTime() > speedAnim) {
			startCycleAnimationDown++;
			setTimerStart();
		}
		if (startCycleAnimationDown == 48) { startCycleAnimationDown = 32; }

	}

}
// Gère l'animation déplacement du joueur 
// + réinitialise l'état du cycle animation si mouvement = stop
// + stocke l'etat du dernier déplacement
void moving::setBoolMovePlayerTop(bool b){
	goTop = b;
	if(!b){ startCycleAnimationTop = 0; }
	if ( !goRight && !goDown && !goLeft){ 
		lastmoveTop = true;
		lastmoveRight = false;
		lastmoveDown = false;
		lastmoveLeft = false;
	}
}
void moving::setBoolMovePlayerRight(bool b) {
	goRight = b;
	if (!b) { startCycleAnimationRight = 16; }
	if (!goTop && !goDown && !goLeft) { 
		lastmoveTop = false;
		lastmoveRight = true;
		lastmoveDown = false;
		lastmoveLeft = false;
	}
}
void moving::setBoolMovePlayerDown(bool b) {
	goDown = b;
	if (!b) { startCycleAnimationDown = 32; }
	if (!goTop && !goRight && !goLeft) { 
		lastmoveTop = false;
		lastmoveRight = false;
		lastmoveDown = true;
		lastmoveLeft = false;
	}
}
void moving::setBoolMovePlayerLeft(bool b) {
	goLeft = b;
	if (!b) { startCycleAnimationLeft = 48; }
	if (!goTop && !goRight && !goLeft) { 
		lastmoveTop = false;
		lastmoveRight = false;
		lastmoveDown = false;
		lastmoveLeft = true;
	}
}
bool moving::getBoolMovePlayerTop(){
	return goTop;
}
bool moving::getBoolMovePlayerRight() {
	return goRight;
}
bool moving::getBoolMovePlayerDown() {
	return goDown;
}
bool moving::getBoolMovePlayerLeft() {
	return goLeft;
}
int moving::midX(){

	if ( *ptrOriginX<0){
		return *ptrWidthScreen / 2 - 32 + *ptrOriginX;
	} else {
		if (*ptrOriginX >= 7680-*ptrWidthScreen/2-32){
			return *ptrWidthScreen-64;
		} else if ( *ptrOriginX > 7680 - *ptrWidthScreen ){
			return *ptrWidthScreen / 2 + (*ptrWidthScreen-(7680 - *ptrOriginX) - 32);
		} else {
			return *ptrWidthScreen / 2 - 32;
		}
	}
}
int moving::midY() {

	if (*ptrOriginY<0) {
		return *ptrHeightScreen / 2 - 32 + *ptrOriginY;
	} else {
		if (*ptrOriginY >= 5120 - *ptrHeightScreen / 2 - 32) {
			return *ptrHeightScreen - 64;
		}
		else if (*ptrOriginY > 5120 - *ptrHeightScreen) {
			return *ptrHeightScreen / 2 + (*ptrHeightScreen - (5120 - *ptrOriginY) - 32);
		}
		else {
			return *ptrHeightScreen / 2 - 32;
		}
	}
}
void moving::setTimerStart(){
	tpsStart = ofGetElapsedTimeMillis();
}
void moving::setTimerEnd() {
	tpsStop = ofGetElapsedTimeMillis();
}
int moving::getDiffTime(){
	return ofGetElapsedTimeMillis() - tpsStart;
}
int moving::getTimerStart() {
	return tpsStart;
}
int moving::getTimerEnd() {
	return tpsStop;
}
