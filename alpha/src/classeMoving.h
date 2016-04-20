/*
Codé par Christophe
But : gérer le personnage
*/
#pragma once
#include "ofMain.h"
class moving {

	int * ptrHeightScreen;
	int * ptrWidthScreen;


	// incrementation pour l'animation
	int startCycleAnimationTop = 0;
	int startCycleAnimationRight = 16;
	int startCycleAnimationDown = 32;
	int startCycleAnimationLeft = 48;

	// Variables pour l'arrêt du personnage
	bool lastmoveTop = false;
	bool lastmoveRight = false;
	bool lastmoveDown = true;
	bool lastmoveLeft = false;

public:

	// Variables pour l'animation de la marche du personnage

	bool goTop = false;
	bool goRight = false;
	bool goDown = false;
	bool goLeft = false;


	// fonction pour le mouvement
	ofImage marche;
	ofImage repos;

	moving();
	void init(int *ptrWidthScreen, int *ptrHeightScreen);
	void movePlayer();
	void playerWait();
	void setBoolMovePlayerTop(bool b);
	void setBoolMovePlayerRight(bool b);
	void setBoolMovePlayerDown(bool b);
	void setBoolMovePlayerLeft(bool b);
	bool getBoolMovePlayerTop();
	bool getBoolMovePlayerRight();
	bool getBoolMovePlayerDown();
	bool getBoolMovePlayerLeft();
	void moving::limitMovePlayer();
};