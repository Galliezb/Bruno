#pragma once
#pragma once
#include "ofBaseApp.h"
#include "ofMain.h"
#include <windows.h>
#include <time.h>
#include <string.h>
class Music {
public:
	Music();
	void Music::nextMusic(string typeTheme);
	void setMusicOff();
	void changeVolume(float volume, string typeMusic);
	void setStoppedForRain(bool stop);
	bool getStoppedForRain();
	int tpsStart;
	string music[10][10];
	ofSoundPlayer musicAmbiance[3],musicHorror[5],musicAttack[3];
	ofSoundPlayer mainSound;
	bool onOff;
	string typeTheme;
	int yA = 0;
	int yH = 0;
	int yZA = 0;
	bool stoppedForRain=false;
};