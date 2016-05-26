#include "ClassMusic.h"
//music[0][x] = Ambient Music
//music[1][x] = Horror Music
//music[2][x] = Zombies Attack Music
Music::Music() {
	mainMusic.setMultiPlay(false);
	mainMusic.load("PisteAudio.wav");
	mainMusic.play();
	//2:00
	/*musicAmbiance[2].loadSound("(A)Far_And_Wide.mp3"); //3:27
	//Horror
	musicHorror[0].loadSound("(H)Blood_Pressure.mp3"); //5:05
	musicHorror[1].loadSound("(H)Haunted.mp3"); //6:40
	musicHorror[2].loadSound("(H)Intimidation.mp3");//8:20
	musicHorror[3].loadSound("(H)On_The_Prowl.mp3");//13:30
	musicHorror[4].loadSound("(H)Trick_Or_Treat.mp3");//15:15
	//Zombies Attack
	musicAttack[0].loadSound("(ZA)Electro_Zombies.mp3");//16:30
	musicAttack[1].loadSound("(ZA)Last_Stand.mp3");//19:15*/
}

void Music::nextMusic(string typeTheme) {
	if (typeTheme == "Ambient") {
		mainMusic.setPositionMS(0);
		ofSoundUpdate();
		if (yA == 0) {
			mainMusic.setPositionMS(0);
		}
		else if (yA == 1) {
			mainMusic.setPositionMS(120000);
		}
		else if (yA == 2) {
			mainMusic.setPositionMS(207000);
		}
		else if (yA == 3) { yA = 0; }
		yA++;

	}
	else if (typeTheme == "Horror") {
		//cout << "coucou";
		cout << mainMusic.getPositionMS() << "\n";
		ofSoundUpdate();
		if (yH == 0) {
			mainMusic.setPositionMS(305000);
		}
		else if (yH == 1) {
			mainMusic.setPositionMS(384000);
		}
		else if (yH == 2) {
			mainMusic.setPositionMS(492000);
		}
		else if (yH == 3) {
			mainMusic.setPositionMS(798000);
		}
		else if (yH == 4) {
			mainMusic.setPositionMS(909000);
		}
		else if (yH == 5) {
			yH = 0;
		}
		yH++;
	}
	else if (typeTheme == "ZA") {
		ofSoundUpdate();
		if (yZA == 0) {
			mainMusic.setPositionMS(970000);
		}
		else if (yZA == 1) {
			mainMusic.setPositionMS(1149000);
		}
		else if (yZA == 2) {
			yZA = 0;
		}
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
		nextMusic("Horror");
	}
	else if (stoppedForRain == true) {
		nextMusic("Ambient");
	}
}

void Music::setStoppedForRain(bool stop) {
	stoppedForRain = stop;
	//cout << stoppedForRain;
}

bool Music::getStoppedForRain()
{
	return stoppedForRain;
}
