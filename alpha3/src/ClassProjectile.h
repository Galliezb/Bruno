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
	ofImage iconProjectile;

	// gère la direction des projectiles
	// fonctionne en 8 quadrants : haut, haut droite, droite, droit bas, bas, bas gauche, gauche, haut gauche
	bool projectileGoTop = false;
	bool projectileGoDown = false;
	bool projectileGoRight = false;
	bool projectileGoLeft = false;

	// position map
	int positionXOnTheMap, positionYOnTheMap;
	// vitesse de rotation ( en ms )
	int speedRotation = 50;
	// vitesse de mouvement ( en pixel )
	int speedMoving = 5;
	
	public:

		/****************************************** VARIABLE PUBLIC *****************************************/
		bool isActive = false;


		/****************************************** METHODE PUBLIC *****************************************/
		Projectile();
		void init(int *ptrPositionJoueurX,int *ptrPositionJoueurY,int *ptrWidthScreen,int *ptrHeightScreen,int *ptrTabContentRessourcePlayer);
		// la position du clic ( détermine la trajectoire à suivre )
		void initDirectionProjectile(int destinationX,int destinationY);
		// mets à jours la position du projectile
		void updatePosition();
		// affiche le projectile si dans la zone d'affichage
		void displayProjectile();
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
		

};