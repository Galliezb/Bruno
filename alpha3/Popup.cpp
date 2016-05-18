#include "PopUp.h"




PopUp::PopUp()
{
}

void PopUp::initPopUp()
{
	hfImage.loadImage("haut_fait.png");
	pop.loadFont("arial.ttf", 15, true);
	popDeux.loadFont("arial.ttf", 8, true);
}

void PopUp::majPopUp(string title, string description)
{
	windowX = ofGetWindowWidth();
	windowY = ofGetWindowHeight();
	titrePop = title;
	ecritFait = description;

	if (faitHaut)
	{
		windowX = ofGetWindowWidth();
		windowY = ofGetWindowHeight();


	}
	if (faitHaut == false)
	{
		if (windowX < ofGetWindowWidth()) {
			windowX += xMove;
			windowY += yMove;
		}
	}
}

void PopUp::drawPopUp()
{
	if (faitHaut)
	{
		hfImage.draw(windowX - 350, windowY - 250, 350, 250);
		pop.drawString(titrePop, windowX - 280, windowY - 100);
		ofSetColor(255);

		popDeux.drawString(ecritFait, windowX - 280, windowY - 75);
		ofSetColor(255);
	}

}


PopUp::~PopUp()
{
}
