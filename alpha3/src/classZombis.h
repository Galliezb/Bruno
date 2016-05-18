#pragma once
#include "ofMain.h"
#include "BarreDeVie.h"

class ClassZombi {

	/****************************************** VARIABLE PRIVATE *****************************************/
	bool AnimMortEnCours=false;
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
	// instance barre de vie
	BarreDeVie *ptrInstancebarreDeVie;


	// ofimage
	ofImage zombiMarche, zombiAttaque, zombiMort;
	ofPath repere;

	// variable de temps pour l'animation
	int tpsStart;

	// positionnage :D
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

	// dommage zombes, negatif car on retire de la barre de vie
	int damage = -5;

	int pointDeVie = 10;

	/****************************************** METHODE PRIVATE *****************************************/
	void setTimerStart();
	int getDiffTime();
	int posAffichageX();
	int posAffichageY();

	// affiche l'animation d'attaque
	void displayAttackZombi();
	int isZombieDead();
	bool animDeathZombiDone = false;
	public :

		/****************************************** METHODE PUBLIC *****************************************/
		ClassZombi();
		void init(int *ptrPositionJoueurX, int *ptrPositionJoueurY, int *ptrWidthScreen, int *ptrHeightScreen, int *ptrTabContentCase, int *ptrTabContentTerrain, string *ptrPlayerCurrentAction, ClassZombi *ptrTabZombis, int *ptrMaxIndexPtrTabZombis, BarreDeVie *ptrInstancebarreDeVie);
		// affichage des zombis présent à l'écran
		void displayZombi();
		// déplace le zombi
		void moveZombi();
		// active le zombi et défini ses paramètres
		void spawnZombi();
		// vérifie la distance entre joueur et zombi
		int distanceBetweenPLayerAndZombi();

		/****************************************** VARIABLE PUBLIC *****************************************/
		// positionnage :D
		int posXZombi, posYZombi;
		// vitesse zombi
		int speedZombi = 1;
		// point de vie du zombi
		int health;
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
		//animation mort du zombie
		void AnimDeathZombie();
		void receiveDamage(int damage);
		bool getAnimMort();
};