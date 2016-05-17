#pragma once
#include "ofMain.h"
#include <cstdlib>
#include <ctime>
#include "../apps/Bruno/alpha3/src/classeMoving.h"
class Meteo
{
private:
	int *ptrPositionJoueurX;
	int *ptrPositionJoueurY;
	int *ptrWidthScreen;
	int *ptrHeightScreen;
public:
	Meteo();
	~Meteo();
	void initMeteo(int *ptrPositionJoueurX, int *ptrPositionJoueurY, int *ptrWidthScreen, int *ptrHeightScreen);
	void dessineNuage();
	int posAffichageX();
	int posAffichageY();
	void majNuage();
	ofImage cumulus;
	int cumulusposY;
	int cumulusposX;
	int tailleXNuage, tailleYNuage;
	ofFbo fbo;


};

