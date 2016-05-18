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
		
		
		cumulusposX = ofRandom(7680);
		cumulusposY = ofRandom(5120);
		//cout << cumulusposY << "\n";
		tailleXNuage = ofRandom(800,200);
		tailleYNuage = ofRandom(600,200);
}
void Meteo::majNuage()
{
	cumulusposX-=ofRandom(1);
	//cout << posAffichageX() << "\n";
}

void Meteo::dessineNuage()
{
	if (posAffichageX() <= -800)
	{
		cumulusposX = ofRandom(10000,8000);
		cumulusposY = ofRandom(5120);
		//cout << "j'ai respawn";
	}
	//fbo.begin();
	
		if (posAffichageX() != -1 && posAffichageY() != -1)
		{
			cumulus./*getTexture().*/draw(posAffichageX(), posAffichageY(), tailleXNuage, tailleYNuage);
		}
	//fbo.end();
}
int Meteo::posAffichageX() {

	//position par défaut de la caméra : *ptrPositionJoueurX + 32 - *ptrWidthScreen / 2;
	int posXcamera = *ptrPositionJoueurX + 32 - *ptrWidthScreen / 2;

	if (*ptrPositionJoueurX + 32 > 7680 - *ptrWidthScreen/2)
	{
		posXcamera = 7680 -*ptrWidthScreen;
	}
	
	if (posXcamera<1) {
		posXcamera = 0;
	}
	
	/*else if (posXcamera> 8160) {
		posXcamera = 8160 - *ptrWidthScreen/2;
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
	if (posYcamera < 1)
	{
		posYcamera = 0;
	}
	else if (posYcamera > 5120 - *ptrHeightScreen) {
		posYcamera = 5120 - *ptrHeightScreen;
	}
	if (cumulusposY > posYcamera - 600 && cumulusposY < posYcamera + 600 + *ptrHeightScreen) {

		// par defaut posZombi - cote haut de l'affichage
		//printf("%d\n", cumulusposY - posYcamera);
		return cumulusposY - posYcamera;

	}
	else {
		// donc on affiche pas
		return -1;
	}
}
// pluie****************************************************************************************	
	void Meteo::initPluie()
	{
		pluie.loadImage("pluie5.png");
		orage.loadSound("tonnerre.mp3");
		orage.setVolume(0.5);
		
		
	}


	void Meteo::TombePluie()

	{
		setDepartTimer();
		//printf("%d && %d\n", tempsDepart, indentationCompteur);
		if (dessinePluie == false)
		{
			if (tempsDepart > 7000)//indentationCompteur)// 7000 est utilisé pour le test de son
			{
				orage.play();
				dessinePluie = !dessinePluie;
				indentationCompteur +=60000;
			}
			/*if (tempsDepart > 10000) {
				dessinePluie = false;
				tempsDepart = 0;
			}*/
		}
		else {
			if (tempsDepart > indentationCompteur)
			{
				
				dessinePluie = !dessinePluie;
				indentationCompteur += 210000;
			}
		}
		if (dessinePluie) {
			
			ofSetColor(200);
			pluie.draw(movePluieX, movePluieY, ofGetWindowWidth() + 40, ofGetWindowHeight() + 40);
		}
	}

	void Meteo::MajPluie()
	{
		if (movePluieX < 0)
		{
			movePluieX++;
			movePluieY++;
		}
		else {
			movePluieX = -40;
			movePluieY = -40;
		}
	}

	void Meteo::setDepartTimer()
	{
		tempsDepart = ofGetElapsedTimeMillis();
	}

	int Meteo::getDifferenceTime()
	{
		return ofGetElapsedTimeMillis() - tempsDepart;
	}

	int Meteo::getDepartTimer()
	{
		return tempsDepart;
	}

	bool Meteo::pleutIl() {
		return dessinePluie;
	}