/*
Made by Galliez Bruno
Version : 3.0
But : Gérer la map
*/
#include "ofMain.h"
#include <math.h>

class classMap{
	private :
		ofImage arbre,boue,eau,herbe,rocher;
		ofFbo fbo;
		bool moveCameraLeft = false;
		bool moveCameraRight = false;
		bool moveCameraUp = false;
		bool moveCameraDown = false;
		int widthImage = 7680;
		int heightImage = 5120;
		int speedScaleCamera = 1;

		// pointeur position joueur
		int *ptrOriginX, *ptrOriginY;
		int *ptrWidthScreen, *ptrHeightScreen;
		// pointeur tableau contenu MAP
		int *ptrTabContentCase, *ptrTabContentTerrain;

public :

		ofImage affichage;

		classMap();
		void init(int *ptrOriginX, int *ptrOriginY, int *ptrWidthScreen, int *ptrHeightScreen, int *ptrTabContentCase, int *ptrTabContentTerrain);
		// Gestion de l'herbe
		bool remplirHerbe();
		bool restoreGrass(int posX, int posY);

		// les ressources
		bool changeCaseWater( unsigned int posX, unsigned int posY);
		bool addRessource( unsigned int posX, unsigned int posY, bool arbre = true, bool rocher = false);
		bool addRessourceRandom( bool arbre = true, bool rocher = false);

		void displayMap();
		int classMap::limitCameraX();
		int classMap::limitCameraY();

		void returnPosCase(int coordX, int coordY);
		void seeDataOfThisFuckingTab();
};