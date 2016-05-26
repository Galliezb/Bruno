#pragma once
#include "ofMain.h"
#include "MenuMain.h"
class RejouerQuitter
{
public:
	RejouerQuitter();
	~RejouerQuitter();
	void initBoutonStatistique();
	void ajoutBoutonStatistique();
	ofImage bouton, boutonSur;
	ofTrueTypeFont font;
	bool rejouer = false;
};

