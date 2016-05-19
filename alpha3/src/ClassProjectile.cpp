#include "ClassProjectile.h"

Projectile::Projectile(){

	iconProjectile.loadImage("iconInventaire.png");
	hitSangZombie.loadImage("hiSangZombie.png");
	needAmmo.load("needAmo.mp3");
	tpsNeedAmmoSoundPlay = ofGetElapsedTimeMillis();

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
	//printf("Souris : %d / %d\n",destinationX+decalageCameraX(),destinationY+decalageCameraY());
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
	int spriteX = 2*55 + typeRessourceLaunch * 55;
	//printf("spriteX = %d\n");
	iconProjectile.drawSubsection(posAffichageX(),posAffichageY(),35,35,spriteX,0,55,55);
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
	//printf("posXcamera => %d\n", posXCamera);
	//printf("X =>%d - %d = %d\n", *ptrPositionJoueurX,posXCamera, *ptrPositionJoueurX - posXCamera);
	return *ptrPositionJoueurX - posXCamera;

}
int Projectile::calculPositionYSpawn() {

	int posYCamera = *ptrPositionJoueurY + 32 - *ptrHeightScreen / 2;

	if (posYCamera<1) {
		posYCamera = 0;
	} else if (posYCamera> 5120 - *ptrHeightScreen) {
		posYCamera = 5120 - *ptrHeightScreen;
	}
	//printf("posYcamera => %d\n",posYCamera);
	//printf("Y =>%d - %d = %d\n", *ptrPositionJoueurY, posYCamera, *ptrPositionJoueurY - posYCamera);
	return *ptrPositionJoueurY - posYCamera;

}

void Projectile::spanwProjectile(){

	// choisi le projectile
	choiceProjectile();

	positionXOnTheMap = *ptrPositionJoueurX-16;
	positionYOnTheMap = *ptrPositionJoueurY-8;

	if ( *ptrPositionJoueurX < *ptrWidthScreen / 2 ){
		positionXOnTheMap += 29;
	}
	if (*ptrPositionJoueurY < *ptrHeightScreen / 2) {
		positionYOnTheMap += 22;
	}

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

void Projectile::drawHitSangZombie(){
	// hit un arbre ? pas de sang !
	//printf("Hit sang en X:%d & Y:%d\n", posAffichageSangX(), posAffichageSangY());
	hitSangZombie.draw(posAffichageSangX(), posAffichageSangY(),64,64);
	isHitZombie = false;
	isActive = false;
}

int Projectile::returnIndexOfCase(){
	return ((positionXOnTheMap + 16) / 64) + ((positionYOnTheMap +40) / 64) * 120 - 1;
}

int Projectile::posAffichageSangX() {

	//position par défaut de la caméra : *ptrPositionJoueurX + 32 - *ptrWidthScreen / 2;
	int posXcamera = *ptrPositionJoueurX + 32 - *ptrWidthScreen / 2;
	if (posXcamera<1) {
		posXcamera = 0;
	}
	else if (posXcamera> 7680 - *ptrWidthScreen) {
		posXcamera = 7680 - *ptrWidthScreen;
	}


	if (posXZombieHit > posXcamera && posXZombieHit < posXcamera + *ptrWidthScreen) {

		// par defaut posZombi - cote gauche de l'affichage
		return posXZombieHit - posXcamera;

	}
	else {
		// donc on affiche pas le zombi
		return -1;
	}

}
int Projectile::posAffichageSangY() {

	int posYcamera = *ptrPositionJoueurY + 32 - *ptrHeightScreen / 2;
	if (posYcamera<1) {
		posYcamera = 0;
	}
	else if (posYcamera> 5120 - *ptrHeightScreen) {
		posYcamera = 5120 - *ptrHeightScreen;
	}


	if (posYZombieHit > posYcamera && posYZombieHit < posYcamera + *ptrHeightScreen) {

		// par defaut posZombi - cote haut de l'affichage
		return posYZombieHit - posYcamera;

	}
	else {
		// donc on affiche pas
		return -1;
	}

}

bool Projectile::playerHaveEnoughRessource(){
	// verif des cas 2,3,4,5,6
	if ( *(ptrTabContentRessourcePlayer + 2) > 0 ||
		 *(ptrTabContentRessourcePlayer + 3) > 0 ||
		 *(ptrTabContentRessourcePlayer + 4) > 0 ||
		 *(ptrTabContentRessourcePlayer + 5) > 0 ||
		 *(ptrTabContentRessourcePlayer + 6) > 0 ){
		 return true;
	} else {
		return false;
	}
}

void Projectile::choiceProjectile(){

	typeRessourceLaunch++;

	// stock insuffisant, on passe au suivant
	printf("Stock visé => %d ( 2 + %d )\n", *(ptrTabContentRessourcePlayer + 2 + typeRessourceLaunch), typeRessourceLaunch);
	if ( *(ptrTabContentRessourcePlayer + 2 + typeRessourceLaunch) < 1 ){
		choiceProjectile();
	// décrémente le stock
	} else {
		*(ptrTabContentRessourcePlayer + 2 + typeRessourceLaunch) -= 1;
	}

	if (typeRessourceLaunch >= 4) { typeRessourceLaunch = 0; }

}

void Projectile::needAmmoSound(){

	if ( !needAmmo.isPlaying() && ofGetElapsedTimeMillis() - tpsNeedAmmoSoundPlay > 5000 ){
		tpsNeedAmmoSoundPlay = ofGetElapsedTimeMillis();
		needAmmo.play();
	}

}
