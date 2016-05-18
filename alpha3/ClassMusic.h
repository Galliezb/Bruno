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
	void nextSound();
	void setTheme(char theme[]);
	void setMusicOnOrOff(bool musicOnOrOff, char theme[]);
	void setSound(bool soundOnOrOff, char theme[]);
	void setSound(char theme[]);
	void setMusic(string musicTheme);
	void setSound(string soundTheme);
	void changeTheme(string newTheme);
	void changeVolume(float volume);
	int getDiffTime();
	void setTimerStart();
	int tpsStart;
	string music[10][10];
	ofSoundPlayer mainMusic;
	ofSoundPlayer mainSound;
	bool onOff;
	string typeTheme;
	int yA = 0;
	int yH = 0;
	int yZA = 0;
};