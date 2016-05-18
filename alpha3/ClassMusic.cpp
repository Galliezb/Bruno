#include "ClassMusic.h"
//music[0][x] = Ambient Music
//music[1][x] = Horror Music
//music[2][x] = Zombies Attack Music
Music::Music() {
	//Ambient
	music[0][0] = "(A)Daybreak.mp3";
	music[0][1] = "(A)End_Of_Days.mp3";
	music[0][2] = "(A)Far_And_Wide.mp3";
	//Horror
	music[1][0] = "(H)Blood_Pressure.mp3";
	music[1][1] = "(H)Haunted.mp3";
	music[1][2] = "(H)Intimidation.mp3";
	music[1][3] = "(H)On_The_Prowl.mp3";
	music[1][4] = "(H)Trick_Or_Treat.mp3";
	//Zombies Attack
	music[2][0] = "(ZA)Electro_Zombies.mp3";
	music[2][1] = "(ZA)Last_Stand.mp3";
	music[2][2] = "(ZA)Upstep.mp3";
}

void Music::nextMusic(string typeTheme) {
	if (typeTheme == "Ambient") {
		mainMusic.load(music[0][yA]);
		mainMusic.play();
		ofLogVerbose() << music[0][yA] << " est en cours";
		if (yA == 2) {
			yA = 0;
		}
		ofLogVerbose() << music[0][yA + 1] << " est la prochaine musique en cours";
		yA++;
	}
	else if (typeTheme == "Horror") {
		mainMusic.load(music[1][yH]);
		mainMusic.play();
		ofLogVerbose() << music[1][yH] << " est en cours";
		if (yH == 4) {
			yH = 0;
		}
		yH++;
		ofLogVerbose() << music[1][yH + 1] << " est la prochaine musique en cours";
	}
	else if (typeTheme == "ZA") {
		mainMusic.load(music[2][yZA]);
		mainMusic.play();
		ofLogVerbose() << music[2][yZA] << " est en cours";
		if (yZA == 2) {
			yZA = 0;
		}
		ofLogVerbose() << music[2][yZA + 1] << " est la prochaine musique en cours";
		yZA++;
	}
}

void Music::setMusic(string musicTheme) {
	if (mainMusic.getIsPlaying() == false) {
		nextMusic(musicTheme);
	}
}

void Music::changeVolume(float volume) {
	mainMusic.setVolume(volume);
}

void Music::setMusicOff() {
	if (stoppedForRain == true) {
		cout << "PUTAIN";
		nextMusic("Horror");
	}
}

void Music::setStoppedForRain(bool stop) {
	stoppedForRain = stop;
	cout << stoppedForRain;
}

bool Music::getStoppedForRain()
{
	return stoppedForRain;
}
