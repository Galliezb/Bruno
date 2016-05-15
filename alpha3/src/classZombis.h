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
	ClassZombi *ptrTabZombis;
	int *ptrMaxIndexPtrTabZombis;

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

	// ecart entre les collisions de zombis
	int ecartDeCollision = 25;



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
		void init(int *ptrPositionJoueurX, int *ptrPositionJoueurY, int *ptrWidthScreen, int *ptrHeightScreen, int *ptrTabContentCase, int *ptrTabContentTerrain, string *ptrPlayerCurrentAction, ClassZombi *ptrTabZombis, int *ptrMaxIndexPtrTabZombis);
		// affichage des zombis présent à l'écran
		void displayZombi();
		// déplace le zombi
		void moveZombi();
		// active le zombi et défini ses paramètres
		void spawnZombi();
		// vérifie la distance entre joueur et zombi
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
		// renvoi l'index de la case ou le zombi sera après déplacement
		int returnIndexCaseZombi();
		int returnPositionCaseZombiX();
		int returnPositionCaseZombiY();
		// voit le position X du zombi sur la case en cours.
		int returnPosOnTheCaseX();
		// voit le position Y du zombi sur la case en cours.
		int returnPosOnTheCaseY();
		// verification qu'un autre zombi n'est pas à portée pour bloquer le déplacement
		bool returnZombiCollisionProximity(bool top, bool right, bool down, bool left);

};