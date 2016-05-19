#pragma once
#include "ofMain.h"

class Projectile{

	// pointer
	int *ptrPositionJoueurX;
	int *ptrPositionJoueurY;
	int *ptrWidthScreen;
	int *ptrHeightScreen;
	int *ptrTabContentRessourcePlayer;

	// gestion du son
	ofSoundPlayer needAmmo;
	ofImage iconProjectile,hitSangZombie;

	// gère la direction des projectiles
	// fonctionne en 8 quadrants : haut, haut droite, droite, droit bas, bas, bas gauche, gauche, haut gauche
	bool projectileGoTop = false;
	bool projectileGoDown = false;
	bool projectileGoRight = false;
	bool projectileGoLeft = false;

	// vitesse de rotation ( en ms )
	int speedRotation = 50;
	// vitesse de mouvement ( en pixel )
	int speedMoving = 15;

	// incrément typre ressource lancé
	// Start -1 car on incrémente systématiquement et vérif ensuite
	int typeRessourceLaunch = -1;

	// timer need Ammo evite la répétition abusive
	int tpsNeedAmmoSoundPlay;
	
	public:

		/****************************************** VARIABLE PUBLIC *****************************************/
		// true pour afficher
		bool isActive = false;
		bool isHitZombie = false;
		// position map
		int positionXOnTheMap, positionYOnTheMap;
		// gère le temps d'affichage du hit sang
		int tpsHitsangZombie = 0;

		// position du zombie hit ( pour animation hit sang )
		int posXZombieHit = 0;
		int posYZombieHit = 0;


		/****************************************** METHODE PUBLIC *****************************************/
		Projectile();
		void init(int *ptrPositionJoueurX,int *ptrPositionJoueurY,int *ptrWidthScreen,int *ptrHeightScreen,int *ptrTabContentRessourcePlayer);
		// la position du clic ( détermine la trajectoire à suivre )
		void initDirectionProjectile(int destinationX,int destinationY);
		// mets à jours la position du projectile
		void updatePosition();
		// affiche le projectile si dans la zone d'affichage
		void displayProjectile();
		// retourne la position du clic cureur vis a vis de la camera
		int decalageCameraX();
		// retourne la position du clic cureur vis a vis de la camera
		int decalageCameraY();
		// calcul la position de depart du projectile et renvoi le X
		int calculPositionXSpawn();
		// calcul la position de depart du projectile et renvoi le Y
		int calculPositionYSpawn();
		// active le projectile et défini sa position de depart
		void spanwProjectile();
		// retourne la valeur X sur l'affichage
		int posAffichageX();
		// retourne la valeur Y sr l''affichage
		int posAffichageY();
		void drawHitSangZombie();

		int returnIndexOfCase();

		// calcul la position d'affichage du sang
		int posAffichageSangX();
		// calcul la position d'affichage du sang
		int posAffichageSangY();

		bool playerHaveEnoughRessource();

		// gère le choix du projectile selon le stock disponible
		// + décrémente le stock
		void choiceProjectile();

		// besoin de munition
		void needAmmoSound();

};