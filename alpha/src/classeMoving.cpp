/*
Codé par Christophe
But : gérer le personnage
*/
#include "classeMoving.h"
#include "ofMain.h"

moving::moving(){
	marche.loadImage("animmarche.png");
	repos.loadImage("animrepos.png");
}
// initialisation de la classe ( OF dispo ici, pas dans le constructeur )
void moving::init(int *ptrWidthScreen, int *ptrHeightScreen) {

	// ajout des adresses pointeurs vers la position joueur
	this->ptrHeightScreen = ptrWidthScreen;
	this->ptrWidthScreen = ptrHeightScreen;

}
void moving::movePlayer(){
	//Animation marche
	if (goTop == true) {

		marche.drawSubsection(*ptrWidthScreen/2, *ptrHeightScreen/2, 64, 64, 64 * startCycleAnimationTop, 0, 64, 64);
		startCycleAnimationTop++;
		if (startCycleAnimationTop == 16) { startCycleAnimationTop = 0; }

	} else if (goRight == true){

		marche.drawSubsection(*ptrWidthScreen/2, *ptrHeightScreen/2, 64, 64, 64 * startCycleAnimationRight, 0, 64, 64);
		startCycleAnimationRight++;
		if (startCycleAnimationRight == 32){ startCycleAnimationRight = 16;}

	} else if (goDown == true) {

		marche.drawSubsection(*ptrWidthScreen/2, *ptrHeightScreen/2, 64, 64, 64 * startCycleAnimationDown, 0, 64, 64);
		startCycleAnimationDown++;
		if (startCycleAnimationDown == 48) { startCycleAnimationDown = 32; }
	} else if (goLeft == true){
	 
		marche.drawSubsection(*ptrWidthScreen/2, *ptrHeightScreen/2, 64, 64, 64 * startCycleAnimationLeft, 0, 64, 64);
		startCycleAnimationLeft++;
		if (startCycleAnimationLeft == 64) { startCycleAnimationLeft = 48; }

	//Animation repos
	} else {
		playerWait();
	}
}

// Gère les animations du personnage au repos.
void moving::playerWait(){
	if (lastmoveTop == true) {

		repos.drawSubsection(*ptrWidthScreen/2, *ptrHeightScreen/2, 64, 64, 64 * startCycleAnimationTop, 0, 64, 64);
		startCycleAnimationTop++;
		if (startCycleAnimationTop == 16) { startCycleAnimationTop = 0; }

	} else if (lastmoveRight == true) {

		repos.drawSubsection(*ptrWidthScreen/2, *ptrHeightScreen/2, 64, 64, 64 * startCycleAnimationRight, 0, 64, 64);
		startCycleAnimationRight++;
		if (startCycleAnimationRight == 32) { startCycleAnimationRight = 16; }

	} else if (lastmoveDown == true) {

		repos.drawSubsection(*ptrWidthScreen/2, *ptrHeightScreen/2, 64, 64, 64 * startCycleAnimationDown, 0, 64, 64);
		startCycleAnimationDown++;
		if (startCycleAnimationDown == 48) { startCycleAnimationDown = 32; }

	} else if (lastmoveLeft == true) {

		repos.drawSubsection(*ptrWidthScreen/2, *ptrHeightScreen/2, 64, 64, 64 * startCycleAnimationLeft, 0, 64, 64);
		startCycleAnimationLeft++;
		if (startCycleAnimationLeft == 64) { startCycleAnimationLeft = 48; }

	}
}
// Gère l'animation déplacement du joueur 
// + réinitialise l'état du cycle animation si mouvement = stop
// + stocke l'etat du dernier déplacement
void moving::setBoolMovePlayerTop(bool b){
	goTop = b;
	if(!b){ startCycleAnimationTop = 0; }
	if ( !goRight && !goDown && !goLeft){ lastmoveTop = true;}
}
void moving::setBoolMovePlayerRight(bool b) {
	goRight = b;
	if (!b) { startCycleAnimationRight = 16; }
	if (!goTop && !goDown && !goLeft) { lastmoveRight = true; }
}
void moving::setBoolMovePlayerDown(bool b) {
	goDown = b;
	if (!b) { startCycleAnimationDown = 32; }
	if (!goTop && !goRight && !goLeft) { lastmoveDown = true; }
}
void moving::setBoolMovePlayerLeft(bool b) {
	goLeft = b;
	if (!b) { startCycleAnimationLeft = 48; }
	if (!goTop && !goRight && !goLeft) { lastmoveLeft = true; }
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
void moving::limitMovePlayer(){
	if (*ptrWidthScreen/2 < 1 ){ *ptrWidthScreen = 1; }
	if (*ptrHeightScreen/2 < 1) { *ptrHeightScreen = 1; }
	if (*ptrWidthScreen/2 > 7680) { *ptrWidthScreen = 7680; }
	if (*ptrHeightScreen/2 > 5120) { *ptrHeightScreen = 5120; }
}