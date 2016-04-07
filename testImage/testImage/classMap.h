/*
Made by Galliez Bruno
Version : 3.0
But : Gérer la map
*/
#include "ofMain.h"

class classMap{
	private :
		ofImage arbre,boue,eau,herbe,rocher;
		ofFbo fbo;
		bool moveCameraLeft = false;
		bool moveCameraRight = false;
		bool moveCameraUp = false;
		bool moveCameraDown = false;
		int posXjoueur = 0, posYjoueur = 0;
		int widthImage = 7680;
		int heightImage = 5120;
		int speedScaleCamera = 1;

	public :

		ofImage affichage;
		int sizeScreenWidth, sizeScreenHeight;
		/*
		tabContentMap[X][Y][0] :
		tabContentMap[X][Y][0] = 0 => herbe ( marche ok )
		tabContentMap[X][Y][0] = 1 => boue ( marche ralentie )
		tabContentMap[X][Y][0] = 2 => eau ( pas de marche, ni arbre, ni roche )
		tabContentMap[X][Y][1] :
		tabContentMap[X][Y][1] = 0 => RIEN
		tabContentMap[X][Y][1] = 1 => arbre
		tabContentMap[X][Y][1] = 2 => rocher
		*/
		int tabContentMap[120][80][2] = { 0 };

		classMap();
		void init(int sizeScreenX, int sizeScreenY);
		void saveMap();
		void updateMapScreen();
		bool remplirHerbe();

		bool ajoutLac( unsigned int posX, unsigned int posY);
		bool addTree( unsigned int posX, unsigned int posY, bool arbre = true, bool rocher = false);
		bool addTreeRandom( bool arbre = true, bool rocher = false);
		bool addStone(unsigned int posX, unsigned int posY, bool arbre = true, bool rocher = false);
		bool addStoneRandom(bool arbre = true, bool rocher = false);

		bool removeTree(unsigned int posX, unsigned int posY, bool arbre = true, bool rocher = false);
		bool removeStone(unsigned int posX, unsigned int posY, bool arbre = true, bool rocher = false);

		void displayMap();

		void setBoolMoveCameraLeft();
		void setBoolMoveCameraRight();
		void setBoolMoveCameraUp();
		void setBoolMoveCameraDown();

		bool getBoolMoveCameraLeft();
		bool getBoolMoveCameraRight();
		bool getBoolMoveCameraUp();
		bool getBoolMoveCameraDown();
};