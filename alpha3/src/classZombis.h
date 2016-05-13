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
	string *ptrPlayerCurrentAction;

	// ofimage
	ofImage zombiMarche, zombiAttaque;
	ofPath repere;

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
		void init(int *ptrPositionJoueurX, int *ptrPositionJoueurY, int *ptrWidthScreen, int *ptrHeightScreen, int *ptrTabContentCase, int *ptrTabContentTerrain, string *ptrPlayerCurrentAction);
		// affichage des zombis pr�sent � l'�cran
		void displayZombi();
		// d�place le zombi
		void moveZombi();
		// active le zombi et d�fini ses param�tres
		void spawnZombi();
		// v�rifie la distance entre joueur et zombi
		int distanceBetweenPLayerAndZombi();

		/****************************************** VARIABLE PUBLIC *****************************************/
		int speedZombi = 1;
		// vitesse d'animation en ms
		int speedAnim = 55;
		bool boolMoveZombiLeft = false;
		bool boolMoveZombiRight = false;
		bool boolMoveZombiTop = false;
		bool boolMoveZombiDown = false;
		// le zombis est-il spawn ?
		bool isSpawnZombi = false;
		// renvoi l'index de la case ou le zombi sera apr�s d�placement
		int returnIndexCaseZombi();
		int returnPositionCaseZombiX();
		int returnPositionCaseZombiY();
		// voit le position X du zombi sur la case en cours.
		int returnPosOnTheCaseX();
		// voit le position Y du zombi sur la case en cours.
		int returnPosOnTheCaseY();
};