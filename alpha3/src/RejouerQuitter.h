#pragma once
#include "ofMain.h"
class RejouerQuitter
{
public:
	RejouerQuitter();
	~RejouerQuitter();
	void initBoutonStatistique();
	void ajoutBoutonStatistique();
	ofImage bouton, boutonSur;
	ofTrueTypeFont font;
};

