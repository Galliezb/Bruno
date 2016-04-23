#pragma once

#include "ofMain.h"
#include "classMap.h"
#include "classeMoving.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
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

		// variable
		// taille ecran utilisateur
		int widthScreen,heightScreen;
		// position de la caméra
		int originX, originY;
		// action du joueur
		string playerCurrentAction = "repos";
		// le joueur a bouge ?
		bool playerHasMove = false;
		bool playerMoveTop = false;
		bool playerMoveRight = false;
		bool playerMoveDown = false;
		bool playerMoveLeft = false;
		// vitesse de défilement
		int scrollingSpeed = 10;

};
