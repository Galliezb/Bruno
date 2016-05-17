#include "Meteo.h"



Meteo::Meteo()
{
}


Meteo::~Meteo()
{
}

void Meteo::initMeteo(int *ptrPositionJoueurX, int *ptrPositionJoueurY, int *ptrWidthScreen, int *ptrHeightScreen)
{
	this->ptrPositionJoueurX = ptrPositionJoueurX;
	this->ptrPositionJoueurY = ptrPositionJoueurY;
	this->ptrWidthScreen = ptrWidthScreen;
	this->ptrHeightScreen = ptrHeightScreen;
		cumulus.loadImage("cumulus.png");
		
		cumulusposX = ofRandom(8160);
		cumulusposY = ofRandom(5120);
		tailleXNuage = ofRandom(800);
		tailleYNuage = ofRandom(600);
}
void Meteo::majNuage()
{
	cumulusposX-=ofRandom(2);
	//cout << posAffichageX() << "\n";
	
}
void Meteo::dessineNuage()
{
	if (posAffichageX() <= -1400)
	{
		cumulusposX = 8960;
		//cout << "j'ai respawn";
	}
	fbo.begin();
	
		if (posAffichageX() != -1 && posAffichageY() != -1)
		{
			cumulus.getTexture().draw(posAffichageX(), posAffichageY(), tailleXNuage, tailleYNuage);
		}
	fbo.end();
}
int Meteo::posAffichageX() {

	//position par défaut de la caméra : *ptrPositionJoueurX + 32 - *ptrWidthScreen / 2;
	int posXcamera = *ptrPositionJoueurX + 32 - *ptrWidthScreen / 2;
	if (*ptrPositionJoueurX + 32 > 7680 - *ptrWidthScreen/2)
	{
		posXcamera = 7680 -*ptrWidthScreen;
	}
	/*if (*ptrPositionJoueurX + 32 > 7680 - *ptrWidthScreen)
	{
		posXcamera = 7680 - *ptrWidthScreen;
	}*/
	if (posXcamera<1) {
		posXcamera = 0;
	}
	
	/*else if (posXcamera> 8160) {
		posXcamera = 8160 - *ptrWidthScreen;
	}*/
	if (cumulusposX > posXcamera - 800 && cumulusposX < posXcamera + 800 + *ptrWidthScreen) {
		// par defaut posZombi - cote gauche de l'affichage
		return cumulusposX - posXcamera-800;	
	}
	else {
		// donc on affiche pas le zombi
		return -1;
	}
}
int Meteo::posAffichageY() {

	int posYcamera = *ptrPositionJoueurY + 32 - *ptrHeightScreen / 2;
	if (posYcamera<1) 
	{
		posYcamera = 0;
	}
	else if (posYcamera> 5120 - *ptrHeightScreen) {
		posYcamera = 5120 - *ptrHeightScreen;
	}
	if (cumulusposY > posYcamera - 600 && cumulusposY < posYcamera + 600 + *ptrHeightScreen) {

		// par defaut posZombi - cote haut de l'affichage
		return cumulusposY - posYcamera;

	}
	else {
		// donc on affiche pas
		return -1;
	}
	

}