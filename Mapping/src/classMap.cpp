/*
Script crée par Galliez Bruno
Création : 28/02/16
Dernière Update : 31/03/16

Objectif de la clase : Gérer la génération du terrain.
*/
#include "classMap.h"
#include <fstream>
#include <stdlib.h>

// constructeur par défaut, il rale pour ca je sais pas pourquoi
classMap::classMap() {

	// taille de l'ecran utilisateur ( utile a l'affichage de du morceau de map )
	//widthScreenUser = ofGetScreenWidth();
	//heightScreenUser = ofGetScreenHeight();
	widthScreenUser = 1000;
	heightScreenUser = 1000;


	printf("****************\n");
	printf("screen user => %d / %d\n", widthScreenUser, heightScreenUser);
	printf("****************\n");


	// Permet de voir les chemins d'accès ( utilie pour débugger quand on a des soucis d'accès a des fichiers )
	printf("****************\n");
	ofFile file(ofToDataPath("sprite.jpg"));
	ofLogVerbose() << "Path access : " << file.getEnclosingDirectory();
	printf("****************\n");

	// tableau contenant les pixels de l'image généré
	pixels = new unsigned char[nbrCaseX * 32 * nbrCaseY * 32 * 3];
	
}

void classMap::genereMapLayer1() {

	/*------------------------------------------ CHARGEMENT DES IMAGES -------------------------------------------*/
	/*
	didLoad = arbre.load("arbre.png");
	// on envoi dans les logs, Opérateur UNITAIRE pour faire du CHAINAGE
	ofLogVerbose() << "Ouvture arbre : " << didLoad;

	didLoad = boue.load("boue.jpg");
	ofLogVerbose() << "Ouvture boue : " << didLoad;

	didLoad = eau.load("eau.jpg");
	ofLogVerbose() << "Ouvture eau : " << didLoad;

	didLoad = herbe.load("herbe.jpg");
	ofLogVerbose() << "Ouvture herbe : " << didLoad;

	didLoad = rocher.load("rocher.png");
	ofLogVerbose() << "Ouvture rocher : " << didLoad;
*/
	didLoad = lac.load("lac.jpg");
	ofLogVerbose() << "Ouvture lac : " << didLoad;
	/*---------------------------------- ALLOCATION MEMOIRE EN CARTE GRAPHIQUE ------------------------------------*/
	// Préparation du tableau qui contiendra les pixel
	fbo.allocate(nbrCaseX * 32, nbrCaseY * 32);
	fbo.setUseTexture(true);
	imgSaver.allocate(nbrCaseX * 32, nbrCaseY * 32,OF_IMAGE_COLOR);


	/*---------------------------------------------- DEBUT GENERATION MAP -----------------------------------------*/
	// ouverture du fichier pour sauvegarder la map
	ofstream fichierTxtSaveMap;
	// ios::trunc => ouverture et vide le fichier s'il existe déjà
	fichierTxtSaveMap.open(filename,ios::trunc);
	
	// commence l'enregistrement de la carte
	fbo.begin();
	// vide la mémoire ( efface le contenu pour éviter les soucis avec des trucs en mémoire louches )
	fbo.clear();



	/*-------------------------------------------------- GENERATION HERBE ------------------------------------------*/
	for (int x = 0; x < nbrCaseX; x++) {
		for (int y = 0; y < nbrCaseY; y++) {
			cpt++;
			//herbe.drawSubsection(32*x,32*y,32,32);
			lac.drawSubsection(32*x,32*y,32,32,384,0,32,32);
		}
	}
	ofLogVerbose() << "Génération de l'herbe sur : " << cpt << " case(s)";

	/*-------------------------------------------------- GENERATION BOUE --------------------------------------------*/
	srand(time(NULL));
	cpt = 0;
	for (int x = 0; x < 50; x++) {

		short int randX = rand()%nbrCaseX + 1;
		short int randY = rand()%nbrCaseY + 1;
		// on ajoute la boue sur la carte
		//boue.draw(randX*32,randY*32,32,32);
		lac.drawSubsection(32*randX,32*randY,32,32,64,0,32,32);
		// et on stock l'info dans le tableau
		tabMapContent[randX][randY][0] = 1;
		cpt++;

		// cree une zone plus large et aleatoire autour de cette case
		short int tailleZoneBoue = rand()%8;
		if (tailleZoneBoue < 2 ){ tailleZoneBoue = 2; }
		// la case au dessus
		for (int x = floor(-tailleZoneBoue/2); x < ceil(tailleZoneBoue/2); x++) {
			for (int y = floor(-tailleZoneBoue/2); y < ceil(tailleZoneBoue/2); y++) {

				ofLogVerbose() << "rand()%101 < 35 : " << rand()%101;
				// 35 % de chance
				if ( rand()%101 < 35 ){

					// verifie qu'on sort pas de la map
					if ( randX+x > 1 && randX+x < nbrCaseX && randY+y > 0 && randY+y < nbrCaseY){
						//boue.draw((randX+x)*32,(randY+y)*32,32,32);
						lac.drawSubsection(32*(randX+x),32*(randY+y),32,32,0,0,32,32);
						tabMapContent[randX+x][randY+y][0] = 1;
						cpt++;
					}
				}

			}
		}

	}
	ofLogVerbose() << "Génération de boue sur : " << cpt << " case(s)";

	/*-------------------------------------------------- GENERATION EAU --------------------------------------------*/
	/*-------------------------------- REDONDANCE !!! UNE FONCTION SERAIT PLUS UTILE -------------------------------*/
	srand(NULL);
	cpt = 0;
	for (int x = 0; x < 20; x++) {

		// ajout de la toute première ligne ( idée du bateau et d'une zone plus grande si on développe plus le jeu par la suite )
		// faudra penser a mettre une montagne pour créer une cuvette accessible seulement depuis la rivière
		// qui malheureusement n'empêchera pas les monstres de passer
		for (int x = 0; x < nbrCaseX; x++) {
			cpt++;
			//eau.draw(32*x,0,32,32);
			lac.drawSubsection(32*x,0,32,32,128,128,32,32);
		}


		short int randX = rand()%nbrCaseX + 1;
		short int randY = rand()%nbrCaseY + 1;
		// on ajoute la boue sur la carte
		//eau.draw(randX*32,randY*32,32,32);
		lac.drawSubsection(32*(randX),32*(randY),32,32,128,128,32,32);
		// et on stock l'info dans le tableau
		tabMapContent[randX][randY][0] = 1;
		cpt++;

		// cree une zone plus large et aleatoire autour de cette case
		short int tailleZoneEau = rand()%8;
		if (tailleZoneEau < 2 ){ tailleZoneEau = 2; }
		// la case au dessus
		for (int x = floor(-tailleZoneEau/2); x < ceil(tailleZoneEau/2); x++) {
			for (int y = floor(-tailleZoneEau/2); y < ceil(tailleZoneEau/2); y++) {
				// 35 % de chance
				if ( rand()%101 < 35 ){

					// verifie qu'on sort pas de la map
					if ( randX+x > 1 && randX+x < nbrCaseX && randY+y > 0 && randY+y < nbrCaseY){
						//eau.draw((randX+x)*32,(randY+y)*32,32,32);
						lac.drawSubsection(32*(randX),32*(randY),32,32,128,128,32,32);
						tabMapContent[randX+x][randY+y][0] = 1;
						cpt++;
					}
				}

			}
		}

	}
	ofLogVerbose() << "Génération de l'eau sur : " << cpt << " case(s)";


	// On va tout transformer pour le récupérer en tableau de pixel
	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glReadPixels(0, 0, nbrCaseX*32, nbrCaseY*32, GL_RGB, GL_UNSIGNED_BYTE, pixels);
	imgSaver.setFromPixels(pixels, nbrCaseX*32, nbrCaseY*32, OF_IMAGE_COLOR);
	// On enregistre le fichier ( bin/data comme rep par défaut )
	imgSaver.saveImage("output_test.jpg", OF_IMAGE_QUALITY_MEDIUM);
	//On ferme l'enregistrement en cours
	fbo.end();
	fichierTxtSaveMap.close();

	
	pix.allocate(nbrCaseX*32,nbrCaseY*32,OF_IMAGE_COLOR);
	fbo.readToPixels(pix);
	ofSaveImage(pix,"C:\\deadlu utility\\of_v0.9.3_vs_release\\apps\\Deadly-utility\\Mapping\\bin\\data\\output_test2.jpg",OF_IMAGE_QUALITY_BEST);
	
	// on indique dans les logs que c'est fait.
	ofLog(OF_LOG_VERBOSE, "Saved frame");

}

void classMap::genereMapLayerForet() {


	genereMapLayer1();

}

void classMap::afficheCarte(int posX,int posY){
	//imgSaver.drawSubsection(0,0,widthScreenUser,heightScreenUser,posX,posY,widthScreenUser,heightScreenUser);
}
