#include "ofMain.h"
#include "MenuMain.h"



MenuMain::MenuMain()
{
	fondEcran.loadImage("fondEcran.jpg");
	//buttonSonOn.loadImage("BoutonSon.png");
	//buttonSonOff.loadImage("BoutonSonOff.png");
	font.loadFont("CandyShop.ttf", 12, true);
	font2.loadFont("CandyShop.ttf", 20, true);
	button.loadImage("Boutton.png");
	buttonSur.loadImage("BouttonSur.png");
	clavier.loadImage("clavier2.png");
	credit.loadImage("credits.png");
}

MenuMain::~MenuMain()
{

}

void MenuMain::aJourMenu()
{
	if (lanceCredit == false) {
		buttonSur.clear();
		button.clear();
	}
}

void MenuMain::testAffichage()
{

	//ofColor col1(200, 150, 50);
	//ofColor col2(50, 200, 150);
	//ofBackgroundGradient(col1, col2, OF_GRADIENT_CIRCULAR);
	tailleFX = ofGetWindowWidth();//taille en X de la fenetre
	tailleFY = ofGetWindowHeight();//taille en y de la fenetre

	if (tailleFX < 1200 || tailleFY < 600)
	{
		ofSetWindowShape(1200, 600);//Taille minimun de la fenêtre de menu
	}
	

	fondEcran.draw(0, 0, tailleFX, tailleFY);
	if (menuPrincipal) {
		if (leJeuSeLance  && lanceOptionTouche && lanceCredit) {

			//buttonSonOn.draw(tailleFX - 64, tailleFY - 64);
			int xbutton = 100;
			do {//création graphique des boutons
				button.draw(tailleFX / 2 - 100, xbutton);
				xbutton += 100;
			} while (xbutton <= 400);

			if (ofGetMouseX() >= tailleFX / 2 - 100 && ofGetMouseX() <= tailleFX / 2 + 100) {
				if (ofGetMouseY() >= 100 && ofGetMouseY() <= 150) {
					buttonSur.draw(tailleFX / 2 - 105, 95);
				}
			}
			if (ofGetMouseX() >= tailleFX / 2 - 100 && ofGetMouseX() <= tailleFX / 2 + 100) {
				if (ofGetMouseY() >= 200 && ofGetMouseY() <= 250) {
					buttonSur.draw(tailleFX / 2 - 105, 195);
				}
			}
			if (ofGetMouseX() >= tailleFX / 2 - 100 && ofGetMouseX() <= tailleFX / 2 + 100) {
				if (ofGetMouseY() >= 300 && ofGetMouseY() <= 350) {
					buttonSur.draw(tailleFX / 2 - 105, 295);
				}
			}
			if (ofGetMouseX() >= tailleFX / 2 - 100 && ofGetMouseX() <= tailleFX / 2 + 100) {
				if (ofGetMouseY() >= 400 && ofGetMouseY() <= 450) {
					buttonSur.draw(tailleFX / 2 - 105, 395);
				}
			}
			/*if (ofGetMouseX() >= tailleFX - 64 && ofGetMouseX() <= tailleFX && ofGetMouseY() >= tailleFY - 64 && ofGetMouseY() <= tailleFY) {//SON
				if (ofGetMousePressed()) {
					//printf("CLICK\n");
					son = !son;
				}
			}*/
			/*if (son)
			{
				buttonSonOff.clear();
				buttonSonOn.draw(tailleFX - 64, tailleFY - 64);

			}
			else
			{

				buttonSonOn.clear();
				buttonSonOff.draw(tailleFX - 64, tailleFY - 64);
			}*/



			if (ofGetMouseX() >= tailleFX / 2 - 100 && ofGetMouseX() <= tailleFX / 2 + 100) {
				if (ofGetMouseY() >= 100 && ofGetMouseY() <= 150) {
					if (ofGetMousePressed()) {
						leJeuSeLance = false;

					}
				}
			}
			if (ofGetMouseX() >= tailleFX / 2 - 100 && ofGetMouseX() <= tailleFX / 2 + 100) {
				if (ofGetMouseY() >= 200 && ofGetMouseY() <= 250) {
					if (ofGetMousePressed()) {
						lanceOptionTouche = false;
						menuPrincipal = false;

					}
				}
			}
			if (ofGetMouseX() >= tailleFX / 2 - 100 && ofGetMouseX() <= tailleFX / 2 + 100) {
				if (ofGetMouseY() >= 300 && ofGetMouseY() <= 350) {
					if (ofGetMousePressed()) {
						//MessageBox(NULL, (LPCSTR)"Je mange des patates avec des carottes et des légumes bien frais, avant de manger un dessert chantilly et framboise\nBruno : Mac\nDamien : Pute\nAdrien : Pute\nHubert Pute secrétaire\nChristophe : Pute", (LPCSTR)"Crédit", MB_OK);
						//ofSystemTextBoxDialog("Comment vas-tu ?",texte);
						lanceCredit = false;
						menuPrincipal = false;
						//printf("%c", texte);
						//posez les questions sur le personnage
					}
				}
			}
			if (ofGetMouseX() >= tailleFX / 2 - 100 && ofGetMouseX() <= tailleFX / 2 + 100) {
				if (ofGetMouseY() >= 400 && ofGetMouseY() <= 450) {
					if (ofGetMousePressed()) {
						OF_EXIT_APP(0);
					}
				}
			}
			font.drawString("Jouer", tailleFX / 2 - 40, 130);
			font.drawString("Touches", tailleFX / 2 - 52, 230);
			font.drawString("Credits", tailleFX / 2 - 48, 330);
			font.drawString("Quitter", tailleFX / 2 - 48, 430);
		}
	}
	if (leJeuSeLance == false)
	{
		fondEcran.clear();
		/*BotMouvement();*/
	}

	if (lanceCredit == false)
	{
		credit.draw(ofGetWindowWidth() / 2 - 500, ofGetWindowHeight() / 2 - 325);
		//font2.drawString("OHM GAME\n\n", (tailleFX / 2) - 120, tailleFY / 5);
		font.drawString("Chef de projet --> Bruno Galliez\n\nOrganisateur du Travail --> Damien Goemaere\n\nPorte Parole -->Adrien Lechantre\n\nMascotte --> Hubert Leroy\n\nBeta-testeur --> Christophe Mauroo", tailleFX / 4 + 200, tailleFY / 5 + 150);
	}
	if (lanceOptionTouche == false) {
		clavier.draw(ofGetWindowWidth() / 2 - 640, ofGetWindowHeight() / 2 - 360);
	}
	if (lanceOptionTouche && lanceCredit && leJeuSeLance)
	{
		menuPrincipal = true;
	}
}






