#pragma once
#include "ofMain.h"

class ClassZombi {

	/****************************************** VARIABLE PRIVATE *****************************************/

	// pointeurs
	int *ptrPositionJoueurX;
	int *ptrPositionJoueurY;
	int *ptrWidthScreen;
	int *ptrHeightScreen;
	int *ptrTabContentCase;
	int *ptrTabContentTerrain;

	// ofimage
	ofImage zombiMarche, zombiAttaque;

	// variable de temps pour l'animation
	int tpsStart;

	// positionnage :D
	int posXZombi,posYZombi;
	bool lastmoveRight = false;
	bool lastmoveLeft = false;
	bool lastmoveTop = false;
	bool lastmoveDown = false;
	// zone de la sprite a afficher
	// incrementation pour l'animation
	int startCycleAnimationTop = 0;
	int startCycleAnimationRight = 16;
	int startCycleAnimationDown = 32;
	int startCycleAnimationLeft = 48;



	/****************************************** METHODE PRIVATE *****************************************/
	void setTimerStart();
	int getDiffTime();
	int posAffichageX();
	int posAffichageY();

	// affiche l'animation d'attaque
	void displayAttackZombi();

	public :

		/****************************************** METHODE PUBLIC *****************************************/
		ClassZombi();
		void init(int *ptrPositionJoueurX, int *ptrPositionJoueurY, int *ptrWidthScreen, int *ptrHeightScreen, int *ptrTabContentCase, int *ptrTabContentTerrain);
		// affichage des zombis présent à l'écran
		void displayZombi();
		// déplace le zombi
		void moveZombi();
		// active le zombi et défini ses paramètres
		void spawnZombi();

		/****************************************** VARIABLE PUBLIC *****************************************/
		int speedZombi = 1;
		// vitesse d'animation en ms
		int speedAnim = 50;
		bool boolMoveZombiLeft = false;
		bool boolMoveZombiRight = false;
		bool boolMoveZombiTop = false;
		bool boolMoveZombiDown = false;
		// le zombis est-il spawn ?
		bool isSpawnZombi = false;
};