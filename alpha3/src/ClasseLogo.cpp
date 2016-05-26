#include "ClasseLogo.h"



ClasseLogo::ClasseLogo()
{

}


ClasseLogo::~ClasseLogo()
{
}
void ClasseLogo::initiation()
{
	sonOhm.loadSound("ohmSon.wav");
	logo1.loadImage("Logo1.jpg");
	logo2.loadImage("Logo2.jpg");
	logo3.loadImage("Logo3.jpg");
	logo4.loadImage("Logo4.jpg");
	logoP.loadImage("Logo.jpg");
	fontBlanc = false;
	dessin = true;
	ofSetFrameRate(60);
	//ofSetFullscreen;
	tailleFX = ofGetScreenWidth();//taille en X de la fenetre
	tailleFY = ofGetScreenHeight();//taille en y de la fenetre
	tmp3 = tailleFX;
	velocity = -tailleFX;
	gravity = 15;
	goMenu = 1;
}

void ClasseLogo::maj() {
	if (velocity < 0)
	{
		velocity += gravity;
		//printf("%d\n", velocity);
	}
	if (tmp3 > 0) {
		tmp3 -= 15;
		//printf("%d\n", tmp3);
	}
	if (tailleFX < 1920 || tailleFY < 1080)
	{
		ofSetWindowShape(1920, 1080);//Taille minimun de la fenêtre de menu
	}
	if (tmp2 == 10)
	{
		fontBlanc = true;
	}
	if (goMenu < 2) {
		if (fontBlanc)
		{
			sonOhm.play();
			Sleep(4000);
			logo1.clear();
			logo2.clear();
			logo3.clear();
			logo4.clear();
			logoP.clear();
			fontBlanc = false;
			goMenu = 2;
		}
	}
}

void ClasseLogo::chargement()
{
	if (goMenu < 2) {
		if (dessin) {
			//col++;
			ofSetBackgroundColor(0);
			ofTranslate(0, 0);
			//ofSetColor(col);
			logo1.draw(velocity, 0, tailleFX, tailleFY / 4);
			logo2.draw(tmp3, tailleFY / 4, tailleFX, tailleFY / 4);
			logo3.draw(velocity, tailleFY / 4 * 2, tailleFX, tailleFY / 4);
			logo4.draw(tmp3, tailleFY / 4 * 3, tailleFX, tailleFY / 4);
		}
		ofSetColor(255);
		if (tmp3 == 0)
		{
			tmp2 = 10;
		}
	}
}