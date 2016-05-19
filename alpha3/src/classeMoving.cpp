#pragma once
#include "classeMoving.h"

moving::moving() {
	marche.loadImage("animmarche.png");
	courir.loadImage("animcourir.png");
	repos.loadImage("animrepos.png");
	construire.loadImage("animconstruire.png");
	degat.loadImage("animdegat.png");
	hacher.loadImage("animhacher.png");
	miner.loadImage("animminer.png");
	mort.loadImage("animmort.png");
	attaquer.loadImage("animattaquer.png");

	for (int i=1; i<18; i++){
		string str = "aie";
		string num = ofToString(i);
		string extension = ".mp3";
		string file = str + num + extension;
		leSonDegatRecu[i].load(file);
	}
	leSonMinage.load("mining.mp3");
	leSonArbre.load("coupeArbre.mp3");

}
// initialisation de la classe ( OF dispo ici, pas dans le constructeur )
void moving::init(int *ptrPositionJoueurX, int *ptrPositionJoueurY, int *ptrWidthScreen, int *ptrHeightScreen, string *ptrPlayerCurrentAction, int *ptrTabContentCase, int *ptrTtabContentTerrain, int *ptrTabContentRessourcePlayer, classMap *ptrInstanceGestionMap, BarreDeVie *ptrInstancebarreDeVie) {

	// pointeur tab content map
	this->ptrTabContentCase = ptrTabContentCase;
	this->ptrTabContentTerrain = ptrTtabContentTerrain;

	// ajout des adresses pointeurs vers la position joueur
	this->ptrHeightScreen = ptrHeightScreen;
	this->ptrWidthScreen = ptrWidthScreen;

	this->ptrPositionJoueurX = ptrPositionJoueurX;
	this->ptrPositionJoueurY = ptrPositionJoueurY;

	// recoit l'accès a l'instance de la map
	this->ptrInstanceGestionMap=ptrInstanceGestionMap;

	// action en cours du joueur
	this->ptrPlayerCurrentAction = ptrPlayerCurrentAction;

	// tableau contenant le ressource joueur
	this->ptrTabContentRessourcePlayer = ptrTabContentRessourcePlayer;

	// instance barre de vie
	this->ptrInstancebarreDeVie = ptrInstancebarreDeVie;
}

void moving::movePlayer() {

	
	// vitesse d'animation
	speedAnim = 50;
	//Animation marche

	// metes l'action joueur en repos s'il n'y est pas
	/*
	if (*ptrPlayerCurrentAction != "repos") {
		*ptrPlayerCurrentAction = "repos";
	}*/


	// Right and left prioritaire !
	if (boolMovePlayerLeft == true) {

		marche.drawSubsection(midX(), midY(), 64, 64, 64 * startCycleAnimationLeft, 0, 64, 64);
		if (getDiffTime() > speedAnim) {
			startCycleAnimationLeft++;
			setTimerStart();
		}
		if (startCycleAnimationLeft == 64) { startCycleAnimationLeft = 48; }

	}
	else if (boolMovePlayerRight == true) {

		marche.drawSubsection(midX(), midY(), 64, 64, 64 * startCycleAnimationRight, 0, 64, 64);
		if (getDiffTime() > speedAnim) {
			startCycleAnimationRight++;
			setTimerStart();
		}
		if (startCycleAnimationRight == 32) { startCycleAnimationRight = 16; }


	}
	else if (boolMovePlayerTop == true) {

		marche.drawSubsection(midX(), midY(), 64, 64, 64 * startCycleAnimationTop, 0, 64, 64);
		if (getDiffTime() > speedAnim) {
			startCycleAnimationTop++;
			setTimerStart();
		}
		if (startCycleAnimationTop == 16) { startCycleAnimationTop = 0; }

	}
	else if (boolMovePlayerDown == true) {

		marche.drawSubsection(midX(), midY(), 64, 64, 64 * startCycleAnimationDown, 0, 64, 64);
		if (getDiffTime() > speedAnim) {
			startCycleAnimationDown++;
			setTimerStart();
		}
		if (startCycleAnimationDown == 48) { startCycleAnimationDown = 32; }
		//Animation repos
	}
	else {
		playerAction();
	}
}

// Gère les animations du personnage au repos.
void moving::playerAction() {

	// rectangle autour du joueur
	/*
	ofSetColor(255, 0, 0);
	ofDrawRectangle(midX(), midY(), 64, 64);
	ofNoFill();
	ofSetColor(255, 255, 255);
	*/

	if (*ptrPlayerCurrentAction == "construire") {
		action = construire;
		speedAnim = 50;
	}
	else if (*ptrPlayerCurrentAction == "courir") {
		action = courir;
		speedAnim = 75;
	}
	else if (*ptrPlayerCurrentAction == "degat") {
		action = degat;
		speedAnim = 50;
	}
	else if (*ptrPlayerCurrentAction == "hacher") {
		action = hacher;
		speedAnim = 80;
	}
	else if (*ptrPlayerCurrentAction == "miner") {
		action = miner;
		speedAnim = 80;
	}
	else if (*ptrPlayerCurrentAction == "mort") {
		action = mort;
		speedAnim = 100;
	}
	else if (*ptrPlayerCurrentAction == "attaquer") {
		action = attaquer;
		speedAnim = 50;
	}
	else {
		action = repos;
		speedAnim = 50;
	}

	// joue les son récolte arbre et minage
	if (actionRecolteEnCours && (startCycleAnimationLeft == 57
		|| startCycleAnimationRight == 25
		|| startCycleAnimationTop == 9
		|| startCycleAnimationDown == 41)) {
		if (*ptrPlayerCurrentAction == "miner"){
			leSonMinage.play();
		} else if (*ptrPlayerCurrentAction == "hacher") {
			leSonArbre.play();
		}

	}

	// Right and left prioritaire !
	if (lastmoveRight == true) {

		action.drawSubsection(midX(), midY(), 64, 64, 64 * startCycleAnimationRight, 0, 64, 64);

		if (getDiffTime() > speedAnim) {
			startCycleAnimationRight++;
			setTimerStart();

			// joue le son aie et retire les PV
			if (*ptrPlayerCurrentAction == "degat" && startCycleAnimationRight == 31) {
				leSonDegatRecu[cptSoundAie].play();
				cptSoundAie++;
				if (cptSoundAie == 17) { cptSoundAie = 1; }
			}


		}
		if (startCycleAnimationRight == 32) { startCycleAnimationRight = 16; }

	} else if (lastmoveLeft == true) {

		action.drawSubsection(midX(), midY(), 64, 64, 64 * startCycleAnimationLeft, 0, 64, 64);
		if (getDiffTime() > speedAnim) {
			startCycleAnimationLeft++;
			setTimerStart();

			// joue le son aie et retire les PV
			if (*ptrPlayerCurrentAction == "degat" && startCycleAnimationLeft == 63) {
				leSonDegatRecu[cptSoundAie].play();
				cptSoundAie++;
				if (cptSoundAie == 17) { cptSoundAie = 1; }
			}


		}
		if (startCycleAnimationLeft == 64) { startCycleAnimationLeft = 48; }


	} else if (lastmoveTop == true) {

		action.drawSubsection(midX(), midY(), 64, 64, 64 * startCycleAnimationTop, 0, 64, 64);
		if (getDiffTime() > speedAnim) {
			startCycleAnimationTop++;
			setTimerStart();

			// joue le son aie et retire les PV
			if (*ptrPlayerCurrentAction == "degat" && startCycleAnimationTop == 15) {
				leSonDegatRecu[cptSoundAie].play();
				cptSoundAie++;
				if (cptSoundAie == 17) { cptSoundAie = 1; }
			}


		}
		if (startCycleAnimationTop == 16) { startCycleAnimationTop = 0; }

		// position repos de base, face vers l'utilisateur pardi !
	} else {

		action.drawSubsection(midX(), midY(), 64, 64, 64 * startCycleAnimationDown, 0, 64, 64);
		if (getDiffTime() > speedAnim) {
			startCycleAnimationDown++;
			setTimerStart();

			// joue le son aie et retire les PV
			if (*ptrPlayerCurrentAction == "degat" && startCycleAnimationDown == 47) {
				leSonDegatRecu[cptSoundAie].play();
				cptSoundAie++;
				if (cptSoundAie == 17) { cptSoundAie = 1; }
			}


		}
		if (startCycleAnimationDown == 48) { startCycleAnimationDown = 32; }

	}

}
// Gère l'animation déplacement du joueur 
// + réinitialise l'état du cycle animation si mouvement = stop
// + stocke l'etat du dernier déplacement
void moving::setBoolMovePlayerTop(bool b) {
	boolMovePlayerTop = b;
	if (!b) { startCycleAnimationTop = 0; }
	if (!boolMovePlayerRight && !boolMovePlayerDown && !boolMovePlayerLeft) {
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
bool moving::getBoolMovePlayerTop() {
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
int moving::midX() {

	int  posXCamera = *ptrPositionJoueurX + 32 - *ptrWidthScreen / 2;

	if (posXCamera<1) {
		posXCamera = 0;
	}
	else if (posXCamera> 7680 - *ptrWidthScreen) {
		posXCamera = 7680 - *ptrWidthScreen;
	}

	return *ptrPositionJoueurX - posXCamera;

}
int moving::midY() {

	int posYCamera = *ptrPositionJoueurY + 32 - *ptrHeightScreen / 2;

	if (posYCamera<1) {
		posYCamera = 0;
	}
	else if (posYCamera> 5120 - *ptrHeightScreen) {
		posYCamera = 5120 - *ptrHeightScreen;
	}

	return *ptrPositionJoueurY - posYCamera;

}
void moving::setTimerStart() {
	tpsStart = ofGetElapsedTimeMillis();
}
int moving::getDiffTime() {
	return ofGetElapsedTimeMillis() - tpsStart;
}
// Gère le déplacement  + la colision avec les objets
void moving::updatePositionJoueur() {

	// si on se déplace mais qu'une action de récolte en cours, on la stop
	if (actionRecolteEnCours){
		actionRecolteEnCours = false;
		*ptrPlayerCurrentAction = "repos";
	}

	// Calcul de case pour les colisions !
	/*************************************** VERS LE HAUT ******************************/
	if (boolMovePlayerTop) {

		*ptrPositionJoueurY -= scrollingSpeed;
		// Putain tu va ou la ? On sort pas de la map gros lâche !
		// -24 mesuré au pixel prêt
		if (*ptrPositionJoueurY < -39) {
			*ptrPositionJoueurY = -39;

			if ((ofGetElapsedTimeMillis() - timerTrollAie) / 1000 > 5) {
				leSonDegatRecu[cptSoundAie].play();
				timerTrollAie = ofGetElapsedTimeMillis();
			}

			// colision arbre / rocher
		}
		else if (*(ptrTabContentCase + returnPosCaseX("center") + returnPosCaseY("top") * 120 - 1) == 1
			|| *(ptrTabContentCase + returnPosCaseX("center") + returnPosCaseY("top") * 120 - 1) == 2) {

			// si position joueur < returnposeY(top soit les pied ) => bloque
			if (*ptrPositionJoueurY < returnPosCaseY("top") * 64 + 6
				&& *ptrPositionJoueurX + 32 > returnPosCaseX("center") * 64 + 12
				&& *ptrPositionJoueurX + 32 < returnPosCaseX("center") * 64 + 52) {
				*ptrPositionJoueurY = returnPosCaseY("top") * 64 + 6;
			}

			// colision case pleine ( Ex eau )
		}
		else if (*(ptrTabContentTerrain + returnPosCaseX("center") + returnPosCaseY("top") * 120 - 1) == 1) {

			// si position joueur < returnposeY(top soit les pied ) => bloque
			if (*ptrPositionJoueurY < returnPosCaseY("top") * 64 + 12) {
				*ptrPositionJoueurY = returnPosCaseY("top") * 64 + 12;
			}

		}
		else if (*(ptrTabContentTerrain + returnPosCaseX("center") + returnPosCaseY("bottom") * 120 - 1) == 2) {

			// si position joueur < returnposeY(top soit les pied ) => bloque
			if (*ptrPositionJoueurY < returnPosCaseY("bottom") * 64) {
				// on reviens en arrière
				*ptrPositionJoueurY += scrollingSpeed;
				// on affecte le déplacement ralenti
				int plus = scrollingSpeed / slowMudCase;
				if (!plus) { plus++; }
				*ptrPositionJoueurY -= plus;
			}

		}

	}

	/*************************************** VERS LA DROITE ******************************/
	if (boolMovePlayerRight) {
		*ptrPositionJoueurX += scrollingSpeed;
		if (*ptrPositionJoueurX > 7640) {
			*ptrPositionJoueurX = 7640;
			// colision arbre ( tout sauf la pointe )
		}
		else if ((*(ptrTabContentCase + returnPosCaseX("center") + returnPosCaseY("bottom") * 120 - 1) == 1
			|| *(ptrTabContentCase + returnPosCaseX("center") + returnPosCaseY("bottom") * 120 - 1) == 2)
			&& *ptrPositionJoueurX + 32 - returnPosCaseX("center") * 64 < 30) {
			// si la position X est > au coté gauche arbre, on stop ( l'arbre commence a 15px )
			if (*ptrPositionJoueurX > returnPosCaseX("center") * 64 - 20 && *ptrPositionJoueurY + 60 > returnPosCaseY("bottom") * 64 + 15) {
				*ptrPositionJoueurX = returnPosCaseX("center") * 64 - 20;

			}
			// colission avec case pleine ( ex eau )
		}
		else if (*(ptrTabContentTerrain + returnPosCaseX("right") + returnPosCaseY("bottom") * 120 - 1) == 1) {

			if (*ptrPositionJoueurX > returnPosCaseX("right") * 64 - 40) {
				*ptrPositionJoueurX = returnPosCaseX("right") * 64 - 40;
			}

		}
		else if (*(ptrTabContentTerrain + returnPosCaseX("center") + returnPosCaseY("bottom") * 120 - 1) == 2) {

			if (*ptrPositionJoueurX + 32 > ((*ptrPositionJoueurX) / 64) * 64) {
				// on reviens en arrière
				*ptrPositionJoueurX -= scrollingSpeed;
				// on affecte le déplacement ralenti
				int plus = scrollingSpeed / slowMudCase;
				if (!plus) { plus++; }
				*ptrPositionJoueurX += plus;
			}

		}

	}
	/*************************************** VERS LE BAS ******************************/
	if (boolMovePlayerDown) {

		*ptrPositionJoueurY += scrollingSpeed;
		if (*ptrPositionJoueurY > 5060) {
			*ptrPositionJoueurY = 5060;

			// colision arbre / rocher
		}
		else if (*(ptrTabContentCase + returnPosCaseX("center") + returnPosCaseY("bottom") * 120 - 1) == 1
			|| *(ptrTabContentCase + returnPosCaseX("center") + returnPosCaseY("bottom") * 120 - 1) == 2) {

			// si position joueur < returnposeY(top soit les pied ) => bloque
			if (*ptrPositionJoueurY > returnPosCaseY("origin") * 64 + 12
				&& *ptrPositionJoueurX + 32 > returnPosCaseX("center") * 64 + 12
				&& *ptrPositionJoueurX + 32 < returnPosCaseX("center") * 64 + 52) {
				*ptrPositionJoueurY = returnPosCaseY("origin") * 64 + 12;
			}

			// colision case pleine ( Ex eau )
		}
		else if (*(ptrTabContentTerrain + returnPosCaseX("center") + returnPosCaseY("bottom") * 120 - 1) == 1) {

			// si position joueur < returnposeY(top soit les pied ) => bloque
			if (*ptrPositionJoueurY > returnPosCaseY("bottom") * 64 - 60) {
				*ptrPositionJoueurY = returnPosCaseY("bottom") * 64 - 60;
			}


		}
		else if (*(ptrTabContentTerrain + returnPosCaseX("center") + returnPosCaseY("bottom") * 120 - 1) == 2) {

			// si position joueur < returnposeY(top soit les pied ) => bloque
			if (*ptrPositionJoueurY < returnPosCaseY("bottom") * 64) {
				// on reviens en arrière
				*ptrPositionJoueurY -= scrollingSpeed;
				// on affecte le déplacement ralenti
				int plus = scrollingSpeed / slowMudCase;
				if (!plus) { plus++; }
				*ptrPositionJoueurY += plus;
			}

		}

	}
	/*************************************** VERS LA GAUCHE ******************************/
	if (boolMovePlayerLeft) {

		*ptrPositionJoueurX -= scrollingSpeed;
		if (*ptrPositionJoueurX < -24) {
			*ptrPositionJoueurX = -24;
		}


		if ((*(ptrTabContentCase + returnPosCaseX("center") + returnPosCaseY("bottom") * 120 - 1) == 1
			|| *(ptrTabContentCase + returnPosCaseX("center") + returnPosCaseY("bottom") * 120 - 1) == 2)
			&& *ptrPositionJoueurX + 32 - returnPosCaseX("center") * 64 > 34) {
			// si la position X est < au coté droite arbre, on stop ( l'arbre commence a 15px )
			if (*ptrPositionJoueurX < returnPosCaseX("center") * 64 + 21 && *ptrPositionJoueurY + 60 > returnPosCaseY("bottom") * 64 + 15) {
				*ptrPositionJoueurX = returnPosCaseX("center") * 64 + 21;

			}
			// colission avec case pleine ( ex eau )
		}
		else if (*(ptrTabContentTerrain + (*ptrPositionJoueurX / 64) + returnPosCaseY("bottom") * 120 - 1) == 1) {
			if (*ptrPositionJoueurX < (*ptrPositionJoueurX / 64) * 64 + 38) {
				*ptrPositionJoueurX = (*ptrPositionJoueurX / 64) * 64 + 38;
			}

		}
		else if (*(ptrTabContentTerrain + returnPosCaseX("center") + returnPosCaseY("bottom") * 120 - 1) == 2) {

			if (*ptrPositionJoueurX + 32 < ((*ptrPositionJoueurX + 32) / 64) * 64 + 64) {
				// on reviens en arrière
				*ptrPositionJoueurX += scrollingSpeed;
				// on affecte le déplacement ralenti
				int plus = scrollingSpeed / slowMudCase;
				if (!plus) { plus++; }
				*ptrPositionJoueurX -= plus;
			}

		}

	}

}
// origin / center / left / Right
int moving::returnPosCaseX(string ancre) {

	if (ancre == "origin") {
		// Par rapport au pt 0.0 de la sprite
		return *ptrPositionJoueurX / 64;
	}
	else if (ancre == "center") {
		// Par rapport au centre de ses pieds
		return (*ptrPositionJoueurX + 32) / 64;
	}
	else if (ancre == "left") {
		return (*ptrPositionJoueurX + 42) / 64;
	}
	else if (ancre == "right") {
		return (*ptrPositionJoueurX + 64) / 64;
		// m'enerve ces warnings d emerde !
	}
	else {
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
	}
	else if (ancre == "bottom") {
		// a la limite BASSE de ses pieds
		return (*ptrPositionJoueurY + 60) / 64;
	}
	else if (ancre == "top") {
		// pour les déplacement vers le haut, limite de ses pieds - 5 px
		return (*ptrPositionJoueurY + 28) / 64;
		// m'enerve ces warnings de merde !
	}
	else {
		return *ptrPositionJoueurY / 64;
	}

}

int moving::returnPosJoueurX(string ancre) {
	// entre les pieds du joueur
	if (ancre == "center") {
		return (*ptrPositionJoueurX + 32) % 64;
	}
	else {
		return *ptrPositionJoueurX % 64;
	}
}

void moving::actionRecolteStart() {

	if ( !actionRecolteEnCours ){

		// 1° on récupère les coordonnées
		posXActionRecolte = returnPosCaseX("center");
		// le top = haut de ses pieds
		if ( lastmoveDown ){
			posYActionRecolte = returnPosCaseY("bottom");
		} else {
			posYActionRecolte = (*ptrPositionJoueurY+50)/64;
		}

		// retire une bug de sens du personnage lorsqu'il coupe un arbre ou mine
		if ((lastmoveLeft || lastmoveRight) && (*ptrPositionJoueurX - (*ptrPositionJoueurX / 64) * 64) < 32) {
			lastmoveLeft = true;
		}
		else if ((lastmoveLeft || lastmoveRight) && (*ptrPositionJoueurX - (*ptrPositionJoueurX / 64) * 64) > 32) {
			lastmoveRight = true;
		}

		// c'est un arbre ?
		if (*(ptrTabContentCase + posXActionRecolte + posYActionRecolte * 120 - 1) == 1 && !lastmoveDown) {
			
			*ptrPlayerCurrentAction = "hacher";
			tpsStartActionRecolte = ofGetElapsedTimeMillis();
			actionRecolteEnCours = true;

		// c'est un rocher ?
		} else if (*(ptrTabContentCase + posXActionRecolte + posYActionRecolte * 120 - 1) == 2) {
			*ptrPlayerCurrentAction = "miner";
			tpsStartActionRecolte = ofGetElapsedTimeMillis();
			actionRecolteEnCours = true;
		}
		

	}

}

bool moving::actionRecolteEnd(){

	// si le joueur prend des dégâts, la récolte s'interrompt
	if (*ptrPlayerCurrentAction == "degat"){
		actionRecolteEnCours = false;
	}

	if (actionRecolteEnCours) {

		if (ofGetElapsedTimeMillis() - tpsStartActionRecolte > 5000 ){			
			// +1 arbre ?
			if (*(ptrTabContentCase + posXActionRecolte + posYActionRecolte * 120 - 1) == 1) {
				*(ptrTabContentRessourcePlayer)+=1;
			// + 1 rocher ?
			} else if (*(ptrTabContentCase + posXActionRecolte + posYActionRecolte * 120 - 1) == 2) {
				*(ptrTabContentRessourcePlayer+1)+=1;
			}
			// on remets l'action par defaut
			*ptrPlayerCurrentAction = "repos";
			// on cloture l'action en cours
			actionRecolteEnCours = false;

			// on corrige la map
			// PUTAIN on passe par le pointeur de l'instance ! C'est trop énorme !
			ptrInstanceGestionMap->restoreTerrainWithoutRessource(posXActionRecolte, posYActionRecolte);

			// action fini plus de verif necessaire
			return false;
		} else {
			// action en cours, verif nécessaire dans ofApp
			return true;
		}

	} else {
		// previens ofApp que l'action est annulé
		return false;
	}

}


