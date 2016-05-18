#pragma once
#include "classInventaire.h"

classInventaire::classInventaire(){
	inventaire.load("inventaire.png");
	icon.load("iconInventaire.png");
	font.load("arialR.ttf", 15);
}
void classInventaire::init(int *ptrTabContentRessourcePlayer, int *ptrWidthScreen, int *ptrHeightScreen){

	// récupère le tableau des ressources
	this->ptrTabContentRessourcePlayer = ptrTabContentRessourcePlayer;

	// taille fenetre pour s'adapter au changement de tailles
	this->ptrWidthScreen = ptrWidthScreen;
	this->ptrHeightScreen = ptrHeightScreen;

}
void classInventaire::affichage(){

	inventaire.draw(returnPosXWindow(), returnPosYWindow(),1024,642);

	// premier affichage a 225 pixel x et 325 y
	// affichage des carré en 55*55
	// 18 pixel vers la droite
	// 19 pixel vers le bas

	int startX = 225 + returnPosXWindow();
	int startY = 325 + returnPosYWindow();

	int i=0;
	do{
		// affiche les icons
		int hauteur = 0;
		if ( i > 8 ){ hauteur = i % 8; }
		icon.drawSubsection(startX+i*18+i*55,startY+hauteur*19,55,55,i*55,0,55,55);
		font.drawString(ofToString(*(ptrTabContentRessourcePlayer + i)), startX + i * 18 + i * 55 + 5, startY + hauteur * 19 + 52);
		i++;
	} while( i < 7 );

}
int classInventaire::returnPosXWindow(){
	return (*ptrWidthScreen - 1024) / 2;
}
int classInventaire::returnPosYWindow(){
	return (*ptrHeightScreen - 642) / 2;
}
void classInventaire::fabriqueRoche(){
	
	if (*(ptrTabContentRessourcePlayer+1) > 0 ){
		*(ptrTabContentRessourcePlayer + 1) -= 1;
		*(ptrTabContentRessourcePlayer + 5) += 5;
	}

}
void classInventaire::fabriqueLance() {

	if (*(ptrTabContentRessourcePlayer) > 0) {
		*(ptrTabContentRessourcePlayer) -= 1;
		*(ptrTabContentRessourcePlayer + 6) += 5;
	}

}
