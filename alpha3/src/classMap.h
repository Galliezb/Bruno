#pragma once
#include "ofMain.h"
#include <math.h>

class classMap{
	private :
		ofImage arbre,boue,eau,herbe,rocher,cadre;
		ofFbo fbo;
		bool moveCameraLeft = false;
		bool moveCameraRight = false;
		bool moveCameraUp = false;
		bool moveCameraDown = false;
		int widthImage = 7680;
		int heightImage = 5120;
		int speedScaleCamera = 1;

		// pointeur position joueur
		int *ptrPositionJoueurX, *ptrPositionJoueurY;
		int *ptrWidthScreen, *ptrHeightScreen;
		// pointeur tableau contenu MAP
		int *ptrTabContentCase, *ptrTabContentTerrain;

public :

		ofImage affichage;

		classMap();
		void init(int *ptrPositionJoueurX, int *ptrPositionJoueurY, int *ptrWidthScreen, int *ptrHeightScreen, int *ptrTabContentCase, int *ptrTabContentTerrain);
		// Gestion de l'herbe
		bool remplirHerbe();
		bool restoreGrass(int posX, int posY);
		void restoreTerrainWithoutRessource(int,int);

		// les ressources
		bool changeCaseWater( unsigned int posX, unsigned int posY);
		bool changeCaseMud(unsigned int posX, unsigned int posY);
		bool addRessource( unsigned int posX, unsigned int posY, bool arbre = true, bool rocher = false);
		bool addRessourceRandom( bool arbre = true, bool rocher = false);

		void displayMap();
		int limitCameraX();
		int limitCameraY();

		void returnPosCase(int coordX, int coordY);

		
};