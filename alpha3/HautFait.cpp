#pragma once
#include "HautFait.h"
void Stats::init() {
	fichierZombie = fopen("fichierZombie.txt", "a");
	fclose(fichierZombie);
	fichierArbre = fopen("fichierArbre.txt", "a");
	fclose(fichierArbre);
	fichierRocks = fopen("fichierRocks.txt", "a");
	fclose(fichierRocks);
	fichierSteps = fopen("fichierSteps.txt", "a");
	fclose(fichierSteps);
	fichierTime = fopen("fichierTime.txt", "a");
	fclose(fichierTime);
	//
	fichierTZombie = fopen("fichierTZombie.txt", "a");
	fclose(fichierTZombie);
	//
	fichierTZombieTwo = fopen("fichierTZombieTwo.txt", "a");
	fclose(fichierTZombieTwo);
	//
	fichierTZombieThree = fopen("fichierTZombieThree.txt", "a");
	fclose(fichierTZombieThree);
	//
	fichierTTime = fopen("fichierTTime.txt", "a");
	fclose(fichierTTime);
	//
	fichierTTimeTwo = fopen("fichierTTimeTwo.txt", "a");
	fclose(fichierTTimeTwo);
	//
	fichierTTimeThree = fopen("fichierTTimeThree.txt", "a");
	fclose(fichierTTimeThree);
	//Moi péter un caaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaable !
	//La vérité tu la sais, c'est qu'ce code me rend to-to-total-lement pété,  gros pédé.
	fichierProjectiles = fopen("fichierProjectiles.txt", "a");
	fclose(fichierProjectiles);

}
void Stats::theGameHasStarted() {
	fichierZombie = fopen("fichierZombie.txt", "r");
	fscanf(fichierZombie, "%d", &zombieKilled);
	//cout << zombieKilled;
	fclose(fichierZombie);
	fichierArbre = fopen("fichierArbre.txt", "r");
	fscanf(fichierArbre, "%d", &treeCut);
	fclose(fichierArbre);
	fichierRocks = fopen("fichierRocks.txt", "r");
	fscanf(fichierRocks, "%d", &rocksMined);
	fclose(fichierRocks);
	fichierSteps = fopen("fichierSteps.txt", "r");
	fscanf(fichierSteps, "%d", &steps);
	fclose(fichierSteps);
	fichierTime = fopen("fichierTime.txt", "r");
	fscanf(fichierTime, "%d", &timeTheGameLast);
	fclose(fichierTime);
	fichierTZombie = fopen("fichierTZombie.txt", "r");
	fscanf(fichierTZombie, "%d", &tZombieKilled);
	fclose(fichierTZombie);
	fichierTZombieTwo = fopen("fichierTZombieTwo.txt", "r");
	fscanf(fichierTZombieTwo, "%d", &tZombieKilledTwo);
	fclose(fichierTZombieTwo);
	fichierTZombieThree = fopen("fichierTZombieThree.txt", "r");
	fscanf(fichierTZombieThree, "%d", &tZombieKilledThree);
	fclose(fichierTZombieThree);
	//
	fichierTTime = fopen("fichierTTime.txt", "r");
	fscanf(fichierTTime, "%d", &tGameLast);
	fclose(fichierTTime);
	//
	fichierTTimeTwo = fopen("fichierTTimeTwo.txt", "r");
	fscanf(fichierTTimeTwo, "%d", &tGameLastTwo);
	fclose(fichierTTimeTwo);
	//
	fichierTTimeThree = fopen("fichierTTimeThree.txt", "r");
	fscanf(fichierTTimeThree, "%d", &tGameLastThree);
	fclose(fichierTTimeThree);
	//
	fichierProjectiles = fopen("fichierProjectiles.txt", "r");
	fscanf(fichierProjectiles, "%d", &projectiles);
	fclose(fichierProjectiles);
}
void Stats::addZombieKilled() {
	zombieKilled++;
	cZombieKilled++;
	achievement();
	//cout << zombieKilled;
	bZombieKilled = true;
	putStatInFile();
}
void Stats::addTreeCut() {
	treeCut++;
	cTreeCut++;
	achievement();
	bTreeCut = true;
	putStatInFile();
}
void Stats::addRockMined() {
	rocksMined++;
	cRocksMined++;
	achievement();
	bRocksMined = true;
	putStatInFile();
}
void Stats::addHowManyStepsIDid(int i) {
	steps = steps + i;
	cSteps = steps + i;
	achievement();
	bSteps = true;
	putStatInFile();
}
void Stats::howLongTheGameLast(int i) {
	timeTheGameLast = timeTheGameLast + i;
	cGameLast = i;
	achievement();
	bGameLast = true;
	putStatInFile();
}

void Stats::projectileLance() {
	projectiles++;
	cProjectiles++;
	bProjectiles = true;
	putStatInFile();
}

void Stats::achievement()
{
	if (currentlyDrawing == true) {
		setTimerStart();
		if (getDiffTime() < 3000) {
			currentlyDrawing = false;
		}
	}
	else {
		if (zombieKilled == 1) {
			test = true;
			titre = "First Blood!";
			description = "Il le meritait quand meme!";
			currentlyDrawing = true;
		}
		else if ((zombieKilled >= 10 && currentlyDrawing == false && tZombieKilled == 0)) {
			test = true;
			titre = "Apprenti meurtrier";
			description = "Tiendras-tu longtemps?";
			tZombieKilled = 1;
			putStatInFile();
			currentlyDrawing = true;
		}
		else if (zombieKilled >= 50 && currentlyDrawing == false && tZombieKilledTwo == 0) {
			test = true;
			titre = "Zombie Killer";
			description = "Ca commence à en faire..";
			tZombieKilledTwo = 1;
			putStatInFile();
			currentlyDrawing = true;
		}
		else if (zombieKilled >= 100 && currentlyDrawing == false && tZombieKilledThree == 0) {
			test = true;
			titre = "Boucherie";
			description = "Tu veux pas mourir?!";
			tZombieKilledThree = 1;
			putStatInFile();
			currentlyDrawing = true;
		}
		else if (treeCut == 1) {
			test = true;
			titre = "Corvee de bois";
			description = "Etait-ce vraiment utile?";
			currentlyDrawing = true;
		}
		else if (treeCut == 10) {
			test = true;
			titre = "Bucheron";
			description = "Quels muscles!";
			currentlyDrawing = true;
		}
		else if (treeCut == 20) {
			test = true;
			titre = "Vingt arbres";
			description = "Et tu replantes au moins?";
			currentlyDrawing = true;
		}
		else if (treeCut == 50) {
			test = true;
			titre = "Deforestation";
			description = "Mere nature ne sera pas contente";
		}
		else if (rocksMined == 1) {
			test = true;
			titre = "Apprenti mineur";
			description = "Premier coup de pioche!";
		}
		else if (rocksMined == 10) {
			test = true;
			titre = "Mineur confirmé";
			description = "Tu peux faire une petanque";
		}
		else if (rocksMined == 20) {
			test = true;
			titre = "Mineur agueri";
			description = "J'espere que tu t'en sers!";
		}
		else if (steps == 1) {
			test = true;
			titre = "Premier pas";
			description = "Le titre suffit a comprendre non?";
		}
		else if (steps == 100) {
			test = true;
			titre = "Les cents pas";
			description = "Et alors, on court? Ya rien à craindre pourtant!";
		}
		else if (steps == 1000) {
			test = true;
			titre = "Les milles pas";
			description = "Regardez ces mollets!";
		}
		else if (timeTheGameLast >= 60000 && currentlyDrawing == false && tGameLast == 0) {
			test = true;
			titre = "La minute";
			description = "Elle est passee vite hein?";

		}
		else if (timeTheGameLast == 600000 && currentlyDrawing == false && tGameLastTwo == 0) {
			test = true;
			titre = "Dix minutes";
			description = "Amusement intense";
		}
		else if (timeTheGameLast == 1200000 && currentlyDrawing == false && tGameLastThree == 0) {
			test = true;
			titre = "La demi-heure";
			description = "Sors au lieu de jouer, glandeur!";
		}
	}
}

void Stats::putStatInFile() {
	if (bZombieKilled) {
		fichierZombie = fopen("fichierZombie.txt", "w");
		fprintf(fichierZombie, "%d", zombieKilled);
		fclose(fichierZombie);
		bZombieKilled = false;
	}
	else if (bTreeCut) {
		fichierArbre = fopen("fichierArbre.txt", "w");
		fprintf(fichierArbre, "%d", treeCut);
		fclose(fichierArbre);
		bTreeCut = false;
	}
	else if (bRocksMined) {
		fichierRocks = fopen("fichierRocks.txt", "w");
		fprintf(fichierRocks, "%d", rocksMined);
		fclose(fichierRocks);
		bRocksMined = false;
	}
	else if (bSteps) {
		fichierSteps = fopen("fichierSteps.txt", "w");
		fprintf(fichierSteps, "%d", steps);
		fclose(fichierSteps);
		bSteps = false;
	}
	else if (bGameLast) {
		fichierTime = fopen("fichierTime.txt", "w");
		fprintf(fichierTime, "%d", timeTheGameLast);
		fclose(fichierTime);
		bGameLast = false;
	}
	else if (bProjectiles) {
		fichierProjectiles = fopen("fichierProjectiles.txt", "w");
		fprintf(fichierProjectiles, "%d", projectiles);
		fclose(fichierProjectiles);
		bProjectiles = false;
	}
	if (tZombieKilled == 1) {
		fichierTZombie = fopen("fichierTZombie.txt", "w");
		fprintf(fichierTZombie, "%d", tZombieKilled);
		fclose(fichierTZombie);
	}
	else if (tZombieKilledTwo == 1) {
		fichierTZombieTwo = fopen("fichierTZombieTwo.txt", "w");
		fprintf(fichierTZombieTwo, "%d", tZombieKilledTwo);
		fclose(fichierTZombieTwo);
	}
	else if (tZombieKilledThree == 1) {
		fichierTZombieThree = fopen("fichierTZombieThree.txt", "w");
		fprintf(fichierTZombieThree, "%d", tZombieKilledThree);
		fclose(fichierTZombieThree);
	}
}

string Stats::displayTitle() {
	return titre;
}

string Stats::displayDescription() {
	return description;
}

bool Stats::returnTest() {
	return test;
}

void Stats::setBoolTest(bool vTest) {
	test = vTest;
}

void Stats::setCurrentlyDrawing(bool draw) {
	currentlyDrawing = draw;
}

void Stats::setTimerStart() {
	tpsStart = ofGetElapsedTimeMillis();
}
void Stats::setTimerEnd() {
	tpsStop = ofGetElapsedTimeMillis();
}
int Stats::getDiffTime() {
	return ofGetElapsedTimeMillis() - tpsStart;
}
int Stats::getTimerStart() {
	return tpsStart;
}
int Stats::getTimerEnd() {
	return tpsStop;
}
void Stats::theGameIsOver() {
	statistique.loadImage("statistiques.png");
	police.loadFont("arial.ttf", 15, true);
	drawStats = true;
	tabZombieKilled = std::to_string(cZombieKilled);
	tabAllZombieKilled = std::to_string(zombieKilled);
	tabTreeCut = std::to_string(cTreeCut);
	tabAllTreeCut = std::to_string(treeCut);
	tabRocksMined = std::to_string(cRocksMined);
	tabAllRocksMined = std::to_string(rocksMined);
	tabSteps = std::to_string(cSteps);
	tabAllSteps = std::to_string(steps);
	tabGameLast = std::to_string(cGameLast);
	tabAllGameLast = std::to_string(timeTheGameLast);
	tabProjectiles = std::to_string(cProjectiles);
	tabAllProjectiles = std::to_string(projectiles);
}

bool Stats::getDrawStats() {
	return drawStats;
}

void Stats::drawStatistics() {
	windowX = ofGetWindowWidth();
	windowY = ofGetWindowHeight();
	statistique.draw(0, 0, windowX, windowY);
	police.drawString("Pendant la partie:", windowX / 5 + 60, windowY / 5 + 50);
	police.drawString("Au total:", windowX / 5 + 560, windowY / 5 + 50);
	police.drawString("Zombies morts:", windowX / 5 - 120, windowY / 5 + 100);
	police.drawString(tabZombieKilled, windowX / 5 + 120, windowY / 5 + 100);
	police.drawString(tabAllZombieKilled, windowX / 5 + 590, windowY / 5 + 100);
	police.drawString("Bois loot:", windowX / 5 - 120, windowY / 5 + 150);
	police.drawString(tabTreeCut, windowX / 5 + 120, windowY / 5 + 150);
	police.drawString(tabAllTreeCut, windowX / 5 + 590, windowY / 5 + 150);
	police.drawString("Pierres loot:", windowX / 5 - 120, windowY / 5 + 200);
	police.drawString(tabRocksMined, windowX / 5 + 120, windowY / 5 + 200);
	police.drawString(tabAllRocksMined, windowX / 5 + 590, windowY / 5 + 200);
	police.drawString("Metres parcouru:", windowX / 5 - 120, windowY / 5 + 250);
	police.drawString(tabSteps, windowX / 5 + 120, windowY / 5 + 250);
	police.drawString(tabAllSteps, windowX / 5 + 590, windowY / 5 + 250);
	police.drawString("Temps de jeu:", windowX / 5 - 120, windowY / 5 + 300);
	police.drawString(tabGameLast, windowX / 5 + 120, windowY / 5 + 300);
	police.drawString(tabAllGameLast, windowX / 5 + 590, windowY / 5 + 300);
	police.drawString("Projectiles:", windowX / 5 - 120, windowY / 5 + 350);
	police.drawString(tabProjectiles, windowX / 5 + 120, windowY / 5 + 350);
	police.drawString(tabAllProjectiles, windowX / 5 + 590, windowY / 5 + 350);
}