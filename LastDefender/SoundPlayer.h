#ifndef __SOUNDPLAYER_H_
#define __SOUNDPLAYER_H_

#include <SFML/Audio.hpp>

#define PROTECTOR_MISSILE 1
#define ALIEN_MISSILE 2

class SoundPlayer
{
public:
	SoundPlayer();
	void playProtectorMissile();	
	void playAlienMissile();
	void playExplosion();
	void playMusic();
	/*
	void playMissile_x_Missile();
	void playMissile_x_Alien();
	void playMissile_x_Protector();*/

private:
	sf::Mutex mutex;
	
	int _source;

	int getSource();
	void setSource(int s);

	void playSoundMissile();	

	// PM = Protector Missile
	sf::SoundBuffer _bufferPM;
	sf::Sound _soundPM;

	// AM = Alien Missile
	sf::SoundBuffer _bufferAM;
	sf::Sound _soundAM;

	// Explosion
	sf::SoundBuffer _bufferEx;
	sf::Sound _soundEx;
		
	sf::Music _soundMusic;
};

#endif
