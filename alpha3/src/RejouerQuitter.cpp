#include "RejouerQuitter.h"



RejouerQuitter::RejouerQuitter()
{
}


RejouerQuitter::~RejouerQuitter()
{
}

void RejouerQuitter::initBoutonStatistique()
{
	bouton.loadImage("Boutton.png");
	boutonSur.loadImage("BouttonSur.png");
	font.loadFont("CandyShop.ttf", 12, true);
}

void RejouerQuitter::ajoutBoutonStatistique()
{
	bouton.draw(ofGetWindowWidth() / 2 - 200, 700);
	bouton.draw(ofGetWindowWidth() / 2 + 100, 700);
	if (ofGetMouseX() >= ofGetWindowWidth() / 2 - 200 && ofGetMouseX() <= ofGetWindowWidth() / 2 - 100) {
		if (ofGetMouseY() >= 700 && ofGetMouseY() <= 750) {
			boutonSur.draw(ofGetWindowWidth() / 2 - 200, 700);
		}
	}
	if (ofGetMouseX() >= ofGetWindowWidth() / 2 + 100 && ofGetMouseX() <= ofGetWindowWidth() / 2 + 200) {
		if (ofGetMouseY() >= 700 && ofGetMouseY() <= 750) {
			boutonSur.draw(ofGetWindowWidth() / 2 + 100, 700);
		}
	}
	//click
	if (ofGetMouseX() >= ofGetWindowWidth() / 2 + 100 && ofGetMouseX() <= ofGetWindowWidth() / 2 + 200) {
		if (ofGetMouseY() >= 700 && ofGetMouseY() <= 750) {
			if (ofGetMousePressed()) {

				OF_EXIT_APP(0);
			}
		}
	}
	if (ofGetMouseX() >= ofGetWindowWidth() / 2 - 200 && ofGetMouseX() <= ofGetWindowWidth() / 2 - 100) {
		if (ofGetMouseY() >= 700 && ofGetMouseY() <= 750) {
			if (ofGetMousePressed()) {
				MenuMain();
			}
		}
	}

	font.drawString("Rejouer", ofGetWindowWidth() / 2 - 165, 735);
	font.drawString("Quitter", ofGetWindowWidth() / 2 + 135, 735);
}
