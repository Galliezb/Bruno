#pragma once
#include "ofmain.h"
class BarreDeVie{

	// pointeur taille écran
	int *ptrWidthScreen;
	int *ptrHeightScreen;
	float pointDeVie, pointDeSprint, pointDeVoltage, maxPointDeVie, maxPointDeVoltage, maxPointDeSprint;

public:
	BarreDeVie();
	void displayBarreVie();
	void init(int *ptrWidthScreen, int *ptrHeightScreen);
	// param = quantité + type (vie,voltage,sprint)
	void modifiePointDeVie(int);
	void modifiePointDeSprint(int);
	void modifiePointDeVoltage(int);

	ofImage bdvie;
};

