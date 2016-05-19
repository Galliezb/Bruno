#pragma once
#include "ofmain.h"
class BarreDeVie{

	// pointeur taille écran
	int *ptrWidthScreen;
	int *ptrHeightScreen;
	string *ptrPlayerCurrentAction;

public:
	float pointDeVie, pointDeSprint, pointDeVoltage, maxPointDeVie, maxPointDeVoltage, maxPointDeSprint;
	BarreDeVie();
	void displayBarreVie();
	void init(int *ptrWidthScreen, int *ptrHeightScreen, string *ptrPlayerCurrentAction);
	// param = quantité + type (vie,voltage,sprint)
	void modifiePointDeVie(int);
	void modifiePointDeSprint(int);
	void modifiePointDeVoltage(int);

	ofImage bdvie;
};

