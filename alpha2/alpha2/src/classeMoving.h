#pragma once
#include <time.h>
#include "ofMain.h"
class moving {

	// pointeur valeur variable ofapp
	int *ptrPositionJoueurX, *ptrPositionJoueurY;
	int *ptrWidthScreen, *ptrHeightScreen;
	// pointeur tab content map
	int *ptrTabContentCase;
	int *ptrTabContentTerrain;

	// incrementation pour l'animation
	int startCycleAnimationTop = 0;
	int startCycleAnimationRight = 16;
	int startCycleAnimationDown = 32;
	int startCycleAnimationLeft = 48;
	// vitesse animation
	int speedAnim = 100;

	// Variables pour l'arr�t du personnage
	bool lastmoveTop = false;
	bool lastmoveRight = false;
	bool lastmoveDown = true;
	bool lastmoveLeft = false;

	// bool timer troll Aie
	int timerTrollAie = 0;
	ofSoundPlayer sound;

	// variable de temps
	int tpsStart, tpsStop,tpsDiff;

	// ralentissement du a la boue
	int slowMudCase = 10; // => /2 = 50% de vitesse en moins

	// Action en cours du personnage
	string  * playerCurrentAction;

	// vitesse de d�filement
	int scrollingSpeed = 10;

public:

	// Variables pour l'animation de la marche du personnage

	bool boolMovePlayerTop = false;
	bool boolMovePlayerRight = false;
	bool boolMovePlayerDown = false;
	bool boolMovePlayerLeft = false;


	// fonction pour le mouvement
	ofImage marche, courir, repos, construire, degat, hacher, miner, mort, action, attaquer;

	moving();
	void init(int *ptrPositionJoueurX, int *ptrPositionJoueurY, int *ptrWidthScreen, int *ptrHeightScreen, string *playerCurrentAction, int *ptrTabContentCase, int *ptrTtabContentTerrain);
	void playerAction();

	// m�thode de gestion du d�placement joueur
	void movePlayer();
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
	void updatePositionJoueur();

	// origin / center / left / Right
	int returnPosCaseX(string ancre);
	// origin / bottom / top
	int returnPosCaseY(string ancre);

	// d�marre l'enregistrement du temps
	void setTimerStart();
	void setTimerEnd();
	int getTimerStart();
	int getTimerEnd();
	int getDiffTime();
};