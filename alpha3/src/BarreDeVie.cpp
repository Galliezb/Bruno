#include "BarreDeVie.h"
BarreDeVie::BarreDeVie()
{
	pointDeVie = 250;
	pointDeSprint = 250;
	pointDeVoltage = 0;
	maxPointDeVie = 250;
	maxPointDeSprint = 250;
	maxPointDeVoltage = 250;
	bdvie.loadImage("barredevie.png");
}
void BarreDeVie::init(int *ptrWidthScreen, int *ptrHeightScreen, string *ptrPlayerCurrentAction){
	this->ptrWidthScreen = ptrWidthScreen;
	this->ptrHeightScreen = ptrHeightScreen;
	this->ptrPlayerCurrentAction = ptrPlayerCurrentAction;
}
void BarreDeVie::displayBarreVie(){

	// 250 c'est la taille max de la barre
	int tailleVie = (pointDeVie / maxPointDeVie) * 250;
	int tailleSprint = (pointDeSprint / maxPointDeSprint) * 250;
	int tailleVoltage = (pointDeVoltage / maxPointDeVoltage) * 250;

	bdvie.draw(*ptrWidthScreen - 310, 10, 300, 95);
	ofSetColor(200, 0, 0);
	ofFill();
	ofDrawRectRounded(*ptrWidthScreen - 265, 15, tailleVie, 25, 100);
	ofSetColor(255);
	ofSetColor(255, 255, 0);
	ofDrawRectRounded(*ptrWidthScreen - 265, 45, tailleVoltage, 25, 100);
	ofSetColor(255);
	ofSetColor(0, 200, 0);
	ofDrawRectRounded(*ptrWidthScreen - 265, 75, tailleSprint, 25, 100);
	ofSetColor(255);
	ofNoFill();
}

void BarreDeVie::modifiePointDeVie(int quantite){
	pointDeVie += quantite;
	if (pointDeVie<1) {
		pointDeVie = 0;
		//printf("mort putain !\n");
		*ptrPlayerCurrentAction = "mort";
	} else if (pointDeVie>maxPointDeVie) {
		pointDeVie = maxPointDeVie;
	}
}
void BarreDeVie::modifiePointDeSprint(int quantite) {
	pointDeSprint += quantite;
	if (pointDeSprint<0) {
		pointDeSprint = 0;
	} else if (pointDeSprint > maxPointDeSprint){
		pointDeSprint = maxPointDeSprint;
	}
}
void BarreDeVie::modifiePointDeVoltage(int quantite) {
	pointDeVoltage += quantite;
	if (pointDeVoltage<0) {
		pointDeVoltage = 0;
	}
	else if (pointDeVoltage>maxPointDeVoltage) {
		pointDeVoltage = maxPointDeVoltage;
	}
}