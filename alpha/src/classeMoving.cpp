/*
Codé par Christophe
But : gérer le personnage
*/
#include "classeMoving.h"
#include "ofMain.h"

moving::moving(){
	marche.loadImage("animmarche.png");
	repos.loadImage("animrepos.png");
	construire.loadImage("animconstruire.png");
	courir.loadImage("animcourir.png");
	degat.loadImage("anidegat.png");
	hacher.loadImage("animhacher.png");
	miner.loadImage("animminer.png");
	mort.loadImage("animmort.png");
}
// initialisation de la classe ( OF dispo ici, pas dans le constructeur )
void moving::init(int *ptrOriginX, int *ptrOriginY, int *ptrWidthScreen, int *ptrHeightScreen) {

	// ajout des adresses pointeurs vers la position joueur
	this->ptrHeightScreen = ptrHeightScreen;
	this->ptrWidthScreen = ptrWidthScreen;

	this->ptrOriginX = ptrOriginX;
	this->ptrOriginY = ptrOriginY;

	printf("Initialisation MOVING : \n");

	ofLogVerbose() << "*ptrWidthScreen : " << *ptrWidthScreen;
	ofLogVerbose() << "*ptrWidthScreen : " << *ptrHeightScreen;

	ofLogVerbose() << "*ptrOriginX : " << *ptrOriginX;
	ofLogVerbose() << "*ptrOriginY : " << *ptrOriginY;


}

void moving::movePlayer(){

	//Animation marche
	// Right and left prioritaire !
	if (goLeft == true) {

		marche.drawSubsection(midX(), midY(), 64, 64, 64 * startCycleAnimationLeft, 0, 64, 64);
		startCycleAnimationLeft++;
		if (startCycleAnimationLeft == 64) { startCycleAnimationLeft = 48; }
	
	} else if (goRight == true) {

		marche.drawSubsection(midX(), midY(), 64, 64, 64 * startCycleAnimationRight, 0, 64, 64);
		startCycleAnimationRight++;
		if (startCycleAnimationRight == 32) { startCycleAnimationRight = 16; }

	} else if (goTop == true) {

		marche.drawSubsection(midX(),midY(), 64, 64, 64 * startCycleAnimationTop, 0, 64, 64);
		startCycleAnimationTop++;
		if (startCycleAnimationTop == 16) { startCycleAnimationTop = 0; }

	} else if (goDown == true) {

		marche.drawSubsection(midX(),midY(), 64, 64, 64 * startCycleAnimationDown, 0, 64, 64);
		startCycleAnimationDown++;
		if (startCycleAnimationDown == 48) { startCycleAnimationDown = 32; }
	//Animation repos
	} else {
		playerAction("wait");
	}
}

// Gère les animations du personnage au repos.
void moving::playerAction(string str){

	if ( str == "construire" ){
		action = construire;
	} else if (str == "courir") {
		action = courir;
	} else if(str == "degat") {
		action = degat;
	} else if (str == "hacher") {
		action = hacher;
	} else if (str == "miner") {
		action = miner;
	} else if (str == "mort") {
		action = mort;
	} else {
		action = construire;
	}
	
	// Right and left prioritaire !
	if (lastmoveRight == true) {

		action.drawSubsection(midX(),midY(), 64, 64, 64 * startCycleAnimationRight, 0, 64, 64);
		startCycleAnimationRight++;
		if (startCycleAnimationRight == 32) { startCycleAnimationRight = 16; }

	} else if (lastmoveLeft == true) {

		action.drawSubsection(midX(),midY(), 64, 64, 64 * startCycleAnimationLeft, 0, 64, 64);
		startCycleAnimationLeft++;
		if (startCycleAnimationLeft == 64) { startCycleAnimationLeft = 48; }
	} else if (lastmoveTop == true) {

		action.drawSubsection(midX(), midY(), 64, 64, 64 * startCycleAnimationTop, 0, 64, 64);
		startCycleAnimationTop++;
		if (startCycleAnimationTop == 16) { startCycleAnimationTop = 0; }

	// position repos de base, face vers l'utilisateur pardi !
	} else {

		action.drawSubsection(midX(),midY(), 64, 64, 64 * startCycleAnimationDown, 0, 64, 64);
		startCycleAnimationDown++;
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
	string fpsStr = "ptrOriginY => " + ofToString(*ptrOriginY);
	ofDrawBitmapString(fpsStr, 400, 100);
	fpsStr = "ptrOriginX => " + ofToString(*ptrOriginX);
	ofDrawBitmapString(fpsStr, 400, 125);
	fpsStr = "ptrOriginX => " + ofToString((7680 - *ptrWidthScreen) + (*ptrOriginX - (7680 - *ptrWidthScreen)));
	ofDrawBitmapString(fpsStr, 400, 150);

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
/*************************************** ACTIONS PLAYER ************************/
void moving::actionPlayerBuild(){
	// Right and left prioritaire !
	if (lastmoveRight == true) {

		construire.drawSubsection(midX(), midY(), 64, 64, 64 * startCycleAnimationRight, 0, 64, 64);
		startCycleAnimationRight++;
		if (startCycleAnimationRight == 32) { startCycleAnimationRight = 16; }

	}
	else if (lastmoveLeft == true) {

		construire.drawSubsection(midX(), midY(), 64, 64, 64 * startCycleAnimationLeft, 0, 64, 64);
		startCycleAnimationLeft++;
		if (startCycleAnimationLeft == 64) { startCycleAnimationLeft = 48; }
	}
	else if (lastmoveTop == true) {

		construire.drawSubsection(midX(), midY(), 64, 64, 64 * startCycleAnimationTop, 0, 64, 64);
		startCycleAnimationTop++;
		if (startCycleAnimationTop == 16) { startCycleAnimationTop = 0; }

		// position repos de base, face vers l'utilisateur pardi !
	}
	else {

		construire.drawSubsection(midX(), midY(), 64, 64, 64 * startCycleAnimationDown, 0, 64, 64);
		startCycleAnimationDown++;
		if (startCycleAnimationDown == 48) { startCycleAnimationDown = 32; }

	}

}
void actionPlayerRun() {

}
void actionPlayerTakeDamage() {

}
void actionPlayerCut() {

}
void actionPlayerMine() {

}
void actionPlayerIsDead() {

}
