#pragma once
#include "ofMain.h"




class MenuMain
{
public:
	ofTrueTypeFont font, font2;
	ofImage button, buttonSur, fondEcran,/* buttonSonOn, buttonSonOff,*/ clavier, credit;
	MenuMain();
	~MenuMain();
	bool menuPrincipal = true;//si tout le menuprincipal est affiché
	void testAffichage();
	int tailleFX;
	int tailleFY;
	bool leJeuSeLance = true;//Bool qui permet de lancer le jeu.
	bool lanceOptionTouche = true;//bool qui permet de lancer le menu touche
	int cpt;
	int temporaire;
	bool lanceCredit = true;//Bool qui permet de lance le menu des crédits
	void aJourMenu();
//	bool son = true;








};

