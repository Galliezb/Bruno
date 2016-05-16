#pragma once
#include "ofMain.h"

class classInventaire  {

	// private
	// pointeur
	int *ptrTabContentRessourcePlayer;
	int *ptrWidthScreen,*ptrHeightScreen;
	ofImage inventaire, icon;
	ofTrueTypeFont font;

	public :
		classInventaire();
		void init(int *ptrTabContentRessourcePlayer, int *ptrWidthScreen, int *ptrHeightScreen);
		void affichage();
		int returnPosXWindow();
		int returnPosYWindow();
		void fabriqueRoche();
		void fabriqueLance();
};