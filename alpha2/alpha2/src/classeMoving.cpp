#include <math.h>
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
void moving::init(int *ptrPositionJoueurX, int *ptrPositionJoueurY, int *ptrWidthScreen, int *ptrHeightScreen, string *playerCurrentAction, int *ptrTabContentCase, int *ptrTtabContentTerrain) {

	// pointeur tab content map
	this->ptrTabContentCase = ptrTabContentCase;
	this->ptrTabContentTerrain = ptrTtabContentTerrain;

	// ajout des adresses pointeurs vers la position joueur
	this->ptrHeightScreen = ptrHeightScreen;
	this->ptrWidthScreen = ptrWidthScreen;

	this->ptrPositionJoueurX = ptrPositionJoueurX;
	this->ptrPositionJoueurY = ptrPositionJoueurY;

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

	int posXCamera = *ptrPositionJoueurX+32 - *ptrWidthScreen / 2;

	if (posXCamera<1) {
		posXCamera = 0;
	} else if (posXCamera> 7680 - *ptrWidthScreen) {
		posXCamera = 7680 - *ptrWidthScreen;
	}

	return *ptrPositionJoueurX - posXCamera;
	printf("ptrPosY => %d\n", *ptrPositionJoueurX);

}
int moving::midY() {

	int posYCamera = *ptrPositionJoueurY+32 - *ptrHeightScreen / 2;

	if (posYCamera<1) {
		posYCamera = 0;
	} else if (posYCamera> 5120 - *ptrHeightScreen) {
		posYCamera = 5120 - *ptrHeightScreen;
	}

	return *ptrPositionJoueurY - posYCamera;
	printf("ptrPosY => %d\n", *ptrPositionJoueurX);

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
void moving::updatePositionJoueur(){

	// Calcul de case pour les colisions !
	/*************************************** VERS LE HAUT ******************************/
	if (boolMovePlayerTop) {

		*ptrPositionJoueurY -= scrollingSpeed;
		// Putain tu va ou la ? On sort pas de la map gros lâche !
		// -24 mesuré au pixel prêt
		if (*ptrPositionJoueurY < -39) {
			*ptrPositionJoueurY = -39;

			if ((ofGetElapsedTimeMillis()-timerTrollAie)/1000 > 5 ){
				sound.play();
				timerTrollAie = ofGetElapsedTimeMillis();
			}

		// colision arbre / rocher
		} else if ( *(ptrTabContentCase + returnPosCaseX("center") + returnPosCaseY("top") * 120 -1 ) == 1
			|| *(ptrTabContentCase + returnPosCaseX("center") + returnPosCaseY("top") * 120 - 1) == 2){
				
			// si position joueur < returnposeY(top soit les pied ) => bloque
			if ( *ptrPositionJoueurY < returnPosCaseY("top") * 64 + 12 && returnPosJoueurX("center") > 12 && returnPosJoueurX("center") < 52){
					*ptrPositionJoueurY = returnPosCaseY("top")*64 + 12;
			}

		// colision case pleine ( Ex eau )
		} else if (*(ptrTabContentTerrain + returnPosCaseX("center") + returnPosCaseY("top") * 120 - 1) == 1) {

			// si position joueur < returnposeY(top soit les pied ) => bloque
			if (*ptrPositionJoueurY < returnPosCaseY("top") * 64 + 12) {
				*ptrPositionJoueurY = returnPosCaseY("top") * 64 + 12;
			}

		} else if (*(ptrTabContentTerrain + returnPosCaseX("center") + returnPosCaseY("bottom") * 120 - 1) == 2) {

			// si position joueur < returnposeY(top soit les pied ) => bloque
			if (*ptrPositionJoueurY < returnPosCaseY("bottom") * 64) {
				// on reviens en arrière
				*ptrPositionJoueurY += scrollingSpeed;
				// on affecte le déplacement ralenti
				*ptrPositionJoueurY -= scrollingSpeed/slowMudCase;

			}

		}

	}

	/*************************************** VERS LA DROITE ******************************/
	if (boolMovePlayerRight) {

		*ptrPositionJoueurX += scrollingSpeed;
		printf("%d=%d\n", *(ptrTabContentTerrain + returnPosCaseX("right") + returnPosCaseY("bottom") * 120 - 1),1);
		printf("r:%d \t b:%d\n", returnPosCaseX("right"), returnPosCaseY("bottom"));
		if (*ptrPositionJoueurX > 7640) {
			*ptrPositionJoueurX = 7640;
		// colision arbre ( tout sauf la pointe )
		} else if( *(ptrTabContentCase + returnPosCaseX("center") + returnPosCaseY("bottom")*120 -1) == 1
				   || *(ptrTabContentCase + returnPosCaseX("center") + returnPosCaseY("bottom") * 120 - 1) == 2 ){
			printf("HIT COLISION RIGHT ARBRE\n");
			// si la position X est > au coté gauche arbre, on stop ( l'arbre commence a 15px )
			if ( *ptrPositionJoueurX > returnPosCaseX("right")*64+40 && *ptrPositionJoueurY > returnPosCaseY("origin")*64+15 ){
				
				*ptrPositionJoueurX = returnPosCaseX("right") * 64+40;
			
			}
		// colission avec case pleine ( ex eau )
		} else if (*(ptrTabContentTerrain + returnPosCaseX("right") + returnPosCaseY("bottom") * 120 - 1) == 1) {
			
			printf("%d>%d\n", *ptrPositionJoueurX+38, returnPosCaseX("right") * 64);
			if (*ptrPositionJoueurX+38 > returnPosCaseX("right") * 64){
				*ptrPositionJoueurX = returnPosCaseX("right") * 64-38;
			}

		}

	}
	/*************************************** VERS LE BAS ******************************/
	if (boolMovePlayerDown) {

		*ptrPositionJoueurY += scrollingSpeed;
		if (*ptrPositionJoueurY > 5060) {
			*ptrPositionJoueurY = 5060;
		}

	}
	/*************************************** VERS LA GAUCHE ******************************/
	if (boolMovePlayerLeft) {

		*ptrPositionJoueurX -= scrollingSpeed;
		if (*ptrPositionJoueurX < -24) {
			*ptrPositionJoueurX = -24;
		}

	}



}
// origin / center / left / Right
int moving::returnPosCaseX(string ancre) {
	if (ancre == "origin") {
		// Par rapport au pt 0.0 de la sprite
		return (*ptrPositionJoueurX) / 64;
	} else if (ancre=="center"){
		// Par rapport au centre de ses pieds
		return (*ptrPositionJoueurX+32)/64;
	} else if (ancre == "left") {
		return (*ptrPositionJoueurX + 42) / 64;
	} else if (ancre == "Right") {
		return (*ptrPositionJoueurX + 64) / 64;
	// m'enerve ces warnings d emerde !
	} else {
		return *ptrPositionJoueurX / 64;
	}
}
// origin / bottom / top
int moving::returnPosCaseY(string ancre) {

	// ptroriginX = centre Sprite de base !

	// Par rapport au bas de ses pieds
	if (ancre == "origin") {
		// Par rapport au pt 0.0 de la sprite
		return (*ptrPositionJoueurY) / 64;
	} else if (ancre == "bottom") {
		// a la limite BASSE de ses pieds
		return (*ptrPositionJoueurY + 60) / 64;
	} else if (ancre == "top") {
		// pour les déplacement vers le haut, limite de ses pieds - 5 px
		return (*ptrPositionJoueurY + 28) / 64;
	// m'enerve ces warnings d emerde !
	} else {
		return *ptrPositionJoueurY / 64;
	}

}
int moving::returnPosJoueurX(string ancre){
	// entre les pieds du joueur
	if (ancre=="center"){
		return (*ptrPositionJoueurX+32)%64;
	}
}