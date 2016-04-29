/*
Made by Galliez Bruno
Version : 5.0
But : Gérer la map
COPYRIGHT : TOUCHE PAS A CA PETIT CON !
*/
#include <math.h>
#include "classMap.h"


/*************************** CONSTRUCTEUR ********************************/
classMap::classMap() {
	// voir init. OF n'est pas encore dispo quand on appelle certaine fonction.
	// Le setup d'OF qui permet un accès total appelera donc un init();
}
void classMap::init(int *ptrOriginX, int *ptrOriginY, int *ptrWidthScreen, int *ptrHeightScreen, int *ptrTabContentCase, int *ptrTtabContentTerrain) {
	arbre.loadImage("arbre.png");
	herbe.loadImage("herbe.jpg");
	boue.loadImage("boue.jpg");
	eau.loadImage("eau.jpg");
	rocher.loadImage("rocher.png");
	cadre.loadImage("cadre.png");
	fbo.allocate(widthImage,heightImage);

	// pointeur tab content map
	this->ptrTabContentCase = ptrTabContentCase;
	this->ptrTabContentTerrain = ptrTtabContentTerrain;

	// taille écran disponible ici ?
	this->ptrHeightScreen = ptrHeightScreen;
	this->ptrWidthScreen = ptrWidthScreen;

	printf("Initialisation MAP :  \n");

	this->ptrOriginX = ptrOriginX;
	this->ptrOriginY = ptrOriginY;
	

	/******************************* GENERATION MAP ************************************/
	bool succes = false;
	// on rempli la carte d'herbe.
	succes = remplirHerbe();
	
	// on ajoute une case d'eau
	succes = changeCaseWater(5, 5);
	succes = changeCaseWater(10, 11);
	succes = changeCaseWater(10, 12);
	succes = changeCaseWater(11, 10);
	succes = changeCaseWater(11, 11);
	succes = changeCaseWater(11, 12);
	
	// ajoute des arbres de manière aleatoire
	succes = addRessourceRandom(true, false);


	// test ajoute des rochers de manière aleatoire
	succes = addRessourceRandom(false, true);

	
	seeDataOfThisFuckingTab();

}
/******************************* HERBE ************************************/
bool classMap::remplirHerbe(){

	fbo.begin();
	ofClear(255, 255, 255, 0);

	for (int x = 0; x<120; x++) {
		for (int y = 0; y<80; y++) {
			herbe.draw(x*64,y*64);
			*(ptrTabContentTerrain + x + y*120 - 1) = 0;
			cadre.draw(x * 64, y * 64);
		}
	}
	fbo.end();
	
	return true;

}
bool classMap::restoreGrass(int posX, int posY){

	if (posX > 119 || posX < 0 || posY > 79 || posY < 0) {
		printf("Coordonnees incorrect, la case sort de la map\n");
		return false;
	} else {
		fbo.begin();
		herbe.draw(posX *64, posY *64);
		fbo.end();
		*(ptrTabContentTerrain + posX + posY * 120 - 1) = 0;
		return true;
	}
}
/******************************** EAU *************************************/
bool classMap::changeCaseWater( unsigned int posX, unsigned int posY){

	// on verifie que le lac sort pas de la map
	if ( posX > 119 || posX < 0 || posY > 79 || posY < 0){
		printf("Coordonnees incorrect, le lac sort de la map\n");
		return false;
	} else {
		fbo.begin();
		eau.draw(posX*64,posY*64);
		*(ptrTabContentTerrain + posX + posY * 120 - 1) = 2;
		fbo.end();
		return true;
	}
	
}
/******************************** ARBRE OU ROCHER *************************************/
bool classMap::addRessource(unsigned int posX, unsigned int posY, bool arbre, bool rocher){

	// on verifie que l'arbre sort pas de la map
	if ( posX > 119 || posX < 0 || posY > 79 || posY < 0){
		if (arbre && !rocher) {
			printf("Coordonnees incorrect, le rocher sort de la map");
		} else if (!arbre && rocher) {
			printf("Coordonnees incorrect, l'arbre sort de la map");
		}
		return false;
	} else {
		//fbo.begin();
		// Si le terrain = herbe + Case vide
		if (*(ptrTabContentTerrain + posX + posY * 120 - 1) == 0 && *(ptrTabContentCase + posX + posY * 120 - 1) == 0){
			if ( arbre && !rocher ){

				//this->arbre.draw(posX *64, posY *64,64,64);
				fbo.begin();
				this->arbre.draw(posX*64,posY*64,64,64);
				fbo.end();
				// on ajoute la disponibilité de l'arbre dans le tableau de donnée
				*(ptrTabContentCase + posX + posY * 120 - 1) = 1;

			} else if ( !arbre && rocher ){
				fbo.begin();
				this->rocher.draw(posX*64,posY*64);
				fbo.end();
				// on ajoute la disponibilité du rocher dans le tableau de donnée
				*(ptrTabContentCase + posX + posY * 120 - 1) = 2;
			}
		} /*else {
			printf("[ERROR][%d][%d]\t T:%d\t C:%d\n", posX, posY, *(ptrTabContentTerrain + posX + posY * 120 - 1), *(ptrTabContentCase + posX + posY * 120 - 1));
		}*/
		//fbo.end();
		affichage.update();
		return true;
	}

}
/********************* ARBRE OU ROCHER ALEATOIRE *****************************/
bool classMap::addRessourceRandom( bool arbre, bool rocher){

	srand(time(NULL));
	int alea = 0;
 
	for (int x=0;x<120;x++){
		for(int y=0;y<80;y++){
			alea = rand()%101;
			if ( alea < 15 ){
				addRessource(x,y,arbre,rocher);
				Sleep(1);
			}
		}
	}
	return true;
}

// tu comprend pas quoi dans DISPLAY ?
void classMap::displayMap(){
	fbo.getTexture().drawSubsection(0, 0, *ptrWidthScreen, *ptrHeightScreen, limitCameraX(), limitCameraY(), *ptrWidthScreen, *ptrHeightScreen);
}
// Limit = la camera ne sort plus de la carte !
// Bonjour les calculs de position joueurs, putain comment deux variable peuvent ne pas s'incrémenter
// a la même vitesse bordel de merde ! Faut trouver pourquoi ! Piste = OF ferait-il du threading ce con ?
int classMap::limitCameraX() {

	if (*ptrOriginX<1) {
		return 0;
	} else if (*ptrOriginX>(7680 - *ptrWidthScreen)) {
		return 7680 - *ptrWidthScreen;
	} else {
		return *ptrOriginX;
	}
}
int classMap::limitCameraY() {
	if (*ptrOriginY<1){
		return 0;
	} else if (*ptrOriginY>(5120 - *ptrHeightScreen)) {
		return 5120 - *ptrHeightScreen;
	} else {
		return *ptrOriginY;
	}
}
// retourne la postion X et Y du clic correspondant au COORDONNES MAP ( pas en pixel ! )
void classMap::returnPosCase(int coordX, int coordY){

	// sort les valeurs de bordure de map et les restaure sur des valeurs correctes.
	int caseX = *ptrOriginX;
	int caseY = *ptrOriginY;
	if (caseX < 0 ){ caseX = 0; }
	if (caseY < 0) { caseY = 0; }
	if (caseX > 7680 - *ptrWidthScreen ) { caseX = 7680 - *ptrWidthScreen; }
	if (caseY > 5120 - *ptrHeightScreen) { caseY = 5120 - *ptrHeightScreen; }


	caseX = floor((caseX + coordX) / 64);
	caseY = floor((caseY + coordY) / 64);

	printf("Case X => %d \tCase Y => %d\t Case => %d \t Terrain =>%d \n",caseX,caseY, *(ptrTabContentCase + caseX + caseY * 120 - 1), *(ptrTabContentTerrain + caseX + caseY * 120 - 1));
}

// Oui WTF, quand ça merde, ca fait chier. Mais bon c'est toujours
// mieux que d'être constipé non ?
void classMap::seeDataOfThisFuckingTab(){

	for(int x=0;x<120;x++){
		for(int y=0;y<80;y++){
			//printf("[%d/%d] : C:%d T:%d\n",x,y, *(ptrTabContentCase + x + y * 120 - 1), *(ptrTabContentTerrain + x + y * 120 - 1));
		}
	}

}