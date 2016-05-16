#include "ClassProjectile.h"

Projectile::Projectile(){
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
	isActive = true;

	// 8 Quadrants !!
	// va vers le haut ( mais en coordonnée !!! 0.0 etant en haut à gauche )
	if ( destinationY < *ptrWidthScreen / 2 - 64 && destinationX > *ptrWidthScreen / 2 - 64 && destinationX < *ptrWidthScreen / 2 + 64){
		projectileGoTop = true;
		projectileGoDown = false;
		projectileGoLeft = false;
		projectileGoRight = false;
		printf("haut\n");
	// Diagonale Haut Droite
	} else if (destinationX > *ptrWidthScreen / 2 + 64 && destinationY > *ptrHeightScreen / 2 - 64 ){
		projectileGoTop = true;
		projectileGoDown = false;
		projectileGoLeft = false;
		projectileGoRight = true;
		printf("Diagonale haut droite\n");
	// A droite toute mon capitaine
	} else if (destinationX > *ptrWidthScreen / 2 + 64 && destinationY > *ptrHeightScreen / 2 - 64 && destinationY < *ptrHeightScreen / 2 + 64) {
		projectileGoTop = false;
		projectileGoDown = false;
		projectileGoLeft = false;
		projectileGoRight = true;
		printf("droite\n");
		// diagonale bas
	} else if (destinationX > *ptrWidthScreen / 2 + 64 && destinationY > *ptrHeightScreen / 2 + 64 ){
		projectileGoTop = false;
		projectileGoDown = true;
		projectileGoLeft = false;
		projectileGoRight = true;
		printf("Diagonale bas droite\n");
	// Vers le bas
	} else if (destinationY > *ptrHeightScreen / 2 + 64 && destinationX > *ptrWidthScreen / 2 - 64 && destinationX < *ptrWidthScreen / 2 + 64) {
		projectileGoTop = false;
		projectileGoDown = true;
		projectileGoLeft = false;
		projectileGoRight = false;
		printf("Vers le bas\n");
	// diagonale bas gauche
	} else if (destinationX < *ptrWidthScreen / 2 -64 && destinationY > *ptrHeightScreen / 2 + 64 ) {
		projectileGoTop = false;
		projectileGoDown = true;
		projectileGoLeft = true;
		projectileGoRight = false;
		printf("diagonale bas gauche\n");
	// A gauche toute mon capitaine !
	} else if (destinationX < *ptrWidthScreen / 2 -64 && destinationY > *ptrHeightScreen / 2 - 64 && destinationY < *ptrHeightScreen / 2 + 64) {
		projectileGoTop = false;
		projectileGoDown = false;
		projectileGoLeft = true;
		projectileGoRight = false;
		printf("Vers la gauche\n");
	// diagonale haut gauche
	} else if (destinationX < *ptrWidthScreen / 2 - 64 && destinationY > *ptrHeightScreen / 2 - 64 && destinationY < *ptrHeightScreen / 2 + 64) {
		projectileGoTop = true;
		projectileGoDown = false;
		projectileGoLeft = true;
		projectileGoRight = false;
		printf("Vers le coin haut gauche\n");
	} else {
		// sens non trouvé, désactivation projectile
		isActive = false;
	}


}

void Projectile::moveProjectile(){

	

}
