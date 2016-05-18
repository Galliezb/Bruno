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
	//nuage
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

	//pluie
	void initPluie();
	void TombePluie();
	void MajPluie();
	int movePluieX = -40,movePluieY=-40;
	ofImage pluie;
	ofSoundPlayer orage;
	bool dessinePluie = false;
	bool pleutIl();
	//timer
	void setDepartTimer();
	
	int getDifferenceTime();
	int getDepartTimer();
	long indentationCompteur =210000;
	long tempsDepart=0;
	



};

