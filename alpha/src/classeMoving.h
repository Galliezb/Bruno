/*
Codé par Christophe
But : gérer le personnage
*/
#pragma once
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
	ofImage marche, repos, construire, courir, degat, hacher, miner, mort, action;

	moving();
	void init(int *ptrOriginX, int *ptrOriginY, int *ptrWidthScreen, int *ptrHeightScreen);
	void movePlayer();
	void playerAction(string str);
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

	// les différentes action du personnage ( mourir, construire etc..
	void actionPlayerBuild();
	void actionPlayerRun();
	void actionPlayerTakeDamage();
	void actionPlayerCut();
	void actionPlayerMine();
	void actionPlayerIsDead();
};