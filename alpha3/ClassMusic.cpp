#include "ClassMusic.h"
//music[0][x] = Ambient Music
//music[1][x] = Horror Music
//music[2][x] = Zombies Attack Music
Music::Music() {
	//Ambient
	musicAmbiance[0].loadSound("(A)Daybreak.mp3");
	musicAmbiance[1].loadSound("(A)End_Of_Days.mp3");
	musicAmbiance[2].loadSound("(A)Far_And_Wide.mp3");
	//Horror
	musicHorror[0].loadSound("(H)Blood_Pressure.mp3");
	musicHorror[1].loadSound("(H)Haunted.mp3");
	musicHorror[2].loadSound("(H)Intimidation.mp3");
	musicHorror[3].loadSound("(H)On_The_Prowl.mp3");
	musicHorror[4].loadSound("(H)Trick_Or_Treat.mp3");
	//Zombies Attack
	musicAttack[0].loadSound("(ZA)Electro_Zombies.mp3");
	musicAttack[1].loadSound("(ZA)Last_Stand.mp3");
	musicAttack[2].loadSound("(ZA)Upstep.mp3");
}

void Music::nextMusic(string typeTheme) {
	if (typeTheme == "Ambient") {
		musicHorror[yH].stop();
		musicAmbiance[yA].play();
		musicAttack[yZA].stop();
		if (yA == 2) {
			yA = 0;
		}
		yA++;
	}
	else if (typeTheme == "Horror") {
		musicHorror[yH].play();
		musicAmbiance[yA].stop();
		musicAttack[yZA].stop();
		if (yH == 4) {
			yH = 0;
		}
		yH++;
	}
	else if (typeTheme == "ZA") {
		musicAttack[yZA].play();
		musicAmbiance[yA].stop();
		musicAttack[yZA].stop();
		if (yZA == 2) {
			yZA = 0;
		}
		yZA++;
	}
}

void Music::changeVolume(float volume, string typeMusic) {
	if (typeMusic == "ambient"){
		musicAmbiance[0].setVolume(volume);
		musicAmbiance[1].setVolume(volume);
		musicAmbiance[2].setVolume(volume);
	} else if (typeMusic == "Horror"){
		musicHorror[0].setVolume(volume);
		musicHorror[1].setVolume(volume);
		musicHorror[2].setVolume(volume);
		musicHorror[3].setVolume(volume);
		musicHorror[4].setVolume(volume);
	} else {
		musicAttack[0].setVolume(volume);
		musicAttack[1].setVolume(volume);
		musicAttack[2].setVolume(volume);
	}
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
