#include "MeneInGame.h"



MeneInGame::MeneInGame()
{
}


MeneInGame::~MeneInGame()
{
}


void MeneInGame::InitInGameMenu()
{

	ecrit.loadFont("CandyShop.ttf", 10, true);
	button.loadImage("Boutton.png");
	buttonSur.loadImage("BouttonSur.png");
	clavier.loadImage("clavier.png");

}

void MeneInGame::MenuMajInGame()
{
	tailleX = ofGetWindowWidth();
	tailleY = ofGetWindowHeight();
}


void MeneInGame::inGame()
{
	logoFont.load("menuingame.png");
	ecrit.loadFont("CandyShop.ttf", 10, true);
	button.loadImage("Boutton.png");
	buttonSur.loadImage("BouttonSur.png");

	if (retourJeu) {
		if (goMenuJeu)
		{
			logoFont.draw(tailleX / 2 - 500, tailleY / 2 - 350, 1000, 700);
			//dessin bouton statistique
			button.draw(tailleX / 2 - 100, tailleY / 5 * 2);

			if (ofGetMouseX() >= tailleX / 2 - 100 && ofGetMouseX() <= tailleX / 2 + 100) {
				if (ofGetMouseY() >= tailleY / 5 * 2 && ofGetMouseY() <= tailleY / 5 * 2 + 50) {
					buttonSur.draw(tailleX / 2 - 100, tailleY / 5 * 2);
				}
			}
			//dessin bouton touches
			button.draw(tailleX / 2 - 100, tailleY / 5 * 2 + 175);

			if (ofGetMouseX() >= tailleX / 2 - 100 && ofGetMouseX() <= tailleX / 2 + 100) {
				if (ofGetMouseY() >= tailleY / 5 * 2 + 175 && ofGetMouseY() <= tailleY / 5 * 2 + 225) {
					buttonSur.draw(tailleX / 2 - 100, tailleY / 5 * 2 + 175);
				}
			}
			//dessin bouton retour au jeu
			button.draw(tailleX / 2 - 100, tailleY / 5 * 2 - 75);

			if (ofGetMouseX() >= tailleX / 5 * 2 - 50 && ofGetMouseX() <= tailleX / 2 + 150) {
				if (ofGetMouseY() >= tailleY / 5 * 2 - 75 && ofGetMouseY() <= tailleY / 5 * 2 - 25) {
					buttonSur.draw(tailleX / 2 - 100, tailleY / 5 * 2 - 75);
				}
			}

			//bouton touche
			if (ofGetMouseX() >= tailleX / 2 - 100 && ofGetMouseX() <= tailleX / 2 + 100 && ofGetMouseY() >= tailleY / 5 * 2 && ofGetMouseY() <= tailleY / 5 * 2 + 50) {
				if (ofGetMousePressed()) {
					//printf("CLICK\n");
					clavierlancer = true;
				}
			}

			//bouton retour au jeu
			if (ofGetMouseX() >= tailleX / 2 - 100 && ofGetMouseX() <= tailleX / 2 + 100 && ofGetMouseY() >= tailleY / 5 * 2 + 175 && ofGetMouseY() <= tailleY / 5 * 2 + 225) {
				if (ofGetMousePressed()) {
					//printf("CLICK3\n");
					retourJeu = false;
				}
			}

			//bouton statistique
			if (ofGetMouseX() >= tailleY / 5 * 2 - 50 && ofGetMouseX() <= tailleX / 2 + 150 && ofGetMouseY() >= tailleY / 5 * 2 - 75 && ofGetMouseY() <= tailleY / 5 * 2 - 25) {
				if (ofGetMousePressed()) {
					statMenuLancer = true;
				}
			}
			ecrit.drawString("Statistique", tailleX / 2 - 60, tailleY / 5 * 2 - 40);
			ecrit.drawString("Touches ", tailleX / 2 - 52, tailleY / 5 * 2 + 32);
			ecrit.drawString("Retour au jeu", tailleX / 2 - 70, tailleY / 5 * 2 + 210);
		}
	}
	if (clavierlancer)
	{

		goMenuJeu = false;
		//retourJeu = false;
		clavier.draw(ofGetWindowWidth() / 2 - 640, ofGetWindowHeight() / 2 - 360);
	}
	if (statMenuLancer)
	{
		goMenuJeu = false;
		//retourJeu = false;
		//il faut un boolean pour lancer la classe stat
	}

}
void MeneInGame::initBarreMusique()
{
	//Sauvegarde du son et position des barres de sons
	sauvMusique = fopen("sauvMusique.txt", "r");
	if (sauvMusique != NULL)
	{
		fscanf(sauvMusique, "%f ", &volA);
		fclose(sauvMusique);
	}
	//sons musique déclaration 

	gui2.setup("Musique");
	gui2.add(volumeA.setup("Volume", volA, 0, 1));
}

void MeneInGame::majBarreMusique()
{
	//sauvegarde sons
	//fscanf(sauvMusique, "%f %f", &volM, &volA);
	sauvMusique = fopen("sauvMusique.txt", "w");
	fprintf(sauvMusique, "%f", volA);
	fclose(sauvMusique);
	volA = volumeA;
}

void MeneInGame::dessineBarreMusique()
{
	if (retourJeu && goMenuJeu) {

		//position des barres de sons
		
		gui2.draw();
		sample2.setVolume(volA);
		gui2.setPosition(ofGetWindowWidth() / 2 - 100, ofGetWindowHeight() / 2 + 25);
	}

}

bool MeneInGame::setRetourJeu()
{
	return retourJeu;
}

bool MeneInGame::getRetourJeu()
{
	return retourJeu;
}


float MeneInGame::getSonAmbiance()
{
	return volA;
}




