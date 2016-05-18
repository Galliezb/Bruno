#include "ClassProjectile.h"

Projectile::Projectile(){

	iconProjectile.loadImage("iconInventaire.png");

}

void Projectile::init(int * ptrPositionJoueurX, int * ptrPositionJoueurY, int * ptrWidthScreen, int * ptrHeightScreen, int * ptrTabContentRessourcePlayer){
	this->ptrPositionJoueurX = ptrPositionJoueurX;
	this->ptrPositionJoueurY = ptrPositionJoueurY;
	this->ptrWidthScreen = ptrWidthScreen;
	this->ptrHeightScreen = ptrHeightScreen;
	this->ptrTabContentRessourcePlayer = ptrTabContentRessourcePlayer;
}

void Projectile::initDirectionProjectile(int destinationX, int destinationY){

	// active le projectile ( nécessaire à l'affichage )
	// et défini sa position de départ ( X et Y )
	spanwProjectile();

	// 8 Quadrants !!
	// HAUT ( mais en coordonnée !!! 0.0 etant en haut à gauche )
	printf("Souris : %d / %d\n",destinationX+decalageCameraX(),destinationY+decalageCameraY());
	if ( destinationY+decalageCameraY() < *ptrPositionJoueurY-32 && destinationX+decalageCameraX() > *ptrPositionJoueurX && destinationX+decalageCameraX() < *ptrPositionJoueurX+64){
		projectileGoTop = true;
		projectileGoDown = false;
		projectileGoLeft = false;
		projectileGoRight = false;
	// HAUT DROIT
	} else if (destinationX+decalageCameraX() > *ptrPositionJoueurX+64 && destinationY+decalageCameraY() < *ptrPositionJoueurY ){
		projectileGoTop = true;
		projectileGoDown = false;
		projectileGoLeft = false;
		projectileGoRight = true;
	// DROITE
	} else if (destinationX+decalageCameraX() > *ptrPositionJoueurX+64 && destinationY+decalageCameraY() > *ptrPositionJoueurY && destinationY+decalageCameraY() < *ptrPositionJoueurY + 64) {
		projectileGoTop = false;
		projectileGoDown = false;
		projectileGoLeft = false;
		projectileGoRight = true;
	// BAS DROIT
	} else if (destinationX+decalageCameraX() > *ptrPositionJoueurX+64 && destinationY+decalageCameraY() > *ptrPositionJoueurY+ 32 ){
		projectileGoTop = false;
		projectileGoDown = true;
		projectileGoLeft = false;
		projectileGoRight = true;
	// BAS
	} else if (destinationY+decalageCameraY() > *ptrPositionJoueurY+ 32 && destinationX+decalageCameraX() > *ptrPositionJoueurX && destinationX+decalageCameraX() < *ptrPositionJoueurX+64) {
		projectileGoTop = false;
		projectileGoDown = true;
		projectileGoLeft = false;
		projectileGoRight = false;
	// BAS GAUCHE
	} else if (destinationX+decalageCameraX() < *ptrPositionJoueurX && destinationY+decalageCameraY() > *ptrPositionJoueurY+64 ) {
		projectileGoTop = false;
		projectileGoDown = true;
		projectileGoLeft = true;
		projectileGoRight = false;
	// GAUCHE
	} else if (destinationX+decalageCameraX() < *ptrPositionJoueurX && destinationY+decalageCameraY() > *ptrPositionJoueurY && destinationY+decalageCameraY() < *ptrPositionJoueurY+64) {
		projectileGoTop = false;
		projectileGoDown = false;
		projectileGoLeft = true;
		projectileGoRight = false;
	// HAUT GAUCHE
	} else if (destinationX+decalageCameraX() < *ptrPositionJoueurX && destinationY+decalageCameraY() < *ptrPositionJoueurY) {
		projectileGoTop = true;
		projectileGoDown = false;
		projectileGoLeft = true;
		projectileGoRight = false;
	} else {
		// sens non trouvé, désactivation projectile
		isActive = false;
	}


}
void Projectile::updatePosition() {

	if (isActive){

		if ( projectileGoTop ){ 
			positionYOnTheMap-= speedMoving;
		} else if (projectileGoDown) { 
			positionYOnTheMap+= speedMoving;
		}
	
		if (projectileGoRight) { 
			positionXOnTheMap+= speedMoving;
		} else if (projectileGoLeft) { 
			positionXOnTheMap-= speedMoving;
		}

		// vérifie l'existence du projectile
		if ( posAffichageX() == -1 || posAffichageY() == -1 ){
			// Projectile Hors de vision, on le fait despawn
			isActive = false;
		}

	}

}

void Projectile::displayProjectile(){
	// caillou = 5*55
	iconProjectile.drawSubsection(posAffichageX(),posAffichageY(),35,35,275,0,55,55);
}
int Projectile::decalageCameraX(){
	int decalage = *ptrPositionJoueurX + 32 - *ptrWidthScreen / 2;

	if (decalage<1) {
		decalage = 0;
	}
	else if (decalage> 7680 - *ptrWidthScreen) {
		decalage = 7680 - *ptrWidthScreen;
	}
	return decalage;
}
int Projectile::decalageCameraY() {
	int decalage = *ptrPositionJoueurY + 32 - *ptrHeightScreen / 2;

	if (decalage<1) {
		decalage = 0;
	} else if (decalage> 5120 - *ptrHeightScreen) {
		decalage = 5120 - *ptrHeightScreen;
	}
	return decalage;
}
int Projectile::calculPositionXSpawn() {

	int posXCamera = *ptrPositionJoueurX + 32 - *ptrWidthScreen / 2;

	if (posXCamera<1) {
		posXCamera = 0;
	} else if (posXCamera> 7680 - *ptrWidthScreen) {
		posXCamera = 7680 - *ptrWidthScreen;
	}
	printf("X =>%d - %d = %d\n", *ptrPositionJoueurX,posXCamera, *ptrPositionJoueurX - posXCamera);
	return *ptrPositionJoueurX - posXCamera;

}
int Projectile::calculPositionYSpawn() {

	int posYCamera = *ptrPositionJoueurY + 32 - *ptrHeightScreen / 2;

	if (posYCamera<1) {
		posYCamera = 0;
	}
	else if (posYCamera> 5120 - *ptrHeightScreen) {
		posYCamera = 5120 - *ptrHeightScreen;
	}
	printf("Y =>%d - %d = %d\n", *ptrPositionJoueurY, posYCamera, *ptrPositionJoueurY - posYCamera);
	return *ptrPositionJoueurY - posYCamera;

}

void Projectile::spanwProjectile(){

	positionXOnTheMap = *ptrPositionJoueurX;
	positionYOnTheMap = *ptrPositionJoueurY;

	isActive = true;

}

int Projectile::posAffichageX() {

	//position par défaut de la caméra : *ptrPositionJoueurX + 32 - *ptrWidthScreen / 2;
	int posXcamera = *ptrPositionJoueurX - *ptrWidthScreen / 2;
	if (posXcamera<1) {
		posXcamera = 0;
	}
	else if (posXcamera> 7680 - *ptrWidthScreen) {
		posXcamera = 7680 - *ptrWidthScreen;
	}


	if (positionXOnTheMap > posXcamera && positionXOnTheMap < posXcamera + *ptrWidthScreen) {

		// par defaut positionXOnTheMap - cote gauche de l'affichage
		return positionXOnTheMap - posXcamera;
	}
	else {
		// donc on affiche pas le zombi
		return -1;
	}

}
int Projectile::posAffichageY() {

	int posYcamera = *ptrPositionJoueurY - *ptrHeightScreen / 2;
	if (posYcamera<1) {
		posYcamera = 0;
	}
	else if (posYcamera> 5120 - *ptrHeightScreen) {
		posYcamera = 5120 - *ptrHeightScreen;
	}


	if (positionYOnTheMap > posYcamera && positionYOnTheMap < posYcamera + *ptrHeightScreen) {

		// par defaut posZombi - cote haut de l'affichage
		return positionYOnTheMap - posYcamera;
	}
	else {
		// donc on affiche pas
		return -1;
	}

}
