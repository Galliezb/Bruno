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

	// g�re la direction des projectiles
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
		// la position du clic ( d�termine la trajectoire � suivre )
		void initDirectionProjectile(int destinationX,int destinationY);
		void moveProjectile();
		

};