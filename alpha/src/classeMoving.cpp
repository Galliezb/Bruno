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

	sound.load("aie.mp3");
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
// Gère le déplacement  + la colision avec les objets
void moving::updateOrigin(){
	int caseX, caseY;
	// Calcul de case pour les colisions !
	
	/*************************************** VERS LE HAUT ******************************/
	if (boolMovePlayerTop) {

		// ici on calcul par rapport à la case et pts d'anchrage 0.0 de la sprite
		int caseX = *ptrOriginX + *ptrWidthScreen / 2;
		int caseY = *ptrOriginY + *ptrHeightScreen / 2;
		// les bords de map c'est chiant putain !
		if (caseX < 0) { caseX = 0; }
		if (caseY < 0) { caseY = 0; }
		if (caseX > 7680 - *ptrWidthScreen) { caseX = 7680 - *ptrWidthScreen; }
		if (caseY > 5120 - *ptrHeightScreen) { caseY = 5120 - *ptrHeightScreen; }
		// on transforme en case
		caseX = floor(caseX / 64);
		caseY = floor(caseY / 64);

		*ptrOriginY -= scrollingSpeed;
		// Putain tu va ou la ? On sort pas de la map gros lâche !
		// -24 mesuré au pixel prêt
		if (*ptrOriginY < 1 - *ptrHeightScreen / 2 - 32 + 64) {
			*ptrOriginY = 1 - *ptrHeightScreen / 2 - 32 + 64 - 24;

			if ((ofGetElapsedTimeMillis()-timerTrollAie)/1000 > 30 ){
				sound.play();
				timerTrollAie = ofGetElapsedTimeMillis();
			}
			printf("**********\nOUCH(%d)\n**********\n", (ofGetElapsedTimeMillis() - timerTrollAie) / 1000);

		}

		// si la case contient un arbre ou rocher + exception X pour passer a coté des arbres.
		if ( ( *(ptrTabContentTerrain + caseX + caseY * 120 - 1) != 0
			 || *(ptrTabContentCase + caseX + caseY * 120 - 1) == 1
			 || *(ptrTabContentCase + caseX + caseY * 120 - 1) == 2)
			 && *ptrOriginX + *ptrWidthScreen / 2 > caseX * 64 + 16 
			 && *ptrOriginX + *ptrWidthScreen / 2 < caseX * 64 + 48) {
			// Limite basse de la case ou y'a colision
			// -20 c'est pour coller au plus proche, on modifie vers le haut la limite de 20
			int maxY = caseY * 64 + 64 -20;
			printf("TOP\n");
			printf("%d < %d\n", *ptrOriginY + *ptrHeightScreen / 2, maxY);
			if (*ptrOriginY + *ptrHeightScreen / 2 < maxY) { *ptrOriginY = maxY - *ptrHeightScreen / 2; }
			printf("%d < %d\n", *ptrOriginY + *ptrHeightScreen / 2, maxY);
		}

	}

	/*************************************** VERS LA DROITE ******************************/
	if (boolMovePlayerRight) {

		// ici on calcul par rapport à la case et pts d'anchrage au niveau du pied droit de la sprite
		int caseX = *ptrOriginX + 39 + *ptrWidthScreen / 2;
		int caseY = *ptrOriginY + 28 + *ptrHeightScreen / 2;
		// les bords de map c'est chiant putain !
		if (caseX < 0) { caseX = 0; }
		if (caseY < 0) { caseY = 0; }
		if (caseX > 7680 - *ptrWidthScreen) { caseX = 7680 - *ptrWidthScreen; }
		if (caseY > 5120 - *ptrHeightScreen) { caseY = 5120 - *ptrHeightScreen; }
		// on transforme en case
		caseX = floor(caseX / 64);
		caseY = floor(caseY / 64);

		*ptrOriginX += scrollingSpeed;
		if (*ptrOriginX > 7679 - *ptrWidthScreen / 2) {
			*ptrOriginX = 7680 - *ptrWidthScreen / 2;
		}

		// si la case contient un arbre ou rocher + exception X pour passer a coté des arbres.
		if ((*(ptrTabContentTerrain + caseX + caseY * 120 - 1) != 0
			|| *(ptrTabContentCase + caseX + caseY * 120 - 1) == 1
			|| *(ptrTabContentCase + caseX + caseY * 120 - 1) == 2)
			&& *ptrOriginY + *ptrHeightScreen / 2 > caseY * 64 - 20) {
			// Limite basse de la case ou y'a colision
			// -20 c'est pour coller au plus proche, on modifie vers le haut la limite de 20
			int maxX = caseX * 64 + 12;
			if (*ptrOriginX + *ptrWidthScreen / 2 > maxX) { *ptrOriginX = maxX - *ptrWidthScreen / 2; }
		}


	}
	/*************************************** VERS LE BAS ******************************/
	if (boolMovePlayerDown) {

		// ici on calcul par rapport à la case et pts d'anchrage 0.0 de la sprite
		int caseX = *ptrOriginX + *ptrWidthScreen / 2;
		int caseY = *ptrOriginY + *ptrHeightScreen / 2;
		// les bords de map c'est chiant putain !
		if (caseX < 0) { caseX = 0; }
		if (caseY < 0) { caseY = 0; }
		if (caseX > 7680 - *ptrWidthScreen) { caseX = 7680 - *ptrWidthScreen; }
		if (caseY > 5120 - *ptrHeightScreen) { caseY = 5120 - *ptrHeightScreen; }
		// on transforme en case
		caseX = floor(caseX / 64);
		caseY = floor(caseY / 64);


		*ptrOriginY += scrollingSpeed;
		if (*ptrOriginY > 5119 - *ptrHeightScreen / 2) {
			*ptrOriginY = 5120 - *ptrHeightScreen / 2;
		}

		// si la case contient un arbre ou rocher + exception X pour passer a coté des arbres.
		if ((*(ptrTabContentTerrain + caseX + (caseY+1) * 120 - 1) != 0
			|| *(ptrTabContentCase + caseX + (caseY+1) * 120 - 1) == 1
			|| *(ptrTabContentCase + caseX + (caseY+1) * 120 - 1) == 2)
			&& *ptrOriginX + *ptrWidthScreen / 2 > caseX * 64 + 16
			&& *ptrOriginX + *ptrWidthScreen / 2 < caseX * 64 + 48) {
			// Limite basse de la case ou y'a colision
			// -20 c'est pour coller au plus proche, on modifie vers le haut la limite de 20
			int maxY = (caseY+1) * 64 -22;
			printf("DOWN\n");
			printf("%d > %d\n", *ptrOriginY + *ptrHeightScreen / 2, maxY);
			if (*ptrOriginY + *ptrHeightScreen / 2 > maxY) { *ptrOriginY = maxY - *ptrHeightScreen / 2; }
			printf("%d > %d\n", *ptrOriginY + *ptrHeightScreen / 2, maxY);
		}


	}
	/*************************************** VERS LA GAUCHE ******************************/
	if (boolMovePlayerLeft) {

		*ptrOriginX -= scrollingSpeed;
		if (*ptrOriginX < 1 - *ptrWidthScreen / 2 - 32 + 64) {
			*ptrOriginX = 1 - *ptrWidthScreen / 2 - 32 + 64;
		}


		// ici on calcul par rapport à la case et pts d'anchrage au niveau du pied droit de la sprite
		int caseX = *ptrOriginX - 7 + *ptrWidthScreen / 2;
		int caseY = *ptrOriginY + 28 + *ptrHeightScreen / 2;
		// les bords de map c'est chiant putain !
		if (caseX < 0) { caseX = 0; }
		if (caseY < 0) { caseY = 0; }
		if (caseX > 7680 - *ptrWidthScreen) { caseX = 7680 - *ptrWidthScreen; }
		if (caseY > 5120 - *ptrHeightScreen) { caseY = 5120 - *ptrHeightScreen; }
		// on transforme en case
		caseX = floor(caseX / 64);
		caseY = floor(caseY / 64);

		printf("*****************************************************\n");
		printf("originX => %d(%d)\t", *ptrOriginX, *ptrOriginX + *ptrWidthScreen / 2);
		printf("originY => %d(%d)\n", *ptrOriginY, *ptrOriginY + *ptrHeightScreen / 2);
		printf("caseX => %d\t", caseX);
		printf("caseY => %d\n", caseY);
		printf("Case => %d\t", *(ptrTabContentCase + caseX + caseY * 120 - 1));
		printf("Terrain => %d\n", *(ptrTabContentTerrain + caseX + caseY * 120 - 1));
		printf("Screen => w;%d\th:%d\n", *ptrWidthScreen, *ptrHeightScreen);
		printf("haut arbre => %d > %d\n", *ptrOriginY + *ptrHeightScreen / 2, caseY * 64 - 10);

		// si la case contient un arbre ou rocher + exception X pour passer a coté des arbres.
		if ((*(ptrTabContentTerrain + caseX + caseY * 120 - 1) != 0
			|| *(ptrTabContentCase + caseX + caseY * 120 - 1) == 1
			|| *(ptrTabContentCase + caseX + caseY * 120 - 1) == 2)
			&& *ptrOriginY + *ptrHeightScreen / 2 > caseY * 64 - 20) {
			// Limite basse de la case ou y'a colision
			// -20 c'est pour coller au plus proche, on modifie vers le haut la limite de 20
			int maxX = caseX * 64 + 32 + 20;
			printf("LEFT HIT !!!\n");
			printf("%d < %d\n", *ptrOriginX + *ptrWidthScreen / 2, maxX);
			if (*ptrOriginX + *ptrWidthScreen / 2 < maxX) { *ptrOriginX = maxX - *ptrWidthScreen / 2; }
			printf("%d < %d\n", *ptrOriginX + *ptrWidthScreen / 2, maxX);
		}


	}



}
// c'est la méthode BOSS ok ? Elle dit t'avance pas, alors t'avance pas bordel !
void moving::returnLimitCollisionMove(){

	// ne pas oublier, les pointeurs pointe des variables qui possèdent déjà la nouvelle position
	// Il faut donc décider ici si on refuse ou limite la distance de déplacement.

	/*
	printf("*****************************************************\n");
	printf("originX => %d\t",*ptrOriginX);
	printf("originY => %d\n", *ptrOriginY);
	printf("caseX => %d\t", caseX);
	printf("caseY => %d\n", caseY);
	printf("Case => %d\t", *(ptrTabContentCase + caseX + caseY * 120 - 1));
	printf("Terrain => %d\n", *(ptrTabContentTerrain + caseX + caseY * 120 - 1));
	*/

	// on verifie que la case ne soit pas de l'eau ( l'eau c'est pour les connards ! Heu les canards ! )
	// Et tout objet qui se trouve dessus
	//if ( *(ptrTabContentCase + caseX + caseY * 120 - 1)!=0 || *(ptrTabContentTerrain + caseX + caseY * 120 -1) !=0 ){
	
		
		// Bordel y'a collision ! Par soucis de conscience professionnelle
		// on va renvoyé la limite de la case plutôt que l'ancienne position
		// Ce sera ainsi adapatable à toute vitesse de déplacement
		/*
		if ( getBoolMovePlayerLeft() ){
			// valeur max X autorisé vers la GAUCHE 
			int maxX = caseX*64+64;
			printf("\n*****\ngauche : %d<%d\n*****\n", *ptrOriginX, maxX);
			if (*ptrOriginX<maxX){ *ptrOriginX=maxX-*ptrWidthScreen/2; }
		}
		if (getBoolMovePlayerRight()) {
			// valeur max X autorisé ers la DROITE
			int maxX = caseX * 64;
			printf("\n*****\ndroite : %d>%d\n*****\n", *ptrOriginX, maxX);
			if (*ptrOriginX>maxX - *ptrWidthScreen / 2) { *ptrOriginX = maxX - *ptrWidthScreen / 2; }
		}*/
		/*
		if (getBoolMovePlayerTop()) {
			// Limite basse de la case ou y'a colision
			int maxY = caseY * 64 + 64;
			printf("%d < %d\n", *ptrOriginY + *ptrHeightScreen / 2, maxY);
			printf("%d\n", *ptrHeightScreen);
			if (*ptrOriginY+*ptrHeightScreen/2 < maxY) { *ptrOriginY = maxY-*ptrHeightScreen/2-10; }
			printf("%d < %d\n", *ptrOriginY + *ptrHeightScreen / 2,maxY);
		}
		if (getBoolMovePlayerDown()) {
			// valeur max X autorisé vers le BAS
			int maxY = caseY * 64;
			if (*ptrOriginY>maxY) { *ptrOriginY = maxY; }
		}*/


	
	//}

}
