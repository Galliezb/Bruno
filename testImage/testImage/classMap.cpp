/*
Made by Galliez Bruno
Version : 3.0
But : Gérer la map
*/
#include <math.h>
#include "classMap.h"


/*************************** CONSTRUCTEUR ********************************/
classMap::classMap() {
}
void classMap::init(int sizeScreenX,int sizeScreenY){
	arbre.loadImage("arbre.png");
	boue.loadImage("boue.jpg");
	eau.loadImage("eau.jpg");
	herbe.loadImage("herbe.jpg");
	rocher.loadImage("rocher.png");
	fbo.setUseTexture(false);
	fbo.allocate(widthImage,heightImage);

	// ofImage de l'affichage
	affichage.allocate(widthImage, heightImage, OF_IMAGE_COLOR);
	affichage.setUseTexture(true);

	// taille écran disponible ici ?
	sizeScreenHeight = sizeScreenX;
	sizeScreenWidth = sizeScreenY;
}
/******************************* HERBE ************************************/
bool classMap::remplirHerbe(){

	fbo.begin();
	//dessine un lac carré partout sur la map
	for(short int x=0;x<120;x++){
		for(short int y=0;y<80;y++){
			if ( y == 0 ){
				eau.draw(x*64,y*64,64,64);
				tabContentMap[x][y][0] = 2;
			} else {
				herbe.draw(x*64,y*64,64,64);
			}
		}
	}
	fbo.end();
	return true;

}
/******************************** LAC *************************************/
bool classMap::ajoutLac( unsigned int posX, unsigned int posY){

	// on verifie que le lac sort pas de la map
	if ( posX > 124 || posX < 0 || posY > 74 || posY < 0){
		printf("Coordonnees incorrect, le lac sort de la map\n");
		return false;
	} else {
		for (int cx=0;cx<5;cx++){
			for (int cy=0;cy<5;cy++){
				fbo.begin();
				eau.draw((posX*64)+(cx * 64), (posY*64)+(cy * 64), 64, 64);
				tabContentMap[cx+posX][cy+posY][0] = 2;
				tabContentMap[cx+posX][cy+posY][1] = 0;
				// par defaut la case de côte est considéré comme de l'herbe
				fbo.end();
			}
		}
		return true;
	}

}
/******************************** ARBRE *************************************/
bool classMap::addTree(unsigned int posX, unsigned int posY, bool arbre, bool rocher){

	// on verifie que l'arbre sort pas de la map
	if ( posX > 124 || posX < 0 || posY > 74 || posY < 0){
		if (arbre && !rocher) {
			ofLog(OF_LOG_VERBOSE, "Coordonnees incorrect, le rocher sort de la map");
		} else if (!arbre && rocher) {
			ofLog(OF_LOG_VERBOSE, "Coordonnees incorrect, l'arbre sort de la map");
		}
		return false;
	} else {
		fbo.begin();
		// Pas d'arbre ou rocher sur un arbre ou rocher ou de l'eau !
		if ( tabContentMap[posX][posY][0] == 0 && tabContentMap[posX][posY][1] == 0){
			if ( arbre && !rocher ){
				this->arbre.draw(posX *64, posY *64,64,64);
				// on ajoute la disponibilité de l'arbre dans le tableau de donnée
				tabContentMap[posX][posY][1] = 1;
			} else if ( !arbre && rocher ){
				this->rocher.draw(posX *64, posY *64,64,64);
				// on ajoute la disponibilité de l'arbre dans le tableau de donnée
				tabContentMap[posX][posY][1] = 2;
			}
		}
		fbo.end();
		return true;
	}

}
/********************* ARBRE ALEATOIRE *****************************/
bool classMap::addTreeRandom( bool arbre, bool rocher){

	srand(time(NULL));
	int alea = 0;
 
	for (int x=0;x<120;x++){
		for(int y=0;y<80;y++){

			fbo.begin();
			alea = rand()%101;
			// Pas d'arbre ou rocher sur un arbre ou rocher ou de l'eau !
			if (tabContentMap[x][y][0] == 0 && tabContentMap[x][y][1] == 0) {

				if (x > 9 && x < 15 && y > 9 && y < 15) {

					printf("tab[%d][%d][0] => %d / ", x, y, tabContentMap[x][y][0]);
					printf("tab[%d][%d][1] => %d VS ", x, y, tabContentMap[x][y][1]);

				}
				if ( alea < 15 ){
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
				if (x > 9 && x < 15 && y > 9 && y < 15 ){
				
					printf("tab[%d][%d][0] => %d / ",x,y, tabContentMap[x][y][0]);
					printf("tab[%d][%d][1] => %d\n ", x, y, tabContentMap[x][y][1]);

				}
			}

			fbo.end();

		}
	}
	return true;

}
			/****************************************************/
			/************ OUI JE TROUVE CA MALIN XD *************/
			/************* NON CA NE L'EST PAS XD *************/
			/****************************************************/

/******************************** ROCHER *************************************/
bool classMap::addStone(unsigned int posX, unsigned int posY, bool arbre, bool rocher) {
	this->addTree(posX,posY,false,true);
	return true;
}
/********************* ROCHER ALEATOIRE *****************************/
bool classMap::addStoneRandom(bool arbre, bool rocher) {
	this->addTreeRandom(false, true);
	return true;
}

/*************************** SUPPRIMER UN ARBRE *********************************/
bool classMap::removeTree(unsigned int posX, unsigned int posY, bool arbre, bool rocher){

	// on verifie qu'on sort pas de la map
	if (posX > 124 || posX < 0 || posY > 74 || posY < 0) {

		if (arbre && !rocher) {
			printf("Coordonnees incorrect, le rocher sort de la map\n");
		}
		else if (!arbre && rocher) {
			printf("Coordonnees incorrect, l'arbre sort de la map\n");
		}
		return false;

	} else {

		fbo.begin();
		if (arbre && !rocher) {

			if ( tabContentMap[posX][posY][1] == 1 ){
				// on mets a jour le tab données
				tabContentMap[posX][posY][1] = 0;
				herbe.draw(posX * 64, posY * 64, 64, 64);
			}

		} else if (!arbre && rocher) {
			if (tabContentMap[posX][posY][1] == 2 ) {
				tabContentMap[posX][posY][1] = 0;
				herbe.draw(posX * 64, posY * 64, 64, 64);
			}

		}
		fbo.end();
		return true;

	}

}
/*************************** SUPPRIMER UN ROCHER ********************************/
bool classMap::removeStone(unsigned int posX, unsigned int posY, bool arbre, bool rocher){
	removeTree(posX, posY, false, true);
	return true;
}

/*************************** SAUVEGARDER L'IMAGE ********************************/
void classMap::saveMap(){

	//on stock les pixels de l'image en low-level pour passer d'un objet à l'autre
	// PUTAIN C'ETAIT CHIANT A COMPRENDRE CA !   
	unsigned char* pixels = new unsigned char[widthImage*heightImage*3];  ;  
	ofImage saveImage;  
	saveImage.allocate(widthImage,heightImage,OF_IMAGE_COLOR);
	saveImage.setUseTexture(false);  

	// On copie les pixel de FBO vers OFIMAGE qui possède la fonction d'enregistrement en fichier
	fbo.begin();
	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glReadPixels(0, 0, fbo.getWidth(), fbo.getHeight(), GL_RGB, GL_UNSIGNED_BYTE, pixels);    
	saveImage.setFromPixels(pixels, fbo.getWidth(), fbo.getHeight(), OF_IMAGE_COLOR);    
	saveImage.saveImage("output.jpg", OF_IMAGE_QUALITY_BEST);  
	fbo.end();  
	ofLog(OF_LOG_VERBOSE, "Image is safe ! Coffee time !"); 
}
/********************* SET => LES BOUBOULES CA FOU LES BOULES ! ***************************/

void classMap::setBoolMoveCameraLeft(){
	(moveCameraLeft) ? moveCameraLeft=false: moveCameraLeft=true;
}
void classMap::setBoolMoveCameraRight() {
	(moveCameraRight) ? moveCameraRight = false : moveCameraRight = true;
}
void classMap::setBoolMoveCameraUp() {
	(moveCameraUp) ? moveCameraUp = false : moveCameraUp = true;
}
void classMap::setBoolMoveCameraDown() {
	(moveCameraDown) ? moveCameraDown = false : moveCameraDown = true;
}
/********************* GET => LES BOUBOULES CA FOU LES BOULES ! ***************************/
bool classMap::getBoolMoveCameraLeft() {
	return moveCameraLeft;
}
bool classMap::getBoolMoveCameraRight() {
	return moveCameraRight;
}
bool classMap::getBoolMoveCameraUp() {
	return moveCameraUp;
}
bool classMap::getBoolMoveCameraDown() {
	return moveCameraDown;
}

/**************************** UPDATER L'AFFICHAGE *********************************/
void classMap::updateMapScreen() {

	/*
	NOTE : 
	1) FBO pourrait afficher avec le .draw mais devrait recalculer l'image a chaque frame => trop gourmand
	2) S'il est nécessaire d'optimiser, on peut mettre à jour l'image d'OFIMAGE en passant par du low level
	   et en ne modifiant que les pixels qui doivent être changé.
	   Mais la pour une raison de temps, on le fait mode bourrin et on recharge tous les pixels !
	3) la doc dit de faire un .update() après la modification des pixels manuellement.
	4) ne pas oublier que "affichage" possède des méthodes pour récupérer l'état des pixels !
	CCL => optimsation mémoire, faudra bosser ici !
	*/

	// info voir au dessus
	unsigned char* pixels = new unsigned char[widthImage * heightImage * 3]; ;

	fbo.begin();
	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glReadPixels(0, 0, fbo.getWidth(), fbo.getHeight(), GL_RGB, GL_UNSIGNED_BYTE, pixels);
	affichage.setFromPixels(pixels, fbo.getWidth(), fbo.getHeight(), OF_IMAGE_COLOR);
	affichage.update();
	affichage.saveImage("outputTest.jpg", OF_IMAGE_QUALITY_MEDIUM);
	fbo.end();
	ofLog(OF_LOG_VERBOSE, "Image FBO transféré dans OfImage pour l'affichage ( mise a jour OK )");
}

void classMap::displayMap(){

	// deplacement camera ( et personnage de ce fait )
	if (moveCameraLeft){
		if (posXjoueur - speedScaleCamera > 0) {
			posXjoueur -= speedScaleCamera;
		}
	}
	if (moveCameraRight) {
		if (posXjoueur + speedScaleCamera < widthImage - sizeScreenWidth) {
			posXjoueur += speedScaleCamera;
		}
	}
	if (moveCameraUp) {
		if (posYjoueur - speedScaleCamera > 0) {
			posYjoueur -= speedScaleCamera;
		}
	}
	if (moveCameraDown) {
		if (posYjoueur + speedScaleCamera < heightImage - sizeScreenHeight) {
			posYjoueur += speedScaleCamera;
		}
	}
	printf("posXjoueur =>%d\n",posXjoueur, moveCameraLeft);
	affichage.drawSubsection(0, 0, sizeScreenWidth, sizeScreenHeight, posXjoueur, posYjoueur, sizeScreenWidth, sizeScreenHeight);
}