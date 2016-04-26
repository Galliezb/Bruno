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
void classMap::init(int *ptrOriginX, int *ptrOriginY, int *ptrWidthScreen, int *ptrHeightScreen) {
	arbre.loadImage("arbre.png");
	herbe.loadImage("herbe.jpg");
	boue.loadImage("boue.jpg");
	eau.loadImage("eau.jpg");
	rocher.loadImage("rocher.png");
	fbo.allocate(widthImage,heightImage);

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
	succes = addRessourceRandom(false,true);
	

}
/******************************* HERBE ************************************/
bool classMap::remplirHerbe(){

	fbo.begin();
	ofClear(255, 255, 255, 0);

	for (int x = 0; x<120; x++) {
		for (int y = 0; y<80; y++) {
			herbe.draw(x*64,y*64);
			tabContentMap[x][y][1] = 0;
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
		tabContentMap[posX][posY][1] = 0;
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
		tabContentMap[posX][posY][0] = 2;
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
		// Pas d'arbre ou rocher sur un arbre ou rocher ou de l'eau !
		if ( tabContentMap[posX][posY][0] == 0 && tabContentMap[posX][posY][1] == 0){
			if ( arbre && !rocher ){

				//this->arbre.draw(posX *64, posY *64,64,64);
				fbo.begin();
				this->arbre.draw(posX*64,posY*64);
				fbo.end();
				// on ajoute la disponibilité de l'arbre dans le tableau de donnée
				tabContentMap[posX][posY][1] = 1;

			} else if ( !arbre && rocher ){
				//this->arbre.draw(posX *64, posY *64,64,64);
				fbo.begin();
				this->rocher.draw(posX*64,posY*64);
				fbo.end();
				// on ajoute la disponibilité du rocher dans le tableau de donnée
				tabContentMap[posX][posY][1] = 2;
			}
		} else {
			printf("[ERROR] => pas d'arbre ni de rocher dans la flotte bordel de merde !\n");
		}
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

			fbo.begin();
			alea = rand()%101;
			// Pas d'arbre ou rocher sur un arbre ou rocher ou de l'eau !
			if (tabContentMap[x][y][0] == 0 && tabContentMap[x][y][1] == 0) {

				if ( alea < 10 ){
					if (arbre && !rocher) {
						this->arbre.draw(x * 64, y * 64, 64, 64);
						// position Arbre => tab donnée
						tabContentMap[x][y][1] = 1;
					}
					else if (!arbre && rocher) {
						this->rocher.draw(x * 64, y * 64, 64, 64);
						// position Arbre => tab donnée
						tabContentMap[x][y][1] = 2;
					}
				}
			}

			fbo.end();

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
void classMap::returnPosCaseClic(int posMouseX, int posMouseY){

	// sort les valeurs de bordure de map et les restaure sur des valeurs correctes.
	int x = *ptrOriginX;
	int y = *ptrOriginY;
	if ( x < 0 ){ x = 0; }
	if ( y < 0) { y = 0; }
	if (x > 7680 - *ptrWidthScreen ) { x = 7680 - *ptrWidthScreen; }
	if (y > 5120 - *ptrHeightScreen) { y = 5120 - *ptrHeightScreen; }


	int caseX = floor((x + posMouseX) / 64);
	int caseY = floor((y + posMouseY) / 64);


	// Y'a moyen de faire ça en OPENGL direct, ou VIA FBO !
	// Putain faut rebosser ça !
	// De toute façon je le supprime d'ici peu de temps :D
	for (int i=caseX*64; i<caseX*64+64; i++){
		for (int j=caseY*64; j<caseY*64+64; j++) {
			affichage.setColor(i,j, ofColor(255, 62, 191) );
		}
	}

	
	affichage.update();
	

}