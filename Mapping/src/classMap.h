/*
Script crée par Galliez Bruno
Création : 28/02/16
Dernière Update : 31/03/16

Objectif de la clase : Gérer la génération du terrain.
*/
#pragma once
#include "ofMain.h"

class classMap {

	// VARIABLES PRIVATES
	// taille de la carte EN NOMBRE DE CASES !
	int nbrCaseX=120, nbrCaseY=80;
	int widthScreenUser, heightScreenUser;
	unsigned char * pixels;
	/*
	tabMapContent[X][Y][0] :
		0 => herbe
		1 => boue
		2 => eau
	tabMapContent[X][Y][1] :
		0 => arbre
		1 => rocher
	*/
	short int tabMapContent[120][80][2]={0};
	string filename = "C:\\deadlu utility\\of_v0.9.3_vs_release\\apps\\Deadly-utility\\Mapping\\bin\\data\\saveMap.txt";
	bool didLoad = false;
	int cpt = 0;

	public :
		classMap::classMap();
		void classMap::genereMapLayer1();
		void classMap::genereMapLayerForet();
		void classMap::afficheCarte(int posX,int posY);
		

		ofImage arbre,boue,eau,herbe,rocher,lac, imgSaver;
		

		ofPath pathLineVertical;
		ofPath pathLineHorizontal;

		ofFbo fbo;
		ofPixels pix;

};