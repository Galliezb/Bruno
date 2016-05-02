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
void moving::init(int *ptrOriginX, int *ptrOriginY, int *ptrWidthScreen, int *ptrHeightScreen, string *playerCurrentAction, int *ptrTabContentCase, int *ptrTtabContentTerrain) {

	// pointeur tab content map
	this->ptrTabContentCase = ptrTabContentCase;
	this->ptrTabContentTerrain = ptrTtabContentTerrain;

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
	if (boolMovePlayerLeft == true) {

		marche.drawSubsection(midX(), midY(), 64, 64, 64 * startCycleAnimationLeft, 0, 64, 64);
		if (getDiffTime() > speedAnim) {
			startCycleAnimationLeft++;
			setTimerStart();
		}
		if (startCycleAnimationLeft == 64) { startCycleAnimationLeft = 48; }
	
	} else if (boolMovePlayerRight == true) {

		marche.drawSubsection(midX(), midY(), 64, 64, 64 * startCycleAnimationRight, 0, 64, 64);
		if (getDiffTime() > speedAnim) {
			startCycleAnimationRight++;
			setTimerStart();
		}
		if (startCycleAnimationRight == 32) { startCycleAnimationRight = 16; }


	} else if (boolMovePlayerTop == true) {

		marche.drawSubsection(midX(),midY(), 64, 64, 64 * startCycleAnimationTop, 0, 64, 64);
		if (getDiffTime() > speedAnim) {
			startCycleAnimationTop++;
			setTimerStart();
		}
		if (startCycleAnimationTop == 16) { startCycleAnimationTop = 0; }

	} else if (boolMovePlayerDown == true) {

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
	boolMovePlayerTop = b;
	if(!b){ startCycleAnimationTop = 0; }
	if ( !boolMovePlayerRight && !boolMovePlayerDown && !boolMovePlayerLeft){ 
		lastmoveTop = true;
		lastmoveRight = false;
		lastmoveDown = false;
		lastmoveLeft = false;
	}
}
void moving::setBoolMovePlayerRight(bool b) {
	boolMovePlayerRight = b;
	if (!b) { startCycleAnimationRight = 16; }
	if (!boolMovePlayerTop && !boolMovePlayerDown && !boolMovePlayerLeft) { 
		lastmoveTop = false;
		lastmoveRight = true;
		lastmoveDown = false;
		lastmoveLeft = false;
	}
}
void moving::setBoolMovePlayerDown(bool b) {
	boolMovePlayerDown = b;
	if (!b) { startCycleAnimationDown = 32; }
	if (!boolMovePlayerTop && !boolMovePlayerRight && !boolMovePlayerLeft) { 
		lastmoveTop = false;
		lastmoveRight = false;
		lastmoveDown = true;
		lastmoveLeft = false;
	}
}
void moving::setBoolMovePlayerLeft(bool b) {
	boolMovePlayerLeft = b;
	if (!b) { startCycleAnimationLeft = 48; }
	if (!boolMovePlayerTop && !boolMovePlayerRight && !boolMovePlayerLeft) { 
		lastmoveTop = false;
		lastmoveRight = false;
		lastmoveDown = false;
		lastmoveLeft = true;
	}
}
bool moving::getBoolMovePlayerTop(){
	return boolMovePlayerTop;
}
bool moving::getBoolMovePlayerRight() {
	return boolMovePlayerRight;
}
bool moving::getBoolMovePlayerDown() {
	return boolMovePlayerDown;
}
bool moving::getBoolMovePlayerLeft() {
	return boolMovePlayerLeft;
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
void moving::updateOrigin(){

	if (boolMovePlayerTop) {
		*ptrOriginY -= scrollingSpeed;
		// Putain tu va ou la ? On sort pas de la map gros lâche !
		if (*ptrOriginY < 1 - *ptrHeightScreen / 2 - 32 + 64) {
			*ptrOriginY = 1 - *ptrHeightScreen / 2 - 32 + 64;
		}
	}
	if (boolMovePlayerRight) {
		*ptrOriginX += scrollingSpeed;
		if (*ptrOriginX > 7679 - *ptrWidthScreen / 2) {
			*ptrOriginX = 7680 - *ptrWidthScreen / 2;
		}
	}
	if (boolMovePlayerDown) {
		*ptrOriginY += scrollingSpeed;
		if (*ptrOriginY > 5119 - *ptrHeightScreen / 2) {
			*ptrOriginY = 5120 - *ptrHeightScreen / 2;
		}
	}
	if (boolMovePlayerLeft) {
		*ptrOriginX -= scrollingSpeed;
		if (*ptrOriginX < 1 - *ptrWidthScreen / 2 - 32 + 64) {
			*ptrOriginX = 1 - *ptrWidthScreen / 2 - 32 + 64;
		}
	}

	// verifie la collision
	returnLimitCollisionMove();


}
// c'est la méthode BOSS ok ? Elle dit t'avance pas, alors t'avance pas bordel !
void moving::limitCollisionMove(){

	// ne pas oublier, les pointeurs pointe des variables qui possèdent déjà la nouvelle position
	// Il faut donc décider ici si on refuse ou limite la distance de déplacement.

	// variable local,
	int caseX = *ptrOriginX + *ptrWidthScreen/2;
	int caseY = *ptrOriginY + *ptrHeightScreen/2;
	// les bords de map c'est chiant putain !
	if (caseX < 0) { caseX = 0; }
	if (caseY < 0) { caseY = 0; }

	// on doit aussi calculer Y
	caseX = floor(caseX / 64);
	caseY = floor(caseY / 64);
	printf("*****************************************************\n");
	printf("originX => %d\t",*ptrOriginX);
	printf("originY => %d\n", *ptrOriginY);
	printf("caseX => %d\t", caseX);
	printf("caseY => %d\n", caseY);
	printf("Case => %d\t", *(ptrTabContentCase + caseX + caseY * 120 - 1));
	printf("Terrain => %d\n", *(ptrTabContentTerrain + caseX + caseY * 120 - 1));


	// on verifie que la case ne soit pas de l'eau ( l'eau c'est pour les connards ! Heu les canards ! )
	// Et tout objet qui se trouve dessus
	// Il faut vérifier 4 colisions, X de la sprite ( en Y = 0 ) et X de la sprite ( en Y : 64 )
	// idem pour les Y mais avec les X
	// les colisions X
	if ( *(ptrTabContentCase + caseX + caseY * 120 - 1)!=0 || *(ptrTabContentCase + caseX + caseY * 120 - 1) != 0){		
		// Bordel y'a collision ! Par soucis de conscience professionnelle
		// on va renvoyé la limite de la case plutôt que l'ancienne position
		// Ce sera ainsi adapatable à toute vitesse de déplacement

		if ( getBoolMovePlayerLeft() ){
			// valeur max X autorisé vers la GAUCHE pour le coin HAUT GAUCHE de la sprite
			int maxX = caseX*64+64;
			printf("\n*****\ngauche : %d<%d\n*****\n", *ptrOriginX, maxX);
			if (*ptrOriginX<maxX){ *ptrOriginX=maxX-*ptrWidthScreen/2; }

			// valeur max X autorisé vers la GAUCHE pour le coin BAS GAUCHE de la sprite
			int maxX = caseX * 64 + 64;
			printf("\n*****\ngauche : %d<%d\n*****\n", *ptrOriginX, maxX);
			if (*ptrOriginX<maxX) { *ptrOriginX = maxX - *ptrWidthScreen / 2; }

		}
		if (getBoolMovePlayerRight()) {
			// valeur max X autorisé ers la DROITE
			int maxX = caseX * 64;
			printf("\n*****\ndroite : %d>%d\n*****\n", *ptrOriginX, maxX);
			if (*ptrOriginX>maxX - *ptrWidthScreen / 2) { *ptrOriginX = maxX - *ptrWidthScreen / 2; }
		}

		if (getBoolMovePlayerTop()) {
			// valeur max X autorisé vers le HAUT 
			int maxY = caseY * 64 + 64;
			if (*ptrOriginY<maxY) { *ptrOriginY = maxY; }
		}
		if (getBoolMovePlayerDown()) {
			// valeur max X autorisé vers le BAS
			int maxY = caseY * 64;
			if (*ptrOriginY>maxY) { *ptrOriginY = maxY; }
		}


	
	}

}
