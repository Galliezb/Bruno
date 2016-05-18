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
	// va vers le haut ( mais en coordonnée !!! 0.0 etant en haut à gauche )
	if ( destinationY < *ptrHeightScreen / 2 - 64 && destinationX > *ptrWidthScreen / 2 - 96 && destinationX < *ptrWidthScreen / 2 + 32){
		projectileGoTop = true;
		projectileGoDown = false;
		projectileGoLeft = false;
		projectileGoRight = false;
	// Diagonale Haut Droite
	} else if (destinationX > *ptrWidthScreen / 2 + 32 && destinationY < *ptrHeightScreen / 2 - 64 ){
		projectileGoTop = true;
		projectileGoDown = false;
		projectileGoLeft = false;
		projectileGoRight = true;
	// A droite toute mon capitaine
	} else if (destinationX > *ptrWidthScreen / 2 + 64 && destinationY > *ptrHeightScreen / 2 - 64 && destinationY < *ptrHeightScreen / 2 + 64) {
		projectileGoTop = false;
		projectileGoDown = false;
		projectileGoLeft = false;
		projectileGoRight = true;
		// diagonale bas droite
	} else if (destinationX > *ptrWidthScreen / 2 + 32 && destinationY > *ptrHeightScreen / 2 + 64 ){
		projectileGoTop = false;
		projectileGoDown = true;
		projectileGoLeft = false;
		projectileGoRight = true;
	// Vers le bas
	} else if (destinationY > *ptrHeightScreen / 2 + 64 && destinationX > *ptrWidthScreen / 2 - 96 && destinationX < *ptrWidthScreen / 2 + 32) {
		projectileGoTop = false;
		projectileGoDown = true;
		projectileGoLeft = false;
		projectileGoRight = false;
	// diagonale bas gauche
	} else if (destinationX < *ptrWidthScreen / 2 -64 && destinationY > *ptrHeightScreen / 2 + 64 ) {
		projectileGoTop = false;
		projectileGoDown = true;
		projectileGoLeft = true;
		projectileGoRight = false;
	// A gauche toute mon capitaine !
	} else if (destinationX < *ptrWidthScreen / 2 -64 && destinationY > *ptrHeightScreen / 2 - 64 && destinationY < *ptrHeightScreen / 2 + 64) {
		projectileGoTop = false;
		projectileGoDown = false;
		projectileGoLeft = true;
		projectileGoRight = false;
	// diagonale haut gauche
	} else if (destinationX < *ptrWidthScreen / 2 - 96 && destinationY < *ptrHeightScreen / 2 - 64) {
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

	positionXOnTheMap = calculPositionXSpawn();
	positionYOnTheMap = calculPositionYSpawn();

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

		// par defaut posZombi - cote gauche de l'affichage
		return positionXOnTheMap +28 - posXcamera;
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
		return positionYOnTheMap + 19 - posYcamera;
	}
	else {
		// donc on affiche pas
		return -1;
	}

}
