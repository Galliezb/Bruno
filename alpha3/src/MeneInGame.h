#pragma once
#include "ofMain.h"
#include "ofxGui.h"
class MeneInGame
{
public:
	MeneInGame();
	~MeneInGame();

	void inGame();
	void InitInGameMenu();
	void MenuMajInGame();


	ofImage logoFont;
	ofTrueTypeFont ecrit;
	ofImage button, buttonSur, clavier;
	int tailleX, tailleY;
	bool retourJeu = false;//bbol qui fait retourner au jeu
	bool goMenuJeu = true;//bool retour au au menu
	bool optionMusique = false;//bool qui gère l'affichage de l'option menu
	bool clavierlancer = false;//bool qui permet de montrer les touches
	bool statMenuLancer = false;//bool qui permet d'afficher la classe statistique
								//musique
	void initBarreMusique();
	void majBarreMusique();
	void dessineBarreMusique();
	bool setRetourJeu();
	bool getRetourJeu();
	float getSonMusique();
	float getSonAmbiance();
	ofxPanel gui;
	ofxPanel gui2;
	ofxFloatSlider volumeM;
	ofSoundPlayer sample;
	ofxFloatSlider volumeA;
	float volM=0, volA=0;
	ofSoundPlayer sample2;
	FILE *sauvMusique;
};

