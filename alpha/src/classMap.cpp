/*
Made by Galliez Bruno
Version : 5.0
But : G�rer la map
COPYRIGHT : TOUCHE PAS A CA PETIT CON !
*/
#include <math.h>
#include "classMap.h"


/*************************** CONSTRUCTEUR ********************************/
classMap::classMap() {
	// voir init. OF n'est pas encore dispo quand on appelle certaine fonction.
	// Le setup d'OF qui permet un acc�s total appelera donc un init();
}
void classMap::init(int *ptrOriginX, int *ptrOriginY, int *ptrWidthScreen, int *ptrHeightScreen) {
	arbre.loadImage("arbre.png");
	herbe.loadImage("herbe.jpg");
	boue.loadImage("boue.jpg");
	eau.loadImage("eau.jpg");
	rocher.loadImage("rocher.png");
	fbo.allocate(widthImage,heightImage);

	// taille �cran disponible ici ?
	this->ptrHeightScreen = ptrHeightScreen;
	this->ptrWidthScreen = ptrWidthScreen;

	printf("Initialisation MAP :  \n");

	this->ptrOriginX = ptrOriginX;
	this->ptrOriginY = ptrOriginY;
	

	/******************************* GENERATION MAP ************************************/
	bool succes = false;
	// on rempli la carte d'herbe.
	succes = remplirHerbe();
	
	/*
	// on ajoute un zone d'eau
	succes = ajoutLac(10, 10);
	
	*/
	// test ajoute des arbres de mani�re aleatoire
	//succes = addTreeRandom();
	
	/*
	// test ajoute des rochers de mani�re aleatoire
	succes = addStoneRandom();
	
	*/
	// update de l'affichage
	//updateMapScreen();

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
bool classMap::restoreGrass(int posCaseX, int posCaseY){

	if (posCaseX > 119 || posCaseX < 0 || posCaseY > 79 || posCaseY < 0) {
		printf("Coordonnees incorrect, la case sort de la map\n");
		return false;
	} else {

		if ( tabContentMap[posCaseX][posCaseY][1] != 0 ){
			fbo.begin();
			herbe.draw(posCaseX,posCaseY);
			fbo.end();
		}
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
		eau.draw(posX,posY);
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
				// r�up�re un tableau de 64*64*3
				for (int i = posX * 64; i<posX * 64 + 64; i++) {
					for (int j = posY * 64; j<posY * 64 + 64; j++) {
						affichage.setColor(i, j, this->arbre.getColor(i,j));
					}
				}

				// on ajoute la disponibilit� de l'arbre dans le tableau de donn�e
				tabContentMap[posX][posY][1] = 1;

			} else if ( !arbre && rocher ){
				//this->rocher.draw(posX *64, posY *64,64,64);
				for (int i = posX * 64; i<posX * 64 + 64; i++) {
					for (int j = posY * 64; j<posY * 64 + 64; j++) {
						affichage.setColor(i, j, this->rocher.getColor(i, j));
					}
				}

				// on ajoute la disponibilit� du rocher dans le tableau de donn�e
				tabContentMap[posX][posY][1] = 2;
			}
		} else {
			printf("[ERROR] => pas d'arbre ni de rocher dans la flotte bordel de merde !\n");
		}
		//fbo.end();
		ofLogVerbose() << "DEBUT update()";
		affichage.update();
		ofLogVerbose() << "FIN update()";
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

				if ( alea < 15 ){
					if (arbre && !rocher) {
						this->arbre.draw(x * 64, y * 64, 64, 64);
						// position Arbre => tab donn�e
						tabContentMap[x][y][1] = 1;
					}
					else if (!arbre && rocher) {
						this->rocher.draw(x * 64, y * 64, 64, 64);
						// position Arbre => tab donn�e
						tabContentMap[x][y][1] = 2;
					}
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

		// on remets de l'herbe
		for (int i = posX * 64; i<posX * 64 + 64; i++) {
			for (int j = posY * 64; j<posY * 64 + 64; j++) {
				int start = (j * 64 + i)*3;
				affichage.setColor(i, j, ofColor(tabPixelHerbe[start+2], tabPixelHerbe[start+1], tabPixelHerbe[start]));
			}
		}

		// mise a jour tableau
		tabContentMap[posX][posY][1] = 0;
		// update image
		affichage.update();
		return true;

	}

}
/*************************** SUPPRIMER UN ROCHER ********************************/
bool classMap::removeStone(unsigned int posX, unsigned int posY, bool arbre, bool rocher){
	removeTree(posX, posY, false, true);
	return true;
}

/*************************** SAUVEGARDER L'IMAGE ********************************/
/*
void classMap::saveMap() {

	// Est-ce utile de conserver ceci ? on peut recr�er l'image depuis un tableau de donn�
	// et l'utilis� directement dans ofImage au besoin.



	//on stock les pixels de l'image en low-level pour passer d'un objet � l'autre
	// PUTAIN C'ETAIT CHIANT A COMPRENDRE CA !   
	unsigned char* pixels = new unsigned char[widthImage*heightImage * 3]; ;
	ofImage saveImage;
	saveImage.allocate(widthImage, heightImage, OF_IMAGE_COLOR);
	saveImage.setUseTexture(false);

	// On copie les pixel de FBO vers OFIMAGE qui poss�de la fonction d'enregistrement en fichier
	fbo.begin();
	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glReadPixels(0, 0, fbo.getWidth(), fbo.getHeight(), GL_RGB, GL_UNSIGNED_BYTE, pixels);
	saveImage.setFromPixels(pixels, fbo.getWidth(), fbo.getHeight(), OF_IMAGE_COLOR);
	saveImage.saveImage("output.jpg", OF_IMAGE_QUALITY_BEST);
	fbo.end();
	ofLog(OF_LOG_VERBOSE, "Image is safe ! Coffee time !");
}
*/


/**************************** UPDATER L'AFFICHAGE *********************************/
void classMap::updateMapScreen() {

	/*
	NOTE : 
	1) FBO pourrait afficher avec le .draw mais devrait recalculer l'image a chaque frame => trop gourmand
	2) S'il est n�cessaire d'optimiser, on peut mettre � jour l'image d'OFIMAGE en passant par du low level
	   et en ne modifiant que les pixels qui doivent �tre chang�.
	   Mais la pour une raison de temps, on le fait mode bourrin et on recharge tous les pixels !
	3) la doc dit de faire un .update() apr�s la modification des pixels manuellement.
	4) ne pas oublier que "affichage" poss�de des m�thodes pour r�cup�rer l'�tat des pixels !
	CCL => optimsation m�moire, faudra bosser ici !
	*/

	// info voir au dessus
	unsigned char* pixels = new unsigned char[widthImage * heightImage * 3];

	fbo.begin();
	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glReadPixels(0, 0, fbo.getWidth(), fbo.getHeight(), GL_RGB, GL_UNSIGNED_BYTE, pixels);
	affichage.setFromPixels(pixels, fbo.getWidth(), fbo.getHeight(), OF_IMAGE_COLOR);
	affichage.update();

	//affichage.saveImage("outputTest.jpg", OF_IMAGE_QUALITY_MEDIUM);
	fbo.end();
	ofLog(OF_LOG_VERBOSE, "Image FBO transf�r� dans OfImage pour l'affichage ( mise a jour OK )");
}

void classMap::displayMap(){
	fbo.getTexture().drawSubsection(0, 0, *ptrWidthScreen, *ptrHeightScreen, limitCameraX(), limitCameraY(), *ptrWidthScreen, *ptrHeightScreen);
}
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

	for (int i=caseX*64; i<caseX*64+64; i++){
		for (int j=caseY*64; j<caseY*64+64; j++) {
			affichage.setColor(i,j, ofColor(255, 62, 191) );
		}
	}

	
	affichage.update();
	

}