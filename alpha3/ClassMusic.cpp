#include "ClassMusic.h"
//music[0][x] = Ambient Music
//music[1][x] = Horror Music
//music[2][x] = Zombies Attack Music
Music::Music() {
	//Ambient
	musicAmbiance[0].loadSound("(A)Daybreak.mp3");
	musicAmbiance[1].loadSound("(A)End_Of_Days.mp3"); //2:00
	musicAmbiance[2].loadSound("(A)Far_And_Wide.mp3"); //3:27
	//Horror
	musicHorror[0].loadSound("(H)Blood_Pressure.mp3"); //5:05
	musicHorror[1].loadSound("(H)Haunted.mp3"); //6:40
	musicHorror[2].loadSound("(H)Intimidation.mp3");//8:20
	musicHorror[3].loadSound("(H)On_The_Prowl.mp3");//13:30
	musicHorror[4].loadSound("(H)Trick_Or_Treat.mp3");//15:15
	//Zombies Attack
	musicAttack[0].loadSound("(ZA)Electro_Zombies.mp3");//16:30
	musicAttack[1].loadSound("(ZA)Last_Stand.mp3");//19:15
}

void Music::nextMusic(string typeTheme) {
	if (typeTheme == "Ambient") {
		musicAttack[yZA].stop();
		musicAmbiance[yA].play();
		musicHorror[yH].stop();
		if (yA == 2) {
			yA = 0;
		}
		yA++;
	}
	else if (typeTheme == "Horror") {
		musicAttack[yZA].stop();
		musicAmbiance[yA].stop();
		musicHorror[yH].play();
		if (yH == 4) {
			yH = 0;
		}
		yH++;
	}
	else if (typeTheme == "ZA") {
		musicAttack[yZA].play();
		musicAmbiance[yA].stop();
		musicHorror[yH].stop();
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
