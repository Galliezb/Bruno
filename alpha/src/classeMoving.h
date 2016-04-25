/*
Codé par Christophe
But : gérer le personnage
*/
#pragma once
#include <time.h>
#include "ofMain.h"
class moving {

	// pointeur valeur variable ofapp
	int *ptrOriginX, *ptrOriginY;
	int *ptrWidthScreen, *ptrHeightScreen;

	// incrementation pour l'animation
	int startCycleAnimationTop = 0;
	int startCycleAnimationRight = 16;
	int startCycleAnimationDown = 32;
	int startCycleAnimationLeft = 48;
	// vitesse animation
	int speedAnim = 100;

	// Variables pour l'arrêt du personnage
	bool lastmoveTop = false;
	bool lastmoveRight = false;
	bool lastmoveDown = true;
	bool lastmoveLeft = false;

	// variable de temps
	int tpsStart, tpsStop,tpsDiff;

	// Action en cours du personnage
	string  * playerCurrentAction;

	// methode private

public:

	// Variables pour l'animation de la marche du personnage

	bool goTop = false;
	bool goRight = false;
	bool goDown = false;
	bool goLeft = false;


	// fonction pour le mouvement
	ofImage marche, courir, repos, construire, degat, hacher, miner, mort, action, attaquer;

	moving();
	void init(int *ptrOriginX, int *ptrOriginY, int *ptrWidthScreen, int *ptrHeightScreen, string *playerCurrentAction);
	void movePlayer();
	void playerAction();
	void setBoolMovePlayerTop(bool b);
	void setBoolMovePlayerRight(bool b);
	void setBoolMovePlayerDown(bool b);
	void setBoolMovePlayerLeft(bool b);
	bool getBoolMovePlayerTop();
	bool getBoolMovePlayerRight();
	bool getBoolMovePlayerDown();
	bool getBoolMovePlayerLeft();
	int midX();
	int midY();

	// démarre l'enregistrement du temps
	void moving::setTimerStart();
	void moving::setTimerEnd();
	int moving::getTimerStart();
	int moving::getTimerEnd();
	int moving::getDiffTime();
};