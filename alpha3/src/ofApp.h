#pragma once
#include "ofMain.h"
#include "classMap.h"
#include "classeMoving.h"
#include "classInventaire.h"
#include "classZombis.h"
#include "BarreDeVie.h"
#include "ClassProjectile.h"
#include "../Meteo.h"
#include "../ClassMusic.h"
#include "MeneInGame.h"
#include "../HautFait.h"
#include "../Popup.h"
#include "RejouerQuitter.h"
#include "ClasseLogo.h"
#include "MenuMain.h"

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
	void setTimerStart();
	// Utilisation des classes
	classMap gestionMap;
	moving movePersonnage;
	classInventaire inventaire;
	ClassZombi zombis[25];
	BarreDeVie barreDeVie;
	Meteo lancementMeteo[50];
	Projectile projectile[5];
	Meteo lancementPluie;
	MeneInGame LancementMenuInGame;
	RejouerQuitter lancementRejouerQuitter;
	//Gestion de la musique
	Music musique;
	Stats hautFait;
	PopUp popup;
	//classe logo
	ClasseLogo lancementChargement;
	//classe Menu
	MenuMain lancementMenu;
	//son du menu Principal
	ofSoundPlayer soundMenu;
	bool sonMenuPrincipallancer = true;
	ofTrueTypeFont font2;
	//string strSurvolTouche;
	


		// variable
		// temps gérant les zombis
		int tpsSpawnZombi = 0;
		// nombre max de zombi
		int maxZombi = 25;
		// en milliseconde
		int timerSpawnZombi=5000;

		// timer recharge sprint
		int tpsTimerRechargeSprint=0;

		// inventaire actuellement affiché ?
		bool affInventaire = false;
		// menu dans le jeu actuellement affiché? 
		bool affMenuInGame = false;
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
		int tabContentRessourcePlayer[7] = {0};
		//ofPath pathLineHorizontal;

		// variable de récolte
		bool actionRecolteActive = false;

		ofTrueTypeFont font;
		string strSurvolInventaire = "";
		string strSurvolTouche = "";
		int cptmusique = 0;

		int tpsStart;
		bool speedTest = false;
};
