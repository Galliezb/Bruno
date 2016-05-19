#pragma once
#include "ofMain.h"
#include "ofxGui.h"
#include "MenuMain.h"
class ClasseLogo
{
public:
	ClasseLogo();
	~ClasseLogo();
	ofImage logo1, logo2, logo3, logo4, logoP;
	int tailleFX, tailleFY;
	void chargement();
	void initiation();
	void maj();
	bool dessin;
	float velocity;
	float gravity;
	int tmp3, tmp2;
	bool fontBlanc;
	int goMenu;
	ofSoundPlayer sonOhm;
	int col = 0;
};

