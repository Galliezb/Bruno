#pragma once
#include "ofMain.h"
#include "PopUp.h"
class Stats {

public:
	//initialisation des fichiers 
	void init();

	int tpsEntreDeuxHautFait = 0;

	void addZombieKilled();
	void addTreeCut();
	void addRockMined();
	void addHowManyStepsIDid(int i);
	void howLongTheGameLast(int i);
	void projectileLance();
	//Ce qu'on devra lancer quand le joueur sera mort
	void theGameIsOver();
	// La méthode que je lance quand on appelle une méthode addSomething();
	// Elle gère les haut-faits
	void achievement();
	string displayTitle();
	string displayDescription();
	//C'est pour ofApp, si le bool return est false, ça arrête de dessiner
	bool returnTest();
	void setBoolTest(bool vTest);
	//La c'est un timer pour empêcher qu'un haut fait ce dessine quand un autre est entrain d'être dessiné
	void setTimerStart();
	void setTimerEnd();
	void putStatInFile();
	int getDiffTime();
	int getTimerStart();
	int getTimerEnd();
	//Méthode à initialiser quand le jeu commence, elle gère la récupération des valeurs dans les fichiers
	void theGameHasStarted();
	//Est-ce que offApp dessine un haut-fait?
	void setCurrentlyDrawing(bool draw);
	bool getDrawStats();
	void drawStatistics();
private:
	int tpsStart, tpsStop;
	string titre;
	string description;
	bool test = false;
	int zombieKilled = 0;
	int treeCut = 0;
	int rocksMined = 0;
	int steps = 0;
	int timeTheGameLast = 0;
	int projectiles = 0;
	FILE * fichierZombie = NULL;
	FILE * fichierArbre = NULL;
	FILE * fichierRocks = NULL;
	FILE * fichierSteps = NULL;
	FILE * fichierTime = NULL;
	FILE * fichierTZombie = NULL;
	FILE * fichierTZombieTwo = NULL;
	FILE * fichierTZombieThree = NULL;
	FILE * fichierTTime = NULL;
	FILE * fichierTTimeTwo = NULL;
	FILE * fichierTTimeThree = NULL;
	FILE * fichierProjectiles = NULL;
	PopUp popup;
	bool bZombieKilled, bTreeCut, bRocksMined, bSteps, bGameLast, bProjectiles;
	int tZombieKilled, tTreeCut, tRocksMined, tSteps, tGameLast;
	int tZombieKilledTwo, tGameLastTwo;
	int tZombieKilledThree, tGameLastThree;
	//'c' pour "current"
	int cZombieKilled, cTreeCut, cRocksMined, cSteps, cGameLast, cProjectiles;
	bool currentlyDrawing = false;
	ofImage statistique;
	bool drawStats = false;
	int windowX, windowY;
	ofTrueTypeFont police;
	std::string tabZombieKilled;
	std::string tabAllZombieKilled;
	std::string tabTreeCut;
	std::string tabAllTreeCut;
	std::string tabRocksMined;
	std::string tabAllRocksMined;
	std::string tabSteps;
	std::string tabAllSteps;
	std::string tabGameLast;
	std::string tabAllGameLast;
	std::string tabProjectiles;
	std::string tabAllProjectiles;
};