#pragma once
#include "ofMain.h"
#include "classMap.h"
#include "classeMoving.h"
#include "classInventaire.h"
#include "classZombis.h"
#include "BarreDeVie.h"
#include "ClassProjectile.h"
#include "../Meteo.h"


class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	// Utilisation des classes
	classMap gestionMap;
	moving movePersonnage;
	classInventaire inventaire;
	ClassZombi zombis[10];
	BarreDeVie barreDeVie;
	Meteo lancementMeteo[50];
	Projectile projectile[5];
	Meteo lancementPluie;

		// variable
		// temps gérant les zombis
		int tpsSpawnZombi = ofGetElapsedTimeMillis();
		// nombre max de zombi
		int maxZombi = 1;
		// en milliseconde
		int timerSpawnZombi=2500;

		// inventaire actuellement affiché ?
		bool affInventaire = false;
		// taille ecran utilisateur
		int widthScreen,heightScreen;
		// position de la caméra
		int positionJoueurX, positionJoueurY;
		// action du joueur
		string playerCurrentAction = "repos";
		// le joueur a bouge ?
		bool playerHasMove = false;
		bool playerMoveTop = false;
		bool playerMoveRight = false;
		bool playerMoveDown = false;
		bool playerMoveLeft = false;
		/* tableau TERRAIN contenant le terrain
		0 => herbe ( marche ok )
		1 => eau ( pas de marche, ni arbre, ni roche )
		2 => boue ( marche ralentie )
		*/
		int tabContentTerrain[9600] = { 0 };
		/* tableau CASE contenant ce qui se trouve sur la case
		0 = > RIEN
		1 = > arbre
		2 = > rocher
		*/
		int tabContentCase[9600] = { 0 };
		/* Tableau contenant le stock du joueur
		0 => bois
		1 => roche
		2 => tête de zombie
		3 => pied de zombie
		4 => bras de zombie
		5 => pierre à lancer
		6 => lance
		*/
		int tabContentRessourcePlayer[7] = {10,10,10,10,10,10,10};
		ofPath pathLineHorizontal;

		// variable de récolte
		bool actionRecolteActive = false;

		ofTrueTypeFont font;
		string strSurvolInventaire = "";

		

};
