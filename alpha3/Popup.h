#pragma once
#include "ofMain.h"
class PopUp
{
public:
	PopUp();
	~PopUp();
	void majPopUp(string title, string description);
	void initPopUp();
	void drawPopUp();
	int windowX, windowY;
	ofImage hautFait;
	int xMove = 10;
	int yMove : 5;
	bool faitHaut = true;
	ofImage hfImage;
	ofTrueTypeFont pop, popDeux;
	string titrePop;
	string ecritFait;

};

